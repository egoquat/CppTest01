#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <sstream>
#include <math.h>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

#define ITERV vector<string>::iterator
typedef unsigned int uint;

template<typename Out>
void split(const std::string& s, char delim, Out result) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

std::vector<std::string> split(const std::string& s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

string ToBinary(const string& E)
{
    vector<string> buffers = split(E, ' ');

    bool isChar = true;

    string binary;
    string character;
    ITERV iter = buffers.begin();
    for (; iter != buffers.end(); ++iter)
    {
        string c = *iter;
        if (true == isChar)
        {
            if ("0" != c && "00" != c)
            {
                binary.clear(); break;
            }
            character = ("0" == c ? "1" : "0");
        }
        else
        {
            int count = c.size();
            for (int i = 0; i < count; ++i)
            {
                binary.append(character);
            }
        }
        isChar = !isChar;
    }

    return binary;
}

char ToChar(const string& B)
{
    int decimal = 0;
    char c = -1;
    for (int i = 0; i < B.size(); ++i)
    {
        decimal += ('1' == B[B.size() - i - 1] ? pow(2, i) : 0);
    }

    cerr << "Char:" << (char)decimal << "/Dec:" << decimal << endl;

    if (decimal >= 32 && decimal <= 126)
    {
        c = (char)decimal;
    }

    return c;
}

string ToString(const string& B)
{
    if (B.size() % 7 != 0)
        return "INVALID";

    string buffer;
    string output;
    bool isValid = true;

    for (int i = 0; i < B.size(); ++i)
    {
        buffer += B[i];

        if (buffer.size() == 7)
        {
            char c = ToChar(buffer);

            if (0 > c)
            {
                isValid = false;
                break;
            }
            cerr << "ToString/buffer:" << buffer << "/c:" << c << endl;
            output += c;
            buffer.clear();
        }
    }

    if (false == isValid || output.size() <= 0)
    {
        output = "INVALID";
    }

    return output;
}

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    string ENCRYPT;
    getline(cin, ENCRYPT);

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    string binary = ToBinary(ENCRYPT);

    cerr << "Input:" + ENCRYPT << endl;
    cerr << "InputBinary:" << binary << endl;

    string output = ToString(binary);
    cerr << output << endl;

    cout << output << endl;
    //cout << "INVALID" << endl;
}