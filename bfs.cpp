#include <cmath>
using namespace std;
#include <iostream>
#include <map>
#include <vector>
#include <deque>
#include <iterator>
//By chyx111
#define DBG(a) cerr << #a << ": " << (a) << endl
typedef long long ll;
#define Rep(i,n) for(int n_ = (n), i = 0; i< n_; ++i)
// {{{
struct Edge{
	int to, next;
	int weight;
};

struct DirectedGraph{
	Edge* edge;
	int *from;
	int *head;
	int ne, n, m;

	DirectedGraph(int n, int m)
		:n(n), m(m)
	{
		ne = 0;
		head = new int[n];
		edge = new Edge[m];
		from = new int[n];
		fill(head, head + n, -1);
	}
	~DirectedGraph()
	{
		delete[] head;
		delete[] edge;
		delete[] from;
	}
	void add(int a, int b, int weight)
	{
		edge[ne].weight = weight;
		edge[ne].to = b;
		edge[ne].next = head[a];
		head[a] = ne;
		ne++;
	}
	void add_bi(int a, int b, int weight)
	{
		add(a, b, weight);
		add(b, a, weight);
	}

};
//}}}

struct BfsTraverse{ // {{{
	deque<int> q;
	vector<bool> visit;
	int *from;
	int curr;
	DirectedGraph *dg;
	BfsTraverse(DirectedGraph *dg)
		:curr(-1), dg(dg)
	{
		visit = vector<bool>(dg->n, false);
		from = new int[dg->n];
	}
	~BfsTraverse()
	{
		delete[] from;
	}
	bool operator>>(int& x)
	{
		if(curr != -1){
			expand();
		}
		if(!q.empty()){
			curr = x = q.front();
			q.pop_front();
			return true;
		}else{
			return false;
		}
	}
	void operator<<(int x)
	{
		q.push_back(x);
		visit[x] = true;
		from[x] = -1;
		curr = -1;
	}
	void expand()
	{
		for(int e = dg->head[curr]; e != -1; e = dg->edge[e].next){
			if(dg->edge[e].weight > 0){
				int to = dg->edge[e].to;
				if(!visit[to]){
					q.push_back(to);
					from[to] = curr;
					visit[to] = true;
				}
			}
		}
		curr = -1;
	}
}; // }}}

template<class T> // {{{
struct Discretize{
	map<T, int> dat;
	vector<T> raw;
	Discretize()
	{
	}
	int operator[](T key)
	{
		typename map<T, int>::iterator it = dat.find(key);
		if(it == dat.end()){
			dat[key] = raw.size();
			raw.push_back(key);
			it = dat.find(key);
		}
		return it->second;
	}
	T index(int index)
	{
		return raw[index];
	}
}; // }}}

char maze[][11] =
{
	"..........",
	"..00000...",
	"..0...0...",
	"......0...",
	"......0...",
	"..........",
	"..00......",
	"..00......",
	"..00000...",
	".........."
};

int dist[100][100];

int n = 10;
void draw()
{
	Rep(i, n){
		Rep(j, n){
			cout << maze[i][j] << " ";
		}
		cout << endl;
	}
}

int main()
{
	DirectedGraph graph(n * n, n * n * 5);
	Discretize<pair<int, int> > disc;
	Rep(i, n)Rep(j, n - 1){
		graph.add_bi(disc[pair<int, int>(i, j)], disc[pair<int, int>(i, j + 1)], 1);
	}
	Rep(i, n - 1)Rep(j, n){
		graph.add_bi(disc[pair<int, int>(i, j)], disc[pair<int, int>(i + 1, j)], 1);
	}
	draw();

	BfsTraverse bfs(&graph);
	Rep(i, n)Rep(j, n){
		if(maze[i][j] == '0'){
			bfs << disc[pair<int, int>(i, j)];
		}
	}

	int curr;
	int prev = '0';
	while(bfs >> curr){
		pair<int, int> pos = disc.raw[curr];
		int fromi = bfs.from[curr];
		if(fromi == -1){
			continue;
		}
		pair<int, int> from = disc.raw[fromi];
		if(maze[from.first][from.second] > prev){
			prev = maze[from.first][from.second];
			maze[pos.first][pos.second] = prev + 1;
			draw();
		}else{
			maze[pos.first][pos.second] = prev + 1;
		}
	}
}

