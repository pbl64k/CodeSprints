
#include <iostream>
#include <istream>
#include <ostream>

#include <string>
#include <vector>

using namespace std;

int main()
{
	int N;

	cin >> N;

	vector<string> buf(N);

	int cap = 0, p = 0, q = 0;

	string cmd;

	while (true)
	{
		cin >> cmd;

		if (cmd == "A")
		{
			int n;

			cin >> n;

			getline(cin, cmd);

			for (; n; --n)
			{
				getline(cin, cmd);

				buf[q++] = cmd;

				++cap;

				q = q % N;

				if (cap > N)
				{
					cap -= 1;
					p += 1;
					p = p % N;
				}

				//cout << cap << " " << p << " " << q << endl;
			}
		}
		else if (cmd == "R")
		{
			int n;

			cin >> n;

			n = min(n, cap);

			cap -= n;
			p += n;
			p = p % N;

			//cout << cap << " " << p << " " << q << endl;
		}
		else if (cmd == "L")
		{
			bool frist = true;

			for (int i = p; (frist && (cap > 0)) || (i != q); i = (i + 1) % N)
			{
				frist = false;

				cout << buf[i] << endl;
			}
		}
		else
		{
			break;
		}
	}

	return 0;
}

