https://www.codingame.com/ide/puzzle/there-is-no-spoon-episode-1

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Don't let the machines win. You are humanity's last hope...
 **/

typedef unsigned int uint;

class VEC
{
public:
    uint x = 0;
    uint y = 0;

    bool isR = false;
    bool isB = false;
};

int main()
{
    int width; // the number of cells on the X axis
    cin >> width; cin.ignore();
    int height; // the number of cells on the Y axis
    cin >> height; cin.ignore();

    cerr << "width:" << width << "//height:" << height << endl;

    const string DEFAULT = "-1 -1";

    if (width <= 0 || height < 0)
    {
        cout << DEFAULT << endl;
        return 1;
    }

    bool** maps = new bool* [height];
    for (uint i = 0; i < height; ++i)
    {
        maps[i] = new bool[width];
    }

    for (int i = 0; i < height; i++) {
        string line; // width characters, each either 0 or .
        getline(cin, line);

        cerr << "line:" << line << endl;

        for (int s = 0; s < line.size(); ++s)
        {
            maps[i][s] = (line[s] == '0');
        }
    }

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    char output[32];

    for (int h = 0; h < height; ++h)
    {
        for (int w = 0; w < width; ++w)
        {
            if (true == maps[h][w])
            {
                //bool isRight = (w < width - 1)?maps[h][w+1]:false;
                //bool isBottom = (h < height - 1)?maps[h+1][w]:false;

                int xN = -1, yN = -1;

                int ibuf = sprintf(output, "%d %d", w, h);

                for (int x = w + 1; x < width; ++x)
                {
                    if (true == maps[h][x])
                    {
                        xN = x; break;
                    }
                }

                yN = (-1 == xN) ? -1 : h;

                ibuf += sprintf(output + ibuf, " %d %d", xN, yN);

                yN = -1;

                for (int y = h + 1; y < height; ++y)
                {
                    if (true == maps[y][w])
                    {
                        yN = y; break;
                    }
                }

                xN = (-1 == yN) ? -1 : w;

                ibuf += sprintf(output + ibuf, " %d %d", xN, yN);

                cout << output << endl;
            }
        }
    }

    //cout << "0 0 1 0 0 1" << endl; // Three coordinates: a node, its right neighbor, its bottom neighbor

    for (int i = 0; i < height; ++i)
    {
        delete[] maps[i];
    }

    delete[] maps;
}
