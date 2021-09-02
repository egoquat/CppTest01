#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <math.h>

#define RadToDeg 180.0f/3.1415926535f
#define DegToRad 3.1415926535f/180.0f

using namespace std;

float GetAngle(float speed, float r)
{
    return 90.0f - (std::atan(speed * speed / (r * 9.81f)) * RadToDeg);
}

int GetSpeedOptimal(float r)
{
    float speed;
    speed = std::sqrt(std::tan((90.0f - 30.0f) * DegToRad) * (r * 9.81f));
    return (int)speed;
}

bool IsStall(float theta) { return theta < 30; }

int main()
{
    int n;
    cin >> n; cin.ignore();
    int v;
    cin >> v; cin.ignore();
    cerr << "n:" << n << " v:" << v << endl;
    vector<vector<int>> scores(n);
    for (int i = 0; i < n; ++i) scores[i].reserve(3);

    cerr << "--- speed" << endl;
    for (int i = 0; i < n; i++) {
        int speed;
        cin >> speed; cin.ignore();
        scores[i][0] = i;
        scores[i][1] = speed;
        scores[i][2] = 0;
        cerr << (char)('a' + scores[i][0]) << " " << scores[i][1] << " " << scores[i][2] << endl;
    }

    int speedMin = 999999;
    vector<int> bendSpeeds(v);
    for (int i = 0; i < v; i++) {
        int r;
        cin >> r; cin.ignore();
        int speedOptimal = GetSpeedOptimal(r);
        speedMin = std::min(speedMin, speedOptimal);
        bendSpeeds[i] = speedOptimal;
    }
    cerr << endl;

    cerr << "--- scores" << endl;
	for (int i = 0; i < n; ++i)
	{
        cerr << scores[i][0] << " " << scores[i][1] << " ";
        for (int j = 0; j < bendSpeeds.size(); ++j)
        {
            int speedOptimal = bendSpeeds[j];
			if (scores[i][1] > speedOptimal) --scores[i][2];
        }
        cerr << scores[i][2] << endl;
	}

	std::sort(scores.begin(), scores.end(), [&](const vector<int>& a, const vector<int>& b)
		{
            if (a[2] <= -1 && b[2] <= -1)
                return a[2] == b[2] ? a[1] > b[1] : a[2] > b[2];
			else if (a[2] <= -1 || b[2] <= -1)
				return a[2] > b[2];
			else
				return a[1] > b[1];
		});

    cout << speedMin << endl;
    cout << "y" << endl;
    for (int i = 0; i < n; ++i)
    {
        cout << (char)('a' + scores[i][0]) << endl;
    }
}