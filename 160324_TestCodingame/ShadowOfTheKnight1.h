https://www.codingame.com/ide/puzzle/shadows-of-the-knight-episode-1

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

class Vec
{
public:
	int X = 0, Y = 0;

public:
	void SetZero()
	{
		X = 0; Y = 0;
	}

	Vec& operator+=(const Vec& rhs)
	{
		X += rhs.X;
		Y += rhs.Y;
		return *this; // return the result by reference
	}

	friend Vec operator+(Vec lhs, const Vec& rhs)
	{
		lhs += rhs;
		return lhs;
	}

	Vec& operator*=(const Vec& rhs)
	{
		X = X * rhs.X;
		Y = Y * rhs.Y;
	}

	friend Vec operator*(Vec lhs, const Vec& rhs)
	{
		lhs *= rhs;
		return lhs;
	}

public:
	Vec() {};
	Vec(int x, int y) { X = x; Y = y; }
};

static int MAX(int a, int b)
{
	if (a > b) return a;
	return b;
}

static int MIN(int a, int b)
{
	if (a > b) return b;
	return a;
}

static bool IsFind(const string& text, const char ch)
{
	std::size_t pos = text.find(ch);
	return pos != string::npos;
}

static void GetDir(const string& bombDir, Vec& dir)
{
	dir.SetZero();

	if (true == IsFind(bombDir, 'U'))
	{
		dir.Y = -1;
	}

	if (true == IsFind(bombDir, 'D'))
	{
		dir.Y = 1;
	}

	if (true == IsFind(bombDir, 'L'))
	{
		dir.X = -1;
	}

	if (true == IsFind(bombDir, 'R'))
	{
		dir.X = 1;
	}
}

int main()
{
	int W; // width of the building.
	int H; // height of the building.
	cin >> W >> H; cin.ignore();
	int N; // maximum number of turns before game over.
	cin >> N; cin.ignore();
	int X0;
	int Y0;
	cin >> X0 >> Y0; cin.ignore();

	cerr << "W:" << to_string(W) << "//H:" << to_string(H) << "//N:" << to_string(N) << "//X0:" << to_string(X0) << "//Y0:" << to_string(Y0) << endl;

	string output;

	Vec dir;
	Vec pos(X0, Y0);
	Vec min(0, 0);
	Vec max(W, H);

	Vec length;

	string bombDirPre = "";

	// game loop
	while (1) {
		string bombDir; // the direction of the bombs from batman's current location (U, UR, R, DR, D, DL, L or UL)
		cin >> bombDir; cin.ignore();

		cerr << "bombDir:" << bombDir << endl;

		GetDir(bombDir, dir);

		switch (dir.X)
		{
		case 1:
			min.X = MAX(min.X, pos.X);
			break;
		case -1:
			max.X = MIN(max.X, pos.X);
			break;
		}

		switch (dir.Y)
		{
		case 1:
			min.Y = MAX(min.Y, pos.Y);
			break;
		case -1:
			max.Y = MIN(max.Y, pos.Y);
			break;
		}

		const int WEIGHT = 6;

		int gapX = (max.X - min.X);
		int gapY = (max.Y - min.Y);

		int gapXResult = (gapX > 1) ? gapX / 2 : gapX;
		int gapYResult = (gapY > 1) ? gapY / 2 : gapY;

		if (bombDirPre == bombDir && W < 1000 && H < 1000)
		{
			if (abs(gapXResult) > WEIGHT)
			{
				gapXResult += gapXResult / 2;
			}

			if (abs(gapYResult) > WEIGHT)
			{
				gapYResult += gapYResult / 2;
			}
		}

		length.X = gapXResult;
		length.Y = gapYResult;

		pos = pos + (dir * length);

		// Write an action using cout. DON'T FORGET THE "<< endl"
		// To debug: cerr << "Debug messages..." << endl;

		cout << to_string(pos.X) << " " << to_string(pos.Y) << endl; // the location of the next window Batman should jump to.

		bombDirPre = bombDir;
	}
}
