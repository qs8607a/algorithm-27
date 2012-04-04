
struct SuffixArray{
	//static const int MAXN = 10000;
	//int bucket[MAXN];
	//int rank[MAXN], perm[MAXN], work[MAXN], sa[MAXN], height[MAXN];
	int *rank, *perm, *work, *sa, *height, *bucket;
	char *str;
	int n;
	SuffixArray(int _n, char *str)
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
};
