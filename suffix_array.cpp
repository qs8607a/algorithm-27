#include <cmath>
using namespace std;
#include <iostream>
#include <algorithm>
#include <string>
#include <numeric>
#include <cstring>

//By chyx111
typedef long long ll;
#define Rep(i,n) for(int n_ = (n), i = 0; i< n_; ++i)
#define two(x) (1<<(x))

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
struct SuffixArray{
	//static const int MAXN = 10000;
	//int bucket[MAXN];
	//int rank[MAXN], perm[MAXN], work[MAXN], sa[MAXN], height[MAXN];
	RangeMinimumQuery<int> *rmq;
	int *rank, *perm, *work, *sa, *height, *bucket;
	char const *str;
	int n;
	SuffixArray(int _n, char const *str)
		:str(str)
	{
		n = _n + 1;
		rank = new int[n];
		perm = new int[n];
		work = new int[n];
		sa = new int[n];
		height = new int[n];
		bucket = new int[max(128, n)];
		Rep(i, n - 1){
			work[i] = str[i];
		}
		work[n - 1] = 0;
		rmq = NULL;
		build_sa();
	}
	~SuffixArray(){
		delete[] rank;
		delete[] perm;
		delete[] work;
		delete[] sa;
		delete[] height;
		delete[] bucket;
	}
	bool cmp(int *r, int a, int b, int l)
	{
		return r[a] == r[b] && r[a + l] == r[b + l];
	}
	void calc_height()
	{
		height[0] = 0;
		int j = 0;
		for(int i = 0; i < n; ++i){
			if(rank[i] == 0){
				continue;
			}
			int k = sa[rank[i] - 1];
			for(; str[i + j] == str[k + j]; ++j){
			}
			height[rank[i]] = j;
			if(j > 0){
				--j;
			}
		}
	}
	void build_sa(int bucket_sz = 128)
	{
		fill(bucket, bucket + bucket_sz, 0);
		Rep(i, n){
			bucket[work[i]]++;
		}
		partial_sum( bucket, bucket + bucket_sz, bucket );
		for(int i = n - 1; i >= 0; i--){
			sa[--bucket[work[i]]] = i;
		}
		copy(work, work + n, rank);

		for(int step = 1; bucket_sz != n; step *= 2){
			// sort right half
			int p = 0; 
			for(int i = n - step; i < n; ++i){
				perm[p++] = i;
			}
			Rep(i, n)if(sa[i] >= step){
				perm[p++] = sa[i] - step;
			}
			Rep(i, n){
				work[i] = rank[perm[i]];
			}

			// sort left halt
			fill(bucket, bucket + bucket_sz, 0 );
			Rep(i, n){
				bucket[work[i]]++;
			}
			partial_sum( bucket, bucket + bucket_sz, bucket );
			for(int i = n - 1; i >= 0; --i){
				sa[--bucket[ work[i]]] = perm[i];
			}

			// update the rank
			bucket_sz = 0;
			work[sa[0]] = bucket_sz++;
			for(int i = 1; i < n; ++i){
				work[sa[i]] = cmp(rank, sa[i-1], sa[i], step) ? bucket_sz - 1 : bucket_sz++; 
			}
			copy(work, work + n, rank);
		}
	}
	int build_rmq()
	{
		calc_height();
		rmq = new RangeMinimumQuery<int>(n);
		for(int i = 0; i < n; ++i){
			(*rmq)[i] = height[i];
		}
		rmq->build();
	}
	int lcp(int x, int y)
	{
		int a = rank[x];
		int b = rank[y];
		if(a == b){
			return n - x - 1;
		}
		if(a + 1 > b){
			swap(a, b);
		}
		return rmq->query(a + 1, b);
	}
};

int main()
{
	char const* str = "ababbabbbabababaaa";
	SuffixArray sa(strlen(str), str);
	sa.build_rmq();
	int n = strlen(str);
	Rep(i, n + 1){
		cerr << str + sa.sa[i] << endl;
		cerr << sa.height[i] << endl;
	}
	Rep(i, n){
		for(int j = i; j < n; ++j){
			cerr << i << " " << j << " " 
				<< str + i << " "
				<< str + j << " "
				<< sa.lcp(i, j) << endl;
		}
	}
}

