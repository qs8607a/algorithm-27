template<class T>
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
};


