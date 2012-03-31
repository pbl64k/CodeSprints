
#include <cassert>

#include <iostream>
#include <istream>
#include <ostream>

#include <utility>
#include <vector>

using namespace std;

pair<int, int> xy2c(int N, int Nm, int R, int x, int y)
{
	int pos = 0;

	int x0 = (x >= R) ? (N - x - 1) : x;
	int y0 = (y >= R) ? (N - y - 1) : y;

	int c = min(x0, y0);

	int sz = ((R - c - 1) * 2) + (1 - Nm);

	if ((y == c) && (x < c + sz))
	{
		pos = x - c;
	}
	else if ((x == c + sz) && (y < c + sz))
	{
		pos = sz + (y - c);
	}
	else if ((y == c + sz) && (x > c))
	{
		pos = (sz * 2) + (c + sz - x);
	}
	else
	{
		pos = (sz * 3) + (c + sz - y);
	}

	return pair<int, int>(c, pos);
}

pair<int, int> c2xy(int N, int Nm, int R, int c, int pos)
{
	int sz = ((R - c - 1) * 2) + (1 - Nm);

	if (sz == 0)
	{
		return pair<int, int>(R - 1, R - 1);
	}

	int pos0 = ((pos < 0) ? (pos + (sz * 4)) : pos) % (sz * 4);

	switch (pos0 / sz)
	{
		case 0:
			return pair<int, int>(c + (pos0 % sz), c);
		case 1:
			return pair<int, int>(c + sz, c + (pos0 % sz));
		case 2:
			return pair<int, int>(c + sz - (pos0 % sz), c + sz);
		case 3:
			return pair<int, int>(c, c + sz - (pos0 % sz));
	}

	assert(false);
}

int main()
{
	int N;

	cin >> N;

	int Nm = N % 2;
	int R = N / 2 + Nm;

	vector<short> M(N * N);

	for (int i = 0; i != N * N; ++i)
	{
		cin >> M[i];
	}

	for (int y = 0; y != N; ++y)
	{
		for (int x = 0; x != N; ++x)
		{
			pair<int, int> c = xy2c(N, Nm, R, x, y);
			pair<int, int> xy = c2xy(N, Nm, R, c.first, c.second + (((c.first % 2) == 0) ? -1 : 1));

			cout << M[xy.first + xy.second * N] << ' ';
		}

		cout << endl;
	}

	return 0;
}

