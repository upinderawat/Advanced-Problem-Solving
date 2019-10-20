#include <bits/stdc++.h>
using namespace std;

std::vector<int> disc;
std::vector<int> low;
int timer = 0;

set<int> find_disc_low(const std::vector<int> adjList[], vector<bool>& visited, int u, int p){
	set<int> cut_v;
	set<int> tmp;
	low[u] = disc[u] = ++timer;
	visited[u] = true;
	int c=0;
	for(auto v : adjList[u]){
		if(!visited[v]){//tree edge
			tmp =find_disc_low(adjList, visited, v, u);
			low[u] = std::min(low[u], low[v]);
			if(low[v] >= disc[u] && p != -1){
				cut_v.insert(u);
			}
			cut_v.insert(tmp.begin(), tmp.end());
		}
		else if(v != p){//back edge
			low[u] = std::min(low[u], disc[v]);
		}
		if(p==-1)c++;
	}
	if(c > 1){
		cut_v.insert(u);
	}
	return cut_v;
}
set<int> articulation_pts(int n, const std::vector<int> adjList[]){
	set<int> cut_v;
	set<int> tmp;
	vector<bool> visited(n, false);
	for(int i=0; i<n; i++){
		if(!visited[i]){
			tmp =find_disc_low(adjList,visited, i, -1);
			cut_v.insert(tmp.begin(), tmp.end());
		}
	}
	// for(auto u: disc){
	// 	cout<<u<<" ";
	// }
	// cout<<"\n";
	// for(auto u : low){
	// 	cout<<u<<" ";
	// }
	
	return cut_v;
}
int main(int argc, char const *argv[]){
	int n, m;
	int u, v;
	set<int> cut_v;
	cin>>n>>m;
	disc.assign(n, 0);
	low.assign(n, 0);
	std::vector<int> adjList[n];
	while(m--){
		cin>>u>>v;
		adjList[u].push_back(v);
		adjList[v].push_back(u);
	}
	cut_v = articulation_pts(n, adjList);
	for(auto v : cut_v){
		cout<<v<<" ";
	}
	return 0;
}