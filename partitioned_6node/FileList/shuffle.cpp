#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

int main()
{
	string s;
	vector<string> v;
	while(cin >> s)
		v.push_back(s);
	random_shuffle(v.begin(),v.end());
	for(int i = 0; i < v.size(); ++i)
		cout << v[i] << endl;
	return 0;
}
