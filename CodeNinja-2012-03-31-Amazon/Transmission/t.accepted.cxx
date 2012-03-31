
#include <iostream>
#include <istream>
#include <ostream>

#include <map>
#include <set>
#include <utility>

using namespace std;

typedef long long mint;

mint ns[10];

map<pair<short, short>, set<mint>> m;

void f(short i, short j)
{
	if (m.find(pair<short, short>(i, j)) != m.end())
	{
		return;
	}

	if (i == j)
	{
		m[pair<short, short>(i, j)] = set<mint>(ns + i, ns + j + 1);

		return;
	}

	m[pair<short, short>(i, j)] = set<mint>();

	set<mint> &s = m[pair<short, short>(i, j)];

	for (short k = i; k != j; ++k)
	{
		f(i, k);
		f(k + 1, j);

		for (set<mint>::iterator fiter = m[pair<short, short>(i, k)].begin(); fiter != m[pair<short, short>(i, k)].end(); ++fiter)
		{
			for (set<mint>::iterator siter = m[pair<short, short>(k + 1, j)].begin(); siter != m[pair<short, short>(k + 1, j)].end(); ++siter)
			{
				s.insert((*fiter) + (*siter));
				s.insert((*fiter) - (*siter));
				s.insert((*fiter) * (*siter));

				if ((*siter) != 0)
				{
					s.insert((*fiter) / (*siter));
				}
			}
		}
	}
}

int main()
{
	short N;

	cin >> N;

	for (short i = 0; i != N; ++i)
	{
		cin >> ns[i];
	}

	f(0, N - 1);

	mint prev = 0;

	for (set<mint>::iterator iter = m[pair<short, short>(0, N - 1)].begin(); iter != m[pair<short, short>(0, N - 1)].end(); ++iter)
	{
		if ((*iter) < 1)
		{
			continue;
		}

		if ((*iter) != ++prev)
		{
			cout << prev << endl;

			break;
		}
	}

	return 0;
}

