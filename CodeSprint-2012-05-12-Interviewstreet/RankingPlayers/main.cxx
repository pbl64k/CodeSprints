
#include <iostream>
#include <istream>
#include <ostream>

#include <cmath>
#include <cstdlib>

#include <time.h>

#include <algorithm>
#include <deque>
#include <list>
#include <map>
#include <utility>
#include <vector>

int gameResult(int player1, int player2);

using namespace std;

#include "rp.cxx"

double g[20] = {1100.0, 1200.0, 800.0, 300.0, 2400.0, 2100.0, 1400.0, 1500.0, 700.0, 1250.0,
                1225.0, 1025.0, 950.0, 975.0, 2350.0, 2250.0, 1475.0, 1325.0, 850.0, 1900.0};

int gr0(int p1, int p2)
{
	double E = 1.0 / (1.0 + pow(10.0, ((g[p2] - g[p1]) / 400.0)));

	//cout << p1 << " " << p2 << ": " << E << endl;

	double x = (0.0 + rand()) / RAND_MAX;

	//cout << "x " << x << endl;

	//cout << "? " << (x < E) << endl;

	return x < E ? p1 : p2;
}

int total_call_cnt = 0;

int gameResult(int player1, int player2)
{
	++total_call_cnt;
	return gr0(player1, player2);
}

int main()
{
	srand(time(NULL));

	vector<int> res = game(20);

	for (vector<int>::iterator r_iter = res.begin(); r_iter != res.end(); ++r_iter)
	{
		cout << (*r_iter) << ": " << g[*r_iter] << endl;
	}

	cout << "Calls: " << total_call_cnt << endl;

	return 0;
}

