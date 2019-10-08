#include <bits/stdc++.h>
#define ll long long
using namespace std;

struct trie{
	trie* child[2];//0 and 1 for unset and set bit
	trie(){
		child[0] = nullptr;
		child[1] = nullptr;
	} 
};

int main(){
	int n,m;
	ll max_xor;
	trie* root= new trie;
	trie *ptr;
	ll tmp;
	ll q;
	cin>>n>>q;
	while(n--){
		ptr = root;
		cin>>tmp;
		bitset<40> bitword(tmp);
		for(int i=39; i>=0; i--){
			if(ptr->child[bitword[i]] == nullptr){
				ptr->child[bitword[i]] = new trie;
			}	
			ptr = ptr->child[bitword[i]];
		}
	}
	while(q--){
		max_xor = 0;
		ptr = root;
		cin>>tmp;
		bitset<40> bitword(tmp);
		for(int i=39; i>=0; i--){
			max_xor = max_xor<<1;
			if(bitword.test(i)){
				if(ptr->child[0]){
					max_xor += 1;
					ptr = ptr->child[0];
				}
				else{
					ptr = ptr->child[1];
				}
			}
			else{
				if(ptr->child[1]){
					max_xor += 1;
					ptr = ptr->child[1];
				}
				else{
					ptr = ptr->child[0];
				}	
			}
		}
		cout<<max_xor<<"\n";
	}


	return 0;
}
