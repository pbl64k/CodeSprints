
#include <iostream>
#include <istream>
#include <ostream>

#include <deque>
#include <list>
#include <map>
#include <set>

using namespace std;

map<int, int> cities;
map<int, set<int> > cnts;

int main()
{
	int T;

	cin >> T;

	for (; T; --T)
	{
		int N, K;

		cin >> N >> K;

		K *= 2;

		//cout << K << endl;

		cities = map<int, int>();
		cnts = map<int, set<int> >();

		set<int> c_inp;

		for (int i = 0; i != N; ++i)
		{
			int x;

			cin >> x;

			c_inp.insert(x);
		}

		for (set<int>::iterator inp_iter = c_inp.begin(); inp_iter != c_inp.end(); ++inp_iter)
		{
			int x;

			x = *inp_iter;

			cities[x] = 1;

			for (map<int, int>::reverse_iterator c_riter = map<int, int>::reverse_iterator(cities.find(x)); c_riter != cities.rend(); ++c_riter)
			{
				if (c_riter->first < (x - K))
				{
					break;
				}

				//cout << c_riter->first << " " << x << " " << (x - K) << endl;

				++c_riter->second;
			}
		}

		for (map<int, int>::iterator c_iter = cities.begin(); c_iter != cities.end(); ++c_iter)
		{
			//cout << "city " << c_iter->first << " cnt " << c_iter->second << endl;
			cnts[c_iter->second].insert(c_iter->first);
		}

		int cnt = 0;

		while (! cnts.empty())
		{
			map<int, set<int> >::reverse_iterator cnd_riter = cnts.rbegin();

			//cout << "selecting cnt " << cnd_riter->first << " " << cnd_riter->second.size() << endl;

			set<int>::iterator fcty_iter = cnd_riter->second.begin();

			int fcty = *fcty_iter;
			int affct_cnt = cnd_riter->first;

			cnts[affct_cnt].erase(fcty);

			deque<int> affct;

			//cout << "a" << endl;
			//cout << "fcty is " << fcty << endl;

			for (map<int, int>::iterator c_iter = cities.find(fcty); c_iter != cities.end(); ++c_iter)
			{
				if (c_iter->first > (fcty + K))
				{
					break;
				}

				affct.push_back(c_iter->first);
				//cout << c_iter->first << " in range" << endl;
			}

			/*
			deque<int>::iterator in_range_iter = affct.begin();
			int affct_cnt_i = affct_cnt;

			//cout << "b " << affct.back() << endl;

			for (map<int, int>::iterator c_iter = ++cities.find(affct.back()); c_iter != cities.end(); ++c_iter)
			{
				//cout << "updating " << c_iter->first << endl;

				while ((*in_range_iter) < (c_iter->first - K) && in_range_iter != affct.end())
				{
					//cout << "glorp" << endl;
					++in_range_iter;
					--affct_cnt_i;
				}

				if (in_range_iter == affct.end())
				{
					break;
				}

				//cout << "was " << c_iter->second << endl;
				cnts[c_iter->second].erase(c_iter->first);

				c_iter->second -= affct_cnt_i;

				//cout << "is " << c_iter->second << endl;
				cnts[c_iter->second].insert(c_iter->first);
			}
			*/

			deque<int>::reverse_iterator in_range_riter = affct.rbegin();
			int affct_cnt_r = affct_cnt;

			//cout << "c " << affct.front() << endl;

			for (map<int, int>::reverse_iterator c_riter = map<int, int>::reverse_iterator(cities.find(affct.front())); c_riter != cities.rend(); ++c_riter)
			{
				//cout << "updating(2) " << c_riter->first << endl;

				while (in_range_riter != affct.rend() && (*in_range_riter) > (c_riter->first + K))
				{
					//cout << "glorp(2) " << (*in_range_riter) << endl;
					++in_range_riter;
					--affct_cnt_r;
					//cout << "woinka" << endl;
				}

				//cout << "kk" << endl;

				if (in_range_riter == affct.rend())
				{
					break;
				}

				//cout << "was " << c_riter->second << endl;
				cnts[c_riter->second].erase(c_riter->first);

				c_riter->second -= affct_cnt_r;

				//cout << "is " << c_riter->second << endl;
				cnts[c_riter->second].insert(c_riter->first);
			}

			//cout << "d" << endl;

			for (deque<int>::iterator affct_iter = affct.begin(); affct_iter != affct.end(); ++affct_iter)
			{
				//cout << *affct_iter << " removed" << endl;
				cnts[cities[*affct_iter]].erase(*affct_iter);
				cities.erase(*affct_iter);
			}

			// normalize cnts

			list<int> cnts_to_remove;

			//cout << "e" << endl;

			for (map<int, set<int> >::reverse_iterator cnts_riter = cnts.rbegin(); cnts_riter != cnts.rend(); ++cnts_riter)
			{
				if (cnts_riter->second.empty())
				{
					//cout << "marked for removal: cnt " << cnts_riter->first << endl;
					cnts_to_remove.push_front(cnts_riter->first);
				}
			}

			//cout << "f" << endl;

			for (list<int>::iterator rem_iter = cnts_to_remove.begin(); rem_iter != cnts_to_remove.end(); ++rem_iter)
			{
				//cout << "removing " << *rem_iter << endl;
				cnts.erase(*rem_iter);
			}

			++cnt; // D'oh.
		}

		cout << cnt << endl;
	}

	return 0;
}

