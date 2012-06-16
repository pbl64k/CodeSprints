
#include <iostream>
#include <istream>
#include <ostream>

#include <list>
#include <string>
#include <utility>

using namespace std;

int main()
{
	int N;

	cin >> N;

	for (; N; --N)
	{
		string d;
		string s;

		cin >> d;
		cin >> s;

		list<pair<bool, pair<int, string::iterator> > > cs;

		for (string::iterator d_iter = d.begin(); d_iter != d.end(); ++d_iter)
		{
			for (list<pair<bool, pair<int, string::iterator> > >::iterator cs_iter = cs.begin(); cs_iter != cs.end(); ++cs_iter)
			{
				if (*(cs_iter->second.second) == *d_iter)
				{
					cs.push_front(make_pair(true, make_pair(cs_iter->second.first + (cs_iter->first ? 0 : 1), cs_iter->second.second + 1)));
				}

				cs_iter->first = false;
			}

			if (*d_iter == *(s.begin()))
			{
				cs.push_front(make_pair(true, make_pair(1, s.begin() + 1)));
			}
		}

		int max_l = 0;
		int min_c = 0;

		for (list<pair<bool, pair<int, string::iterator> > >::iterator cs_iter = cs.begin(); cs_iter != cs.end(); ++cs_iter)
		{
			if (cs_iter->second.second - s.begin() > max_l)
			{
				max_l = cs_iter->second.second - s.begin();
				min_c = cs_iter->second.first;
			}
			else if ((cs_iter->second.second - s.begin() == max_l) && (cs_iter->second.first < min_c))
			{
				min_c = cs_iter->second.first;
			}
		}

		cout << max_l << " " << min_c << endl;
	}

	return 0;
}

