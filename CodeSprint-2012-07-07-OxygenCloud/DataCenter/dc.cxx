
#include <iostream>
#include <istream>
#include <ostream>

#include <map>
#include <utility>

using namespace std;

#define M 1000000007L

typedef long long unsigned mint;

map<pair<mint, mint>, mint> xp;
map<pair<mint, mint>, mint> b;
map<pair<mint, mint>, mint> m;

mint expmod(mint b, mint x)
{
	if (x == 0)
	{
		return 1;
	}

	pair<mint, mint> ix(b, x);

	if (xp.find(ix) == xp.end())
	{
		if (x % 2 == 0)
		{
			mint p = expmod(b, x / 2);
	
			xp[ix] = (p * p) % M;
		}
		else
		{
			xp[ix] = (expmod(b, x - 1) * b) % M;
		}
	}

	return xp[ix];
}

mint bincoeff(mint n, mint k)
{
	if (k == 0 || k == n)
	{
		return 1;
	}

	if (n == 0)
	{
		return 0;
	}

	pair<mint, mint> ix(n, k);

	if (b.find(ix) == b.end())
	{
		b[ix] = (bincoeff(n - 1, k - 1) + bincoeff(n - 1, k)) % M;
	}

	return b[ix];
}

mint f(mint k, mint n)
{
	if (k == n)
	{
		return 1;
	}

	if (k == (n - 1))
	{
		return k;
	}

	pair<mint, mint> ix(k, n);

	if (m.find(ix) == m.end())
	{
		mint r = 0;

		for (mint i = k + 1; i <= n; ++i)
		{
			mint r0 = expmod(k, i - k);

			r0 = (r0 * f(i - k, n - k)) % M;
			r0 = (r0 * bincoeff(n - k, i - k)) % M;

			r = (r + r0) % M;
		}

		m[ix] = r;
	}

	return m[ix];
}

int main()
{
	mint t, n, res;

	cin >> t;

	for (; t; --t)
	{
		cin >> n;

		res = 0;

		for (mint i = 2; i <= n; ++i)
		{
			res = (res + f(i, n)) % M;
		}

		cout << res << endl;
	}

	return 0;
}

