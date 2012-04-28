
#include <iostream>
#include <istream>
#include <ostream>

#include <cassert>

#include <string>
#include <list>

using namespace std;

char xf(char a, char b)
{
	if ((a == 'a' && b == 'b') || (a == 'b' && b == 'a'))
	{
		return 'c';
	}
	else if ((a == 'a' && b == 'c') || (a == 'c' && b == 'a'))
	{
		return 'b';
	}
	else if ((a == 'b' && b == 'c') || (a == 'c' && b == 'b'))
	{
		return 'a';
	}

	assert(false);
}

int main()
{
	int T;

	cin >> T;

	string str;

	for (; T; --T)
	{
		cin >> str;

		list<char> l;

		for (string::reverse_iterator s_riter = str.rbegin(); s_riter != str.rend(); ++s_riter)
		{
			l.push_front(*s_riter);
		}

		size_t total = 0;

		while (true)
		{
			size_t cnt = 0;

			for (list<char>::iterator l_iter = l.begin(); l_iter != l.end(); ++l_iter)
			{
				list<char>::iterator l_niter = l_iter;

				if (l_niter == l.end())
				{
					break;
				}

				for (++l_niter; l_niter != l.end() && (*l_iter) != (*l_niter); )
				{
					list<char>::iterator l_eiter = l_niter;

					++l_niter;

					(*l_iter) = xf(*l_iter, *l_eiter);

					l.erase(l_eiter);

					++cnt;
					++total;
				}
			}

			if (cnt == 0)
			{
				break;
			}
		}

		cout << (str.size() - total) << endl;
	}

	return 0;
}

