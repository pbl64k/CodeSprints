
#include <iostream>
#include <istream>
#include <ostream>

#include <deque>
#include <map>
#include <set>
#include <utility>

using namespace std;

typedef short mint;

mint D;

map<mint, deque<mint> > cs0;
set<mint> q;
map<mint, deque<mint> > cs;

pair<mint, deque<pair<mint, pair<mint, mint> > > > st(mint n)
{
	mint tot = 1;

	deque<pair<mint, pair<mint, mint> > > rtot;

	for (deque<mint>::iterator cs_iter = cs[n].begin(); cs_iter != cs[n].end(); ++cs_iter)
	{
		deque<pair<mint, pair<mint, mint> > > temp_rtot;

		pair<mint, deque<pair<mint, pair<mint, mint> > > > r = st(*cs_iter);

		tot += r.first;

		for (deque<pair<mint, pair<mint, mint> > >::iterator r_iter = r.second.begin(); r_iter != r.second.end(); ++r_iter)
		{
			mint in_path = r_iter->first;
			mint in_nodes = r_iter->second.first;
			mint in_rpath = r_iter->second.second;

			mint tot_path = in_path + in_nodes + in_rpath;

			if (tot_path <= D)
			{
				tot += 1;
	
				temp_rtot.push_back(make_pair(tot_path, make_pair(in_nodes + 1, in_nodes + in_rpath)));

				for (deque<pair<mint, pair<mint, mint> > >::iterator rtot_iter = rtot.begin(); rtot_iter != rtot.end(); ++rtot_iter)
				{
					mint rtot_path = rtot_iter->first;
					mint rtot_nodes = rtot_iter->second.first;
					mint rtot_rpath = rtot_iter->second.second;

					mint tot_path2 = rtot_path + in_path + (rtot_nodes * in_rpath) + (in_nodes * rtot_rpath) + (rtot_nodes * in_nodes);

					if (tot_path2 <= D)
					{
						tot += 1;

						temp_rtot.push_back(make_pair(tot_path2, make_pair(rtot_nodes + in_nodes, in_nodes + in_rpath + rtot_rpath)));
					}
				}
			}
		}

		rtot.insert(rtot.end(), temp_rtot.begin(), temp_rtot.end());
	}

	rtot.push_back(make_pair(0, make_pair(1, 0)));

	return make_pair(tot, rtot);
}

void ren(mint n)
{
	q.insert(n);

	for (deque<mint>::iterator cs0_iter = cs0[n].begin(); cs0_iter != cs0[n].end(); ++cs0_iter)
	{
		if (q.find(*cs0_iter) == q.end())
		{
			cs[n].push_front(*cs0_iter);
			ren(*cs0_iter);
		}
	}
}

int main()
{
	mint T, N, a, b;

	cin >> T;

	for (; T; --T)
	{
		cin >> N >> D;

		cs0 = map<mint, deque<mint> >();
		cs = map<mint, deque<mint> >();
		q = set<mint>();

		for (mint i = 0; i != (N - 1); ++i)
		{
			cin >> a >> b;

			cs0[a].push_front(b);
			cs0[b].push_front(a);
		}

		ren(0);

		// is 0 always the root node?
		pair<mint, deque<pair<mint, pair<mint, mint> > > > r = st(0);

		cout << r.first << endl;
	}

	return 0;
}

