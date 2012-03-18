
#include <iostream>
#include <istream>
#include <ostream>

#include <algorithm>
#include <vector>

using namespace std;

#define M 1000000007LL

typedef long long mint;

mint fact[1001];
mint choice[1001][1001];

mint skmax = 0;

bool lt_skmax(mint x)
{
	return x < skmax;
}

bool gt_skmax(mint x)
{
	return x > skmax;
}

int main()
{
	fact[0] = 1;

	for (mint i = 1; i <= 1000; ++i)
	{
		fact[i] = (fact[i - 1] * i) % M;
	}

	for (mint n = 0; n <= 1000; ++n)
	{
		for (mint k = 0; k <= 1000; ++k)
		{
			if (k == 0)
			{
				choice[n][k] = 1;
			}
			else if (n == 0)
			{
				choice[n][k] = 0;
			}
			else if (n == k)
			{
				choice[n][k] = 1;
			}
			else if (n < k)
			{
				choice[n][k] = 0;
			}
			else
			{
				choice[n][k] = (choice[n - 1][k - 1] + choice[n - 1][k]) % M;
			}
		}
	}

	mint T;

	cin >> T;

	for (; T; --T)
	{
		mint N;

		cin >> N;

		vector<mint> sk(N);

		for (mint i = 0; i != N; ++i)
		{
			cin >> sk[i];
		}

		sort(sk.begin(), sk.end());

		mint K;

		cin >> K;

		vector<mint> sks(K);

		skmax = 0;

		for (mint i = 0; i != K; ++i)
		{
			cin >> sks[i];

			skmax = max(skmax, sks[i]);
		}

		mint result = 0;

		mint ri = 0;
		mint ri2 = 0;

		mint n0 = 0;
		mint ns = 0;

		bool skmax_starter = true;

		for (vector<mint>::iterator starter = lower_bound(sk.begin(), sk.end(), skmax); starter != sk.end(); ++starter)
		{
			n0 = (starter - sk.begin()) - K + (skmax_starter ? 1 : 0);
			ns = (sk.end() - starter) - 1;

			//cout << "n0: " << n0 << " ns: " << ns << endl;

			for (mint i = 0; i <= n0; ++i)
			{
				ri = (choice[n0][i] * fact[i]) % M;

				if (ns > 0)
				{
					for (mint j = 0; j <= n0 - i; ++j)
					{
						ri2 = (ri * ((choice[n0 - i][j] * fact[K + j - (skmax_starter ? 1 : 0)]) % M)) % M;
						ri2 = (ri2 * ((choice[ns][1] * fact[N - i - j - K - 2 + (skmax_starter ? 1 : 0)]) % M)) % M;
						//cout << i << ' ' << j << ' ' << N - i - j - K - 2 << endl;

						result = (result + ri2) % M;
						//cout << "res(j): " << result << " ri: " << ri << " ri2: " << ri2 << endl;
					}
				}
				else
				{
					ri2 = (ri * fact[N - i - 1]) % M;

					result = (result + ri2) % M;
					//cout << "res(j): " << result << " ri: " << ri << " ri2: " << ri2 << endl;
				}
			}

			skmax_starter = false;
		}

		/*
		for (mint i = 0; i <= n0; ++i)
		{
			ri = (((fact[i] * fact[N - i - 1]) % M) * choice[n0][i]) % M;
			result = (result + ri) % M;
		}

	
		cout << result << endl;
		if (ns > 0)
		{
			for (mint i = 0; i <= n0; ++i)
			{
				ri = (((((fact[i + 1] * fact[N - i - 1]) % M) * ns) % M) * choice[n0][i]) % M;
				result = (result + ri) % M;
			}
		}
		*/
	
		cout << result << endl;
	}

	return 0;
}

