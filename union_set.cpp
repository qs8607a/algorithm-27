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
