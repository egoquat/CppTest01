#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <math.h>

using namespace std;

struct NCost
{
    int Idx, Cost;
    NCost(int idx, int cost) { Idx = idx; Cost = cost; }
};
class Node
{
public:
    int Idx; vector<NCost> Adjs;
    void AddAdj(int idxAdj, int cost) {
        Adjs.push_back(NCost(idxAdj, cost));
    }
    Node() { }
    void Set(int idx) { Idx = idx; }
};
vector<Node> Nodes;
void fp(int g, int curr, int c, int depth, map<int, bool>& vs, int& cost_) {
    Node& node = Nodes[curr];
    depth++;
    for (int i = 0; i < node.Adjs.size(); ++i) {
        NCost& adj = node.Adjs[i];
        if (vs[adj.Idx] == true) continue;
        int cost = c + adj.Cost;
        if (cost > cost_) continue;
        if (adj.Idx == g) {
            cost_ = cost;
            cerr << "  fp_found:" << g << "/from:" << node.Idx << "/cost:" << adj.Cost << "/depth:" << depth << endl;
            continue;
        }
        vs[adj.Idx] = true;
        cerr << " next:" << adj.Idx << "/cost:" << adj.Cost << "/depth:" << depth << endl;
        fp(g, adj.Idx, cost, depth, vs, cost_);
        vs[adj.Idx] = false;
    }
}
int main()
{
    int n, e, s, g;
    cin >> n >> e >> s >> g; cin.ignore();
    cerr << " n:" << n << "/e:" << e << "/s:" << s << "/g:" << g << endl;
    for (int i = 0; i < n; i++) {
        int node;
        cin >> node; cin.ignore();
    }
    Nodes.resize(n);
    for (int i = 0; i < Nodes.size(); ++i) {
        Nodes[i].Set(i);
    }
    for (int i = 0; i < e; i++) {
        int x, y, c;
        cin >> x >> y >> c; cin.ignore();
        Node& nodeX = Nodes[x];
        Node& nodeY = Nodes[y];
        nodeX.AddAdj(y, c);
        nodeY.AddAdj(x, c);
    }
    vector<int> nexts;
    map<int, bool> vs;
    int costmin = 1 << 30, depth = 0;
    nexts.push_back(s);
    vs[s] = true;
    fp(g, s, 0, depth, vs, costmin);
    cerr << "result cost min : " << costmin << endl;

    // Write an answer using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    cout << "0 0" << endl;
}