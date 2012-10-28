
#include <iostream>
#include <istream>
#include <ostream>

#include <list>
#include <map>
#include <utility>
#include <vector>

using namespace std;

typedef long long mint;

int main()
{
	int t;
	
	cin >> t;

	for (; t; --t)
	{
		mint n, m, k;
		mint i, j, c;

		cin >> n >> m >> k;

		mint weight = 0;
		mint comps = n;
		vector<mint> v2c(n);
		vector<list<mint> > c2v(n);
		vector<mint> csz(n);
		map<mint, list<pair<mint, mint> > > es;

		for (mint cnt = 0; cnt != n; ++cnt)
		{
			v2c[cnt] = cnt;
			c2v[cnt].push_front(cnt);
			csz[cnt] = 1;
		}

		for (mint cnt = 0; cnt != m; ++cnt)
		{
			cin >> i >> j >> c;
			--i;
			--j;

			es[c].push_front(make_pair(i, j));
		}
		
		for (map<mint, list<pair<mint, mint> > >::iterator es0_iter = es.begin(); es0_iter != es.end(); ++es0_iter)
		{
			for (list<pair<mint, mint> >::iterator es_iter = es0_iter->second.begin(); es_iter != es0_iter->second.end(); ++es_iter)
			{
				if (comps <= k)
				{
					break;
				}
	
				mint i0, j0;
	
				i0 = es_iter->first;
				j0 = es_iter->second;
	
				if (v2c[i0] == v2c[j0])
				{
					continue;
				}
	
				weight += es0_iter->first;
				--comps;
	
				mint n_comp = v2c[i0];
				mint obs_comp = v2c[j0];

				if (csz[n_comp] < csz[obs_comp])
				{
					swap(n_comp, obs_comp);
				}
	
				for (list<mint>::iterator v_iter = c2v[obs_comp].begin(); v_iter != c2v[obs_comp].end(); ++v_iter)
				{
					v2c[*v_iter] = n_comp;
					c2v[n_comp].push_front(*v_iter);
				}

				csz[n_comp] += csz[obs_comp];
			}
		}

		if (comps > k)
		{
			cout << "Impossible!" << endl;
		}
		else
		{
			cout << weight << endl;
		}
	}

	return 0;
}

