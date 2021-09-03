https://www.codingame.com/ide/puzzle/sudoku-validator

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

#define priorityqueue priority_queue<int, vector<int>, greater<int>>

using namespace std;

int main()
{
	priorityqueue queues[27];
	int numbers[9][9];
	int x = 0, y = 0, z = 0;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			int n;
			cin >> n; cin.ignore();
			numbers[i][j] = n;

			x = i;
			y = 9 + j;
			z = 18 + ((i / 3) * 3 + j / 3);
			queues[x].push(n);
			queues[y].push(n);
			queues[z].push(n);

			cerr << x << y << z << ":" << n << " ";
		}
		cerr << endl;
	}

	cerr << " ------------ " << endl;
	bool isCorrect = true;
	for (int i = 0; i < 27; ++i)
	{
		cerr << i << " ";
		priorityqueue& q = queues[i];
		for (int j = 1; j <= 9; ++j)
		{
			cerr << q.top();
			if (q.top() != j)
			{
				isCorrect = false; break;
			}
			q.pop();
		}
		cerr << endl;
		if (isCorrect == false) break;
	}

	// Write an answer using cout. DON'T FORGET THE "<< endl"
	// To debug: cerr << "Debug messages..." << endl;

	cout << (isCorrect ? "true" : "false") << endl;
}