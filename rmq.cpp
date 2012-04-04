#include <iostream>
#include <cmath>
using namespace std;
#include <algorithm>
#include <cstdlib>
#include <cassert>
#include <vector>

//By chyx111
#define DBG(a) cerr << #a << ": " << (a) << endl
#define Rep(i,n) for(int n_ = (n), i = 0; i< n_; ++i)
#define two(x) (1<<(x))

template<class T> ostream& operator<<(ostream& os, vector<T> v){
	Rep(i, v.size()){
		if(i){
			os << ' ';
		}
		os << v[i];
	}
	return os;
};

template<class T>
struct RangeMinimumQuery{
	T *dat[20];
	int level, n;
	RangeMinimumQuery(int n)
		:n(n)
	{
		for(level = 0; two(level) <= n; ++level){
			dat[level] = new T[n];
		}
	}
	void build()
	{
		for(int i = 1; i < level; ++i){
			for(int j = 0; j + two(i - 1) < n; ++j){
				dat[i][j] = min(dat[i - 1][j], dat[i - 1][j + two(i - 1)]);
			}
		}
	}
	T query(int from, int to)
	{
		int len = to - from + 1;
		int bit = 31 - __builtin_clz(len);
		return min(dat[bit][from], dat[bit][to - two(bit) + 1]);
	}
	T& operator[](int x){
		return dat[0][x];
	}
};

int main() {
	int n = 10;
	RangeMinimumQuery<int> rmq(n);
	vector<int> arr;
	Rep(i, n){
		arr.push_back(rand() % 20 + 10);
		rmq[i] = arr[i];
	}
	rmq.build();
	Rep(i, n)for(int j = i; j < n; ++j){
		//cerr << i << " " << j << " ";
		//int a, b;
		//DBG(a = rmq.query(i, j));
		//DBG(b = *min_element(arr.begin() + i, arr.begin() + j + 1));
		//if(a != b){
		//	DBG(arr);
		//	DBG(a);
		//	DBG(b);
		//}
		assert(rmq.query(i, j) == *min_element(arr.begin() + i, arr.begin() + j + 1));
	}
	DBG("done");
	return 0;
}

