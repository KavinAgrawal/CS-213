#include <iostream>
#include <set>
#include <vector>
#include <map>

using namespace std;
// otherwise -1

typedef pair<int, int> pairs;
typedef set<pairs> sets;
typedef map<int,vector<int>> Graph;

int main(){
	int n,m;
	cin >> n >> m;
	Graph g;
	for(int i=0 ; i<m ; i++){
		int u,v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	sets s;
	for(int i=0;i<n;i++){
	    pairs x;
	    x.first=g[i].size(); x.second=i;
	    s.insert(x);
	}
	vector<int> c(n,n+1);
	while(!s.empty()){
	    auto it = s.begin();
	    for(size_t i=0;i<g[it->second].size();i++){
	        for(sets::iterator itr = s.begin(); itr!=s.end(); itr++ ){
                if(itr->second == g[it->second][i]){
                    pairs x;
                    x.second = itr->second; x.first = itr->first -1;
                    s.erase(itr);
                    s.insert(x);
                    break;
                }
	   	    }
	    }
        set<int> v;
	    for(size_t i=0;i<g[it->second].size();i++){
	        v.insert(c[g[it->second][i]]);
        }
	    int j=1;
	    for(std::set<int>::iterator i=v.begin();;i++){
	        if(j!=*i || i==v.end()){
                c[it->second]=j;
	            break;
	        }
	        else{ j++;
	        }
	    }
	    s.erase(it);
	}
    for(size_t i=0;i<c.size();i++){
        cout<< c[i] << " ";
    }
}
