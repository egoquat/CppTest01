#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

#define umap unordered_map

int w = 0, h = 0;

bool IsSide(const vector<string>& stgs, int x, int y) {
    bool bSide = (x == 0 || x >= (w - 1)) || (y == 0 || y >= (h - 1));
    if (bSide == true) return true;
    
    int ix = 0, iy = 0; 
    ix = x - 1; iy = y;
    if (x >= 0 && x < w && y >= 0 && y < h) {
        bSide |= (stgs[iy][ix] != '#');
    }
    ix = x + 1; iy = y;
    if (x >= 0 && x < w && y >= 0 && y < h) {
        bSide |= (stgs[iy][ix] != '#');
    }
    ix = x; iy = y - 1;
    if (x >= 0 && x < w && y >= 0 && y < h) {
        bSide |= (stgs[iy][ix] != '#');
    }
    ix = x; iy = y + 1;
    if (x >= 0 && x < w && y >= 0 && y < h) {
        bSide |= (stgs[iy][ix] != '#');
    }
    return bSide;
}

int solution(vector<string> stgs, vector<string> reqs) {
    w = stgs[0].size(), h = stgs.size();
    int ntotal = w * h;
    umap<char, int> stns;
    umap<char, vector<int>> stss;
    for (int i = 0; i < stgs.size(); ++i) {
        const string& stg = stgs[i];
        for (int j = 0; j < stg.size(); ++j) {
            char c = stg[j];
            stns[c]++;
            vector<int>& sts = stss[c];
            int idx = i * w + j;
            sts.push_back(idx);
        }
    }
    
    int num = 0;
    for (int i = 0; i < reqs.size(); ++i) {
        const string& req = reqs[i];
        char c = req[0];
        bool bRAll = req.size() >= 2;
        vector<int>& sts = stss[c];
        if (bRAll == true) {
            num += stns[c];
            stns[c] = 0;
            sts.clear();
            continue;
        }
        if (sts.size() <= 0)
            continue;
        bool bR = false;
        vector<int> rems;
        for (int j = 0; j < sts.size(); ++j) {
            int idx = sts[j];
            int x = idx % w;
            int y = idx / w;
            
            bool bRem = IsSide(stgs, x, y);
            
            if (bRem == true) {
                num++;
                stns[c]--;
                stgs[idx] = '#';
                rems.push_back(idx);
                continue;
            }
        }
    }
    
    int ans = ntotal - num;
    return ans;
}