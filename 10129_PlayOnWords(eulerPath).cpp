#include <cstdlib>
#include <cmath>
#include <map>
#include <set>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <complex>
#include <queue>

using namespace std;
#define pb push_back
#define all(a) (a).begin(),(a).end()
#define sz(a) (int)((a).size())
#define rep(i,n) for(int i=0; i<n; ++i)
#define itr(c) __typeof((c).begin())
#define tr(c, i) for(itr(c) i = (c).begin(); i != (c).end(); ++i)
static const double EPS = 1e-5;

class Edge{
public:
    int src, dst;
    Edge(int src, int dst):src(src), dst(dst){}
};
typedef vector<Edge>  Edges;
typedef vector<Edges> Graph;

void visit(Graph& g, int a, vector<int> &path){
    while(!g[a].empty()){
        int b = g[a].back().dst;
        g[a].pop_back();
        visit(g, b, path);
    }
    path.pb(a);
}

bool eulerpath(Graph &g, int s, vector<int> &path){
    int n = sz(g), m = 0;
    vector<int> deg(n);
    rep(u, n){
        m += sz(g[u]);
        for(Edges::const_iterator e = g[u].begin(); e != g[u].end(); e++ ) deg[e->dst]--;
        deg[u] += sz(g[u]);
    }
    int k = n - count(all(deg), 0);
    if(k == 0 || (k == 2 )){   //&& deg[s] == 1)){
        //path.clear();
        //visit(g, s, path);
        //reverse(all(path));
        return true;//sz(path) == m + 1;
    }
    return false;
}

int main(){
    int T;    cin >> T;
    rep(t, T){
        int N;        cin >> N;
        vector<string> vs(N,"");
        rep(i, N) cin >> vs[i];
        
        Edges edges;
        set<int> tmp;
        rep(i, N)rep(j, N)
            if(i != j && vs[i][sz(vs[i])-1] == vs[j][0]){
                edges.pb( Edge(i, j) );
                tmp.insert( i );
            }
        
        Graph g(N);
        rep(i, sz(edges)) g[edges[i].src].pb( edges[i] );

        int result = false;
        for(set<int>::iterator it = tmp.begin(); it != tmp.end(); it++){
            vector<int> path;
            if(result = eulerpath(g, g[*it][0].src, path)) break;
        }
        
        result?cout << "Ordering is possible."  << endl:
            cout << "The door cannot be opened." << endl;
    }
    return 0;
}
