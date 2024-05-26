#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

int main()
{
    cout << "100BoxRandomTest input count:";
    int cntin = 0;
    try 
    {
        cin >> cntin;
    }
    catch(exception e)
    {

    }


}

void MakeBoxNumbers(int cntin, int*& boxes)
{
    boxes = new int[cntin];
    memset(boxes, 0, sizeof(int) * cntin);
    for (int i = 0; i < cntin; ++i)
    {
        boxes[i] = i + 1;
    }
}

