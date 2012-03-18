
#include <iostream>
#include <istream>
#include <ostream>

#include <cmath>

using namespace std;

typedef double pt;

int main()
{
	pt P;

	pt pr[1000001];

	cin >> P;

	int cutoff = 1000000;

	pr[1] = P;

	for (int i = 2; i <= 1000000; ++i)
	{
		pr[i] = (pr[i - 1] * (1 - P)) + ((1 - pr[i - 1]) * P);

		if (abs(pr[i] - 0.5) < 1e-16)
		{
			cutoff = i;

			break;
		}
	}

	int Q;

	cin >> Q;

	int N;

	cout.setf(ios::fixed, ios::floatfield);
	cout.precision(4);

	for (; Q; --Q)
	{
		cin >> N;

		if (N > cutoff)
		{
			cout << pr[cutoff] << endl;
		}
		else
		{
			cout << pr[N] << endl;
		}
	}

	return 0;
}

