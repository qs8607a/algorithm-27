#include <sstream>
#include <cassert>
#include <map>
#include <vector>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <numeric>
using namespace std;
//By chyx111
#define DBG(a) cerr << #a << ": " << (a) << endl
#define Rep(i,n) for(int n_ = (n), i = 0; i< n_; ++i)
template <class T> inline void checkMax(T &a, T b) {if (a < b) a = b;}
#define PR pair
template<typename S, typename T> ostream& operator<<(ostream& os, pair<S,T> p){ return os << "(" << p.first << "," << p.second << ")"; };
typedef pair<int, int> pii;
typedef long long ll;
