#include "stdinc.h"

int const N = 10000;
int pnt[N];
int getpnt(int x){
    if( pnt[x] < 0 ) return x;
    return pnt[x] = getpnt( pnt[x] );
}
void merge_set(int x, int y){
    int px = getpnt(x);
    int py = getpnt(y);
    if( px == py )return;
    int sz = pnt[ py ];
    pnt[ py ] = px;
    pnt[ px ] += sz;
}


int main(){
    memset(pnt,-1,(sizeof pnt));
    //1<->2 3
    merge_set(1, 2);
    
    merge_set(1, 1);
    assert( pnt[ getpnt(1) ] == -2 );
    assert( pnt[ getpnt(2) ] == -2 );
    assert( pnt[ getpnt(3) ] == -1 );
    assert( getpnt(1) == getpnt(2) );
    assert( getpnt(1) != getpnt(3) );
}
