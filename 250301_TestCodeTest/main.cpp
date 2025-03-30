
// https://www.codingame.com/ide/puzzle/moves-in-maze
#include <iostream>
#include <string>
#include <queue>
#include <algorithm>
#include <unordered_map>
#include <functional>

using namespace std;

#define umap unordered_map

int W = 0, H = 0;
int GetIdx(int x, int y)
{
    return y * W + x;
}
void GetXY(int idx, int& x, int& y)
{
    x = idx % W;
    y = idx / W;
}

struct FDepth {
    int X = 0;
    int Y = 0;
    int Degree = 0;
	void Set(int x, int y, int degree) { X = x; Y = y; Degree = degree; }
	FDepth(int x, int y, int degree) { Set(x, y, degree); }
	FDepth() {}
};

int main()
{
    int w;
    int h;
    cin >> w >> h; cin.ignore();
    W = w; H = h;
    string* maps = new string[h];
    FDepth start;

    for (int i = 0; i < h; i++) {
        string r;
        getline(cin, r);
        maps[i] = r;
        cerr << r << endl;
        for (int j = 0; j < r.size(); ++j){
            char c = r[j];
            if (c == 'S') {
                start.Set(j, i, 0);
                maps[i][j] = '0';
                //cerr << " Start:xy:" << j << ", " << i << endl;
            }
        }
    }

    cerr << "W H " << w << ", " << H << endl;

    const int CntTotal = W * H;
    queue<FDepth> que; 
    que.push(start);
    int cnt = 0, idx = 0, x = 0, y = 0;

    function<char(int)> tochar = [](int num){
        if (num <= 9) return '0' + num;
        int nc = num - 10;
        return 'A' + nc;
    };

    function<bool(int, int, int, queue<FDepth>&)> onUpdate = [&](int xIn, int yIn, int depth, queue<FDepth>& que) {
        int x = xIn, y = yIn;
		if (x <= -1) x = W - 1;
		if (y <= -1) y = H - 1;
		if (x >= W) x = 0;
        if (y >= H) y = 0;
		
        char c = maps[y][x];
        if (c !='.')
            return false;

        char c0 = tochar(depth);       
        maps[y][x] = c0;
        cerr << x << "," << y << "=" << c << ":" << c0 << endl;
		que.push(FDepth(x, y, depth));
        return true;
    };

    int depth = 0;
    bool bProceed = false;
    while(que.size() >= 1)
    {
        FDepth& d = que.front();
        int x = d.X, y = d.Y;
		int currDepth = d.Degree + 1;
        int x2, y2;
        x2 = x + 1; y2 = y;
        bProceed = onUpdate(x2, y2, currDepth, que);
        x2 = x - 1; y2 = y;
        bProceed = onUpdate(x2, y2, currDepth, que);
        x2 = x; y2 = y + 1;
        bProceed = onUpdate(x2, y2, currDepth, que);
        x2 = x; y2 = y - 1;
        bProceed = onUpdate(x2, y2, currDepth, que);
        que.pop();
    }

    for (int i = 0; i < h; i++) {
        //cerr << maps[i] << endl;
        cout << maps[i] << endl;
    }

    delete maps;
}