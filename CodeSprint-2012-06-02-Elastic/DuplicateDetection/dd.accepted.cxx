
#include <iostream>
#include <istream>
#include <ostream>
#include <sstream>

#include <deque>
#include <map>
#include <string>
#include <utility>

using namespace std;

map<string, bool> V;
map<string, map<string, bool> > E;

int main()
{
	int N;

	string l;

	getline(cin, l);

	stringstream ss(l);

	ss >> N;

	int cnt = 0;

	for (int i = 0; i != N; ++i)
	{
		getline(cin, l);

		size_t lc = l.find_last_of(',');

		string email = l.substr(lc + 1);

		string rest = l.substr(0, lc);

		lc = rest.find_last_of(',');

		string phone = rest.substr(lc + 1);

		V[email] = false;
		V[phone] = false;
		E[email][phone] = true;
		E[phone][email] = true;
	}

	deque<string> list;

	for (map<string, bool>::iterator v_iter = V.begin(); v_iter != V.end(); ++v_iter)
	{
		list.push_back(v_iter->first);

		bool unseen = false;

		while (! list.empty())
		{
			string v0 = list.front();

			list.pop_front();

			if (! V[v0])
			{
				V[v0] = true;

				unseen = true;

				for (map<string, bool>::iterator e_iter = E[v0].begin(); e_iter != E[v0].end(); ++e_iter)
				{
					list.push_back(e_iter->first);
				}
			}
		}

		if (unseen)
		{
			++cnt;
		}
	}

	cout << cnt << endl;

	return 0;
}

