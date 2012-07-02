
#include <iostream>
#include <istream>
#include <ostream>

#include <vector>

using namespace std;

int n;

vector<short> m;
vector<short> v;

void tr(int i);

void tr0(int i)
{
	if (i < 0 || i >= n * n)
	{
		return;
	}

	if (m[i] && ! v[i])
	{
		tr(i);
	}
}

void tr(int i)
{
	v[i] = 1;

	if (i % n != 0)
	{
		tr0(i - n - 1);
		tr0(i - 1);
		tr0(i + n - 1);
	}

	tr0(i - n);
	tr0(i + n);

	if (i % n != n - 1)
	{
		tr0(i - n + 1);
		tr0(i + 1);
		tr0(i + n + 1);
	}
}

int main()
{
	int t;

	cin >> t;

	for (; t; --t)
	{
		cin >> n;

		m = vector<short>(n * n);
		v = vector<short>(n * n);

		for (int i = 0; i != n * n; ++i)
		{
			cin >> m[i];
		}

		int cnt = 0;

		for (int i = 0; i != n * n; ++i)
		{
			if (m[i] && ! v[i])
			{
				++cnt;

				tr(i);
			}
		}

		cout << cnt << endl;
	}

	return 0;
}

