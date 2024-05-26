#include <string>
#include <vector>

using namespace std;

struct Point{
    bool bSet = false;
    int X = 0, Y = 0;
    void Set(int x, int y) {X=x; Y=y; bSet=true;}
    Point() {}
    Point(int x, int y) { Set(x, y); }
};
vector<int> solution(vector<string> park, vector<string> rs) {
    int w = park[0].size();
    int h = park.size();
    Point st;
    for (int y = 0; y < park.size(); ++y) {
        string& l = park[y];
        for (int x = 0; x < l.size(); ++x) {
            char c = l[x];
            if (c == 'S') {
                st.Set(x, y); 
                break;
            }
        }
        if (st.bSet == true) { break; }
    }
    
    for (int i = 0; i < rs.size(); ++i) {
        string& r = rs[i];
        
    }
    vector<int> ans;
    return ans;
}
