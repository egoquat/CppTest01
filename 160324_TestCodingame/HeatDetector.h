#include <stdlib.h>
#include <vector>
#include <math.h>

using namespace std;

class HeatDetector
{
	typedef unsigned int uint;

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
		int W = 4; // width of the building.
		int H = 8; // height of the building.
		//cin >> W >> H; cin.ignore();

		int N = 40; // maximum number of turns before game over.
		//cin >> N; cin.ignore();

		int X0 = 2;
		int Y0 = 3;
		//cin >> X0 >> Y0; cin.ignore();

		// game loop
		while (1) {
			string bombDir; // the direction of the bombs from batman's current location (U, UR, R, DR, D, DL, L or UL)
			cin >> bombDir; cin.ignore();

			// Write an action using cout. DON'T FORGET THE "<< endl"
			// To debug: cerr << "Debug messages..." << endl;

			cout << "0 0" << endl; // the location of the next window Batman should jump to.
		}
	}
};

