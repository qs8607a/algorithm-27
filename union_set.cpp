#include "stdinc.h"

struct UnionSet{
	int *pnt;
	int n;
	UnionSet(int n)
		:n(n)
	{
		pnt = new int[n];
		Rep(i, n){
			pnt[i] = -1;
		}
	}
	~UnionSet()
	{
		delete[] pnt;
	}
	void merge_set(int x, int y)
	{
		int px = get_pnt(x);
		int py = get_pnt(y);
		if(px == py){
			return;
		}
		pnt[px] += pnt[py];
		pnt[py] = px;
	}
	int get_pnt(int x)
	{
		if(pnt[x] < 0){
			return x;
		}
		return pnt[x] = get_pnt(pnt[x]);
	}
};
// poj3908

class UnionSet2{  // {{{
	vector<int> pnt;
	vector<int> id;
	int n;
	public:
	UnionSet2(int n)
		:n(n)
	{
		id = vector<int>(n);
		pnt = vector<int>(n);
		Rep(i, n){
			id[i] = i;
			pnt[i] = -1;
		}
	}
	void merge_set(int x, int y)
	{
		int px = get_pnt(x);
		int py = get_pnt(y);
		if(px == py){
			return;
		}
		pnt[px] += pnt[py];
		pnt[py] = px;
	}
	int get_pnt(int x)
	{
		return get_pnt_impl(id[x]);
	}
	int get_size(int x)
	{
		return -pnt[get_pnt(x)];
	}
	void remove(int x)
	{
		int old = get_pnt(x);
		if(pnt[old] == -1){
			return; // only one element
		}
		++pnt[old]; // decrease size
		id[x] = pnt.size();
		pnt.push_back(-1);
	}
	private:
	int get_pnt_impl(int x)
	{
		if(pnt[x] < 0){
			return x;
		}
		return pnt[x] = get_pnt_impl(pnt[x]);
	}

}; // }}}

int main(){
	UnionSet union_set(4);
    //1<->2 3
    union_set.merge_set(1, 2);
    
    union_set.merge_set(1, 1);
    assert( union_set.pnt[ union_set.get_pnt(1) ] == -2 );
    assert( union_set.pnt[ union_set.get_pnt(2) ] == -2 );
    assert( union_set.pnt[ union_set.get_pnt(3) ] == -1 );
    assert( union_set.get_pnt(1) == union_set.get_pnt(2) );
    assert( union_set.get_pnt(1) != union_set.get_pnt(3) );
}
