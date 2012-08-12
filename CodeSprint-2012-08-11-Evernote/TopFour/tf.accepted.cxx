
#include <iostream>
#include <istream>
#include <ostream>

#include <utility>

using namespace std;

int main()
{
	int tf[4];

	int N, x, k;

	cin >> N;

	k = 0;

	for (; N; --N)
	{
		cin >> x;

		for (int i = 0; i != k; ++i)
		{
			if (x > tf[i])
			{
				swap(x, tf[i]);
			}
		}

		if (k < 4)
		{
			tf[k] = x;
			++k;
		}
	}

	for (int i = 0; i != k; ++i)
	{
		cout << tf[i] << endl;
	}

	return 0;
}

