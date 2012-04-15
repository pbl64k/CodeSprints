
#include <iostream>
#include <istream>
#include <ostream>

using namespace std;

typedef long mint;

int main()
{
	mint N;

	cin >> N;

	mint count = 1;

	mint last, cur;

	bool exp_growth = true;

	cin >> last;

	for (mint i = 1; i != N; ++i)
	{
		cin >> cur;

		if (cur == last)
		{
			continue;
		}

		if ((cur > last) == exp_growth)
		{
			++count;

			exp_growth = !exp_growth;
		}

		last = cur;
	}

	cout << count << endl;

	return 0;
}

