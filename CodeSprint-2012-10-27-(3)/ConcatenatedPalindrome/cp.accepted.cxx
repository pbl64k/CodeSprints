
#include <iostream>
#include <istream>
#include <ostream>

#include <algorithm>
#include <map>
#include <string>
#include <utility>
#include <vector>

using namespace std;

typedef int mint;

mint n, m;

mint palin(string &s, mint ix)
{
	for (mint i = m - 1; i >= ix; --i)
	{
		bool p = true;

		for (mint j = 0; j <= (i - ix) / 2; ++j)
		{
			if (s[ix + j] != s[i - j])
			{
				p = false;

				break;
			}
		}

		if (p)
		{
			return i - ix + 1;
		}
	}

	// Cannot happen.
	return 0;
}

class st
{
	public:
	map<char, st *> m_;

	st(): m_()
	{
	}

	void addk(string &s, mint ix)
	{
		if (ix == m)
		{
			return;
		}

		if (m_.find(s[ix]) == m_.end())
		{
			m_[s[ix]] = new st();
		}

		m_[s[ix]]->addk(s, ix + 1);
	}

	mint chk(string &s, mint ix)
	{
		if (ix == m)
		{
			return 0;
		}

		if (m_.find(s[ix]) == m_.end())
		{
			return palin(s, ix);
		}

		return 2 + m_[s[ix]]->chk(s, ix + 1);
	}
};

mint check(vector<string> &ts, vector<string> &ms)
{
	st *t = new st();

	for (vector<string>::iterator iter = ts.begin(); iter != ts.end(); ++iter)
	{
		t->addk(*iter, 0);
	}

	mint r = 0;

	for (vector<string>::iterator iter = ms.begin(); iter != ms.end(); ++iter)
	{
		r = max(r, t->chk(*iter, 0));
	}

	return r;
}

int main()
{
	cin >> n >> m;

	string s, rs;

	vector<string> strs(n), rstrs(n);

	for (int i = 0; i != n; ++i)
	{
		cin >> s;

		rs = s;

		reverse(rs.begin(), rs.end());

		strs[i] = s;
		rstrs[i] = rs;
	}

	cout << max(check(strs, rstrs), check(rstrs, strs)) << endl;

	return 0;
}

