
#include <iostream>
#include <istream>
#include <ostream>

#include <deque>

using namespace std;

int main()
{
	int N;

	cin >> N;

	long long P = 1;
	int zeroes = 0;
	deque<long long> xs;

	for (; N; --N)
	{
		long long x;

		cin >> x;

		if (x)
		{
			P *= x;

			xs.push_back(x);
		}
		else
		{
			++zeroes;

			xs.push_back(x);
		}
	}

	if (zeroes > 1)
	{
		for (deque<long long>::iterator j = xs.begin(); j != xs.end(); ++j)
		{
			cout << 0 << endl;
		}
	}
	else if (zeroes == 1)
	{
		for (deque<long long>::iterator j = xs.begin(); j != xs.end(); ++j)
		{
			cout << ((*j) ? 0 : P) << endl;
		}
	}
	else
	{
		for (deque<long long>::iterator j = xs.begin(); j != xs.end(); ++j)
		{
			cout << (P / (*j)) << endl;
		}
	}
}

