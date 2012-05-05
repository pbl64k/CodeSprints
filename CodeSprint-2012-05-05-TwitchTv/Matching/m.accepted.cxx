
#include <iostream>
#include <istream>
#include <ostream>

#include <vector>

using namespace std;

#define M 1000000007

vector<long long> c(1000001);

long long exteuc(long long a, long long b)
{
	long long x1, x2, x3, y1, y2, y3, r1, r2, r3, q;

	x1 = 1; y1 = 0; r1 = a;
	x2 = 0; y2 = 1; r2 = b;

	do
	{
		q = r1 / r2;
		x3 = x1 - (q * x2);
		y3 = y1 - (q * y2);
		r3 = (x3 * a) + (y3 * b);

		x1 = x2; y1 = y2; r1 = r2;
		x2 = x3; y2 = y3; r2 = r3;
	}
	while (r3 > 0);

	return y1;
}

int main()
{
	long long N;

	cin >> N;

	++N;

	c[0] = 1;
	c[1] = 1;

	for (long long i = 2; i <= N; ++i)
	{
		long long ci = 0;

		ci = (2 * c[i - 1]) % M;
		ci = (((2 * (i - 1)) + 1) * ci) % M;

		long long mi = (exteuc(M, i + 1) % M);
		mi = mi < 0 ? mi + M : mi;

		ci = (mi * ci) % M;

		c[i] = ci;
	}

	cout << c[N - 1] << endl;;

	return 0;
}

