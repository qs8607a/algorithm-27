#include "stdinc.h"

vector<int> zalgorithm(string input) {
	int n = input.size();
	vector<int> ret(n);

	ret[0] = n;
	int L = -1, R = -1;
	for(int i = 1; i < n; ++i){
		if( R < i ){
			L = R = i;
			for(int j = 0; i + j < n; ++j){
				if( input[j] == input[i+j] ){
					R++;
				}else{
					break;
				}
			}
			ret[i] = R - L;
			R--;
		}else if( ret[i - L] + i - 1 < R ){
			ret[i] = ret[i-L];
		}else{
			for(int j = R - i; i + j < n; ++j){
				if( input[j] == input[i+j] ){
					R++;
				}else{
					break;
				}
			}
			L = i;
			ret[i] = R - L;
			R--;
		}
		//cout<<i<<" "<<L<<" "<<R<<" "<<ret[i]<<endl;
	}
	return ret;
}

vector<int> zalgorithm_mock(string input){
	int n = input.size();
	vector<int> ret(n);
	Rep(i, n){
		ret[i] = 0;
		for(int j = 0;  i + j < n; ++j){
			if( input[j] == input[i+j] ){
				ret[i]++;
			}else{
				break;
			}
		}
	}
	return ret;
}

int main(){
	string string_test;
	Rep(i, 1000){
		string_test += rand() % 2 + '0';
	}
//	cout<<string_test<<endl;
//	vector<int> v1 = zalgorithm_mock(string_test);
//	vector<int> v2 = zalgorithm(string_test);
//	copy(ALL(v1), ostream_iterator<int>(cout," ")); cout<<endl;
//	copy(ALL(v2), ostream_iterator<int>(cout," ")); cout<<endl;

	assert( zalgorithm_mock(string_test) == zalgorithm(string_test) );
}
