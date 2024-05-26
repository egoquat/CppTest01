#pragma once

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <cmath>

using namespace std;
typedef vector<int> vecs;
typedef vector<vecs> vvecs;

int H, W;
bool ranged(int x, int y) { return x >= 0 && x <= W - 1 && y >= 0 && y <= H - 1; }
int idxing(int x, int y) { return y * W + x; }
void dfs(vvecs& dots, map<int, bool>& vs, int ig, int xin, int yin, vecs& accums, int& xmin, int& xmax) {
    int idx;
    idx = idxing(xin, yin);
    vs[idx] = true;
    accums.push_back(idx);
    xmin = min(xmin, xin); xmax = max(xmax, xin);
    cout << "dfs "<< ig << " add:" << xin << "/" << yin << endl;
    int xs[4], ys[4];
    xs[0] = xin; 	ys[0] = yin - 1;
    xs[1] = xin + 1; ys[1] = yin;
    xs[2] = xin; 	ys[2] = yin + 1;
    xs[3] = xin - 1; ys[3] = yin;
    int x, y;
    for (int i = 0; i <= 3; ++i) {
        x = xs[i]; y = ys[i];
        int idx2 = idxing(x, y);
        if (ranged(x, y) && dots[y][x] == 1 && vs[idx2] == false) {
            dfs(dots, vs, ig, x, y, accums, xmin, xmax);
        }
    }

}

int solution(vector<vector<int>> dots) {
    H = dots.size(); W = dots[0].size();
    map<int, bool> vs;
    map<int, int> sums;
    vecs acs;
    int xmin, xmax, omax = -(1 << 30);
    for (int i = 0; i < dots.size(); ++i) {
        vecs& ds = dots[i];
        for (int j = 0; j < ds.size(); ++j) {
            int oil = ds[j];
            if (oil == 0) continue;
            int idx = idxing(j, i);
            if (vs[idx] == true) continue;
            xmin = 1 << 30, xmax = -(1 << 30);
            dfs(dots, vs, acs.size(), j, i, acs, xmin, xmax);
            int am = acs.size();
            for (int k = xmin; k <= xmax; k++) {
                int oil = sums[k] += am;
                if (omax < oil) {
                    omax = oil;
                    cout << "update max oil("<< k <<") : " << omax << "// " << xmin << "-" << xmax << "//am:" << am << endl;
                }
            }
            acs.clear();
        }
    }

    int ans = omax;
    return ans;
}