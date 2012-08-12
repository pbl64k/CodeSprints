
#include <iostream>
#include <istream>
#include <ostream>

#include <map>
#include <string>
#include <utility>

using namespace std;

int main()
{
	int N, k;

	cin >> N;

	map<string, int> cnts;

	string t;

	for (; N; --N)
	{
		cin >> t;

		++cnts[t];
	}

	cin >> k;

	map<int, map<string, bool> > freqs;

	for (map<string, int>::iterator i = cnts.begin(); i != cnts.end(); ++i)
	{
		freqs[i->second][i->first] = true;
	}

	for (map<int, map<string, bool> >::reverse_iterator i = freqs.rbegin(); i != freqs.rend(); ++i)
	{
		for (map<string, bool>::iterator j = i->second.begin(); j != i->second.end(); ++j)
		{
			cout << j->first << endl;
	
			--k;

			if (! k)
			{
				break;
			}
		}

		if (! k)
		{
			break;
		}
	}

	return 0;
}

