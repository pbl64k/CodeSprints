
#include <iostream>
#include <istream>
#include <ostream>

#include <cmath>

#include <map>
#include <vector>
#include <utility>

using namespace std;

long double Pr0(long long n, map<pair<long long, long long>, long double> &pr, map<long long, long double> &pr0, long double p, long long k);

long double Pr(long long n, long long i, map<pair<long long, long long>, long double> &pr, map<long long, long double> &pr0, long double p, long long k)
{
	pair<long long, long long> key(n, i);

	if (pr.find(key) == pr.end())
	{
		if (i > n)
		{
			pr[key] = 0;
		}
		else if (n == 1)
		{
			if (i == 0)
			{
				pr[key] = 1 - p;
			}
			else
			{
				pr[key] = p;
			}
		}
		else if (i == 0)
		{
			pr[key] = (1 - Pr0(n - 1, pr, pr0, p, k)) * (1 - p);
		}
		else
		{
			pr[key] = Pr(n - 1, i - 1, pr, pr0, p, k) * p;
		}
	}

	return pr[key];
}

long double Pr0(long long n, map<pair<long long, long long>, long double> &pr, map<long long, long double> &pr0, long double p, long long k)
{
	if (pr0.find(n) == pr0.end())
	{
		if (n < k)
		{
			pr0[n] = 0;
		}
		else
		{
			pr0[n] = Pr0(n - 1, pr, pr0, p, k) + Pr(n, k, pr, pr0, p, k);
		}
	}

	return pr0[n];
}

int main()
{
	int T;

	cin >> T;

	for (; T; --T)
	{
		long double p;
		long long k;

		cin >> p >> k;

		map<pair<long long, long long>, long double> pr;
		map<long long, long double> pr0;

		long long po = 0;
		long double exp = 0;
		long double exppo = 0;

		for (long long i = 1; ; ++i)
		{
			po += (2 * i) - 1;

			long double pcur = Pr(i, k, pr, pr0, p, k);

			if (i >= k && (pcur < 1e-12))
			{
				break;
			}

			exp += i * pcur;
			exppo += po * pcur;
		}

		cout << floor(exp) << ' ' << floor(exppo) << endl;
	}

	return 0;
}

