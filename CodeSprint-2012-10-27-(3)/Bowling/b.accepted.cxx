
#include <iostream>
#include <istream>
#include <ostream>

using namespace std;

#define M 1000000007

// !
typedef int mint;

#define S (100 + 1) * ((30 + 1) * 100) * (10 + 2) * (10 + 2)

int mm[S];

mint f(mint fr, mint sc, mint n1, mint n2);
mint ff(mint fr, mint sc, mint n1, mint n2);
mint ff1(mint fr, mint sc, mint n1);
mint ff12(mint fr, mint sc, mint n1, mint n2);

mint f(mint fr, mint sc, mint n1, mint n2)
{
	if (fr < 0 || sc < 0 || sc > 30 * fr)
	{
		return 0;
	}

	if (mm[fr + (sc * (100 + 1)) + ((n1 + 1) * (100 + 1) * ((30 + 1) * 100)) + ((n2 + 1) * (100 + 1) * ((30 + 1) * 100) * (10 + 2))] == -1)
	{
		mm[fr + (sc * (100 + 1)) + ((n1 + 1) * (100 + 1) * ((30 + 1) * 100)) + ((n2 + 1) * (100 + 1) * ((30 + 1) * 100) * (10 + 2))] = static_cast<int>(ff(fr, sc, n1, n2));
	}

	return mm[fr + (sc * (100 + 1)) + ((n1 + 1) * (100 + 1) * ((30 + 1) * 100)) + ((n2 + 1) * (100 + 1) * ((30 + 1) * 100) * (10 + 2))];
}

mint ff(mint fr, mint sc, mint n1, mint n2)
{
	if (n1 != -1)
	{
		if (n2 != -1)
		{
			return ff12(fr, sc, n1, n2);
		}

		return ff1(fr, sc, n1);
	}
	else if (fr == 1)
	{
		if (sc > 20)
		{
			return 1;
		}
		
		return sc + 1;
	}
	else if (sc == fr * 30)
	{
		return 1;
	}
	else if (sc == 0)
	{
		return 1;
	}
	else if (fr == 0)
	{
		return 0;
	}
	else
	{
		mint cnt = 0;

		for (mint tsc = 0; tsc != 10; ++tsc)
		{
			//cnt = (cnt + (((tsc + 1) * f(fr - 1, sc - tsc, -1, -1)) % M)) % M;

			mint r = f(fr - 1, sc - tsc, -1, -1);

			for (mint j = 0; j != tsc + 1; ++j)
			{
				cnt = (cnt + r) % M;
			}
		}

		for (mint tsc = 0; tsc != 11; ++tsc)
		{
			//cnt = (cnt + ((10 * f(fr - 1, sc - 10 - tsc, tsc, -1)) % M)) % M;
			
			mint r = f(fr - 1, sc - 10 - tsc, tsc, -1);

			cnt = (cnt + r) % M;
			cnt = (cnt + r) % M;
			cnt = (cnt + r) % M;
			cnt = (cnt + r) % M;
			cnt = (cnt + r) % M;
			cnt = (cnt + r) % M;
			cnt = (cnt + r) % M;
			cnt = (cnt + r) % M;
			cnt = (cnt + r) % M;
			cnt = (cnt + r) % M;
		}

		cnt = (cnt + f(fr, sc, 10, -1)) % M;

		return cnt;
	}
}

mint ff1(mint fr, mint sc, mint n1)
{
	if (fr == 0 && sc == 0)
	{
		return 1;
	}
	else if (sc < n1)
	{
		return 0;
	}
	else if (n1 == 10 && fr > 1)
	{
		mint cnt = 0;

		for (mint tsc = 0; tsc != 10; ++tsc)
		{
			//cnt = (cnt + (((tsc + 1) * f(fr - 2, sc - 10 - (tsc * 2), -1, -1)) % M)) % M;

			mint r = f(fr - 2, sc - 10 - (tsc * 2), -1, -1);

			for (mint j = 0; j != tsc + 1; ++j)
			{
				cnt = (cnt + r) % M;
			}
		}

		for (mint tsc = 0; tsc != 10; ++tsc)
		{
			cnt = (cnt + f(fr - 1, sc - 20, tsc, 10 - tsc)) % M;
		}

		for (mint tsc = 0; tsc != 11; ++tsc)
		{
			cnt = (cnt + f(fr - 1, sc - 20 - tsc, 10, tsc)) % M;
		}

		return cnt;
	}
	else if (n1 == 10 && fr == 1)
	{
		mint cnt = 0;

		for (mint tsc = 0; tsc != 10; ++tsc)
		{
			//cnt = (cnt + (((tsc + 1) * f(fr - 1, sc - 10 - tsc, -1, -1)) % M)) % M;
			
			mint r = f(fr - 1, sc - 10 - tsc, -1, -1);

			for (mint j = 0; j != tsc + 1; ++j)
			{
				cnt = (cnt + r) % M;
			}
		}

		for (mint tsc = 0; tsc != 10; ++tsc)
		{
			cnt = (cnt + f(fr - 1, sc - 20, tsc, 10 - tsc)) % M;
		}

		for (mint tsc = 0; tsc != 11; ++tsc)
		{
			cnt = (cnt + f(fr - 1, sc - 20 - tsc, 10, tsc)) % M;
		}

		return cnt;
	}
	else
	{
		mint cnt = 0;

		for (mint tsc = 0; tsc != 10 - n1; ++tsc)
		{
			cnt = (cnt + f(fr - 1, sc - n1 - tsc, -1, -1)) % M;
		}

		for (mint tsc = 0; tsc != 11; ++tsc)
		{
			cnt = (cnt + f(fr - 1, sc - 10 - tsc, tsc, -1)) % M;
		}

		return cnt;
	}
}

mint ff12(mint fr, mint sc, mint n1, mint n2)
{
	if (fr == 0 && sc == 0)
	{
		return 1;
	}
	else if (sc < n1 + n2)
	{
		return 0;
	}
	else if (n1 == 10)
	{
		if (n2 == 10)
		{
			mint cnt = 0;

			for (mint tsc = 0; tsc != 11; ++tsc)
			{
				cnt = (cnt + f(fr - 1, sc - 20 - tsc, n2, tsc)) % M;
			}

			return cnt;
		}
		else
		{
			mint cnt = 0;

			for (mint tsc = 0; tsc != 11 - n2; ++tsc)
			{
				cnt = (cnt + f(fr - 1, sc - 10 - n2 - tsc, n2, tsc)) % M;
			}

			return cnt;
		}
	}
	else if (n1 + n2 == 10)
	{
		mint cnt = 0;

		for (mint tsc = 0; tsc != 11; ++tsc)
		{
			cnt = (cnt + f(fr - 1, sc - 10 - tsc, tsc, -1)) % M;
		}

		return cnt;
	}
	else
	{
		return f(fr - 1, sc - n1 - n2, -1, -1);
	}
}

int main()
{
	for (mint i = 0; i != S; ++i)
	{
		mm[i] = -1;
	}

	mint t;

	cin >> t;

	for (mint tt = 0; tt != t; ++tt)
	{
		mint n, k;

		cin >> n >> k;

		cout << f(n, k, -1, -1) << endl;
	}

	return 0;
}

