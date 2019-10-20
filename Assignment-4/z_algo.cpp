#include <bits/stdc++.h>
using namespace std;

vector<int> build_z(const char *p){
	int l,r;
	int n;
	l = r = 0;
	string s = p;
	n = s.size();
	std::vector<int> z(n, 0);
	for(int i=1; i< n; i++){
		if(i <= r){
			z[i] = std::min(z[i-l], r - i + 1);
		}
		while( (z[i] + i < n) and (s[z[i]] == s[z[i] + i]) ){
			z[i]++;
		}
		if((i + z[i] -1) > r){
			l = i;
			r = i + z[i] -1;
		}
	}
	return z;
}
int find(string s, const char* p){
	s += "$";
	s+= p;
	cout<<s;
	std::vector<int> z= build_z(s.c_str());
	for(auto u : z){
		cout<<u<<" ";
	}
}
int main(int argc, char const *argv[]){
	// vector<int> z = build_z("aaabaab");
	string s="upinder";
	find(s, "er");
	return 0;
}