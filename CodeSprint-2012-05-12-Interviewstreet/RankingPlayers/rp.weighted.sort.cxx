
bool w_sc = true;
int n_g = 2;
int g_thr = 15;
double thr = 1.75;

map<pair<int, int>, bool> memo_w;

vector<int> wins;
vector<int> games;
vector<list<int> > wins_against;

double score(int p, bool weighted)
{
	if (games[p] == 0)
	{
		return 0;
	}

	int sc = 0;

	for (list<int>::iterator opp_iter = wins_against[p].begin(); opp_iter != wins_against[p].end(); ++opp_iter)
	{
		sc += (weighted ? wins[*opp_iter] : 0) + 1; // winning against winless opponents is still worth something
	}

	return (0.0 + sc) / games[p];
}

bool win_n(int n, int p1, int p2)
{
	int w1 = 0;
	int w2 = 0;

	while (w1 < n && w2 < n)
	{
		++games[p1];
		++games[p2];

		if (gameResult(p1, p2) == p1)
		{
			++w1;
			++wins[p1];
			wins_against[p1].push_front(p2);
		}
		else
		{
			++w2;
			++wins[p2];
			wins_against[p2].push_front(p1);
		}
	}

	return w1 > w2;
}

bool win_1(int p1, int p2)
{
	return win_n(1, p1, p2);
}

bool win_2(int p1, int p2)
{
	return win_n(2, p1, p2);
}

bool win_3(int p1, int p2)
{
	return win_n(3, p1, p2);
}

bool memo_win_1(int p1, int p2)
{
	if (memo_w.find(make_pair(p1, p2)) == memo_w.end())
	{
		bool outcome = win_1(p1, p2);

		memo_w[make_pair(p1, p2)] = outcome;
		memo_w[make_pair(p2, p1)] = !outcome;
	}

	return memo_w[make_pair(p1, p2)];
}

bool memo_win_2(int p1, int p2)
{
	if (memo_w.find(make_pair(p1, p2)) == memo_w.end())
	{
		bool outcome = win_2(p1, p2);

		memo_w[make_pair(p1, p2)] = outcome;
		memo_w[make_pair(p2, p1)] = !outcome;
	}

	return memo_w[make_pair(p1, p2)];
}

bool memo_win_3(int p1, int p2)
{
	if (memo_w.find(make_pair(p1, p2)) == memo_w.end())
	{
		bool outcome = win_3(p1, p2);

		memo_w[make_pair(p1, p2)] = outcome;
		memo_w[make_pair(p2, p1)] = !outcome;
	}

	return memo_w[make_pair(p1, p2)];
}

bool memo_win_sm(bool t, int p1, int p2)
{
	if (t)
	{
		return memo_win_3(p1, p2);
	}
	else
	{
		return memo_win_2(p1, p2);
	}
}

bool win_acc(int p1, int p2)
{
	if (games[p1] >= g_thr && games[p2] >= g_thr)
	{
		double sc1 = score(p1, w_sc);
		double sc2 = score(p2, w_sc);

		if (sc1 / sc2 >= thr)
		{
			return true;
		}

		if (sc2 / sc1 >= thr)
		{
			return false;
		}
	}

	return win_n(n_g, p1, p2);
}

bool memo_win_acc(int p1, int p2)
{
	if (memo_w.find(make_pair(p1, p2)) == memo_w.end())
	{
		bool outcome = win_acc(p1, p2);

		memo_w[make_pair(p1, p2)] = outcome;
		memo_w[make_pair(p2, p1)] = !outcome;
	}

	return memo_w[make_pair(p1, p2)];
}

void crude_sort(vector<int>::iterator st, vector<int>::iterator fn)
{
	if (fn - st < 2)
	{
		return;
	}

	bool f = (fn - st) > 2;
	n_g = f ? 3 : 2;

	vector<int>::iterator orig_st = st;
	vector<int>::iterator ls = fn - 1;

	// pick a pivot
	vector<int>::iterator md = st + ((fn - st) / 2);

	bool st_md = memo_win_acc(*st, *md);
	bool md_ls = memo_win_acc(*md, *ls);

	if (st_md && md_ls) // st > md > ls
	{
		swap(*st, *md);
	}
	else if (!st_md && md_ls) // st < md > ls
	{
		if (memo_win_acc(*ls, *st)) // st < ls < md
		{
			swap(*ls, *st);
		}
	}
	else if (st_md && !md_ls) // st > md < ls
	{
		if (memo_win_acc(*st, *ls)) // st > ls > md
		{
			swap(*ls, *st);
		}
	}
	else // st < md < ls
	{
		swap(*st, *md);
	}

	// partition
	for (vector<int>::iterator iter = st + 1; iter != fn; ++iter)
	{
		if (memo_win_acc(*iter, *st))
		{
			swap(*iter, *st);
			++st;
			swap(*iter, *st);
		}
	}

	/*
	cout << "Pivot: " << (*st) << endl;
	for (vector<int>::iterator iter = orig_st; iter != fn; ++iter)
	{
		cout << (*iter) << " ";
	}
	cout << endl;
	*/

	// recursion
	crude_sort(orig_st, st);
	crude_sort(st + 1, fn);
}

vector<int> game(int nPlayers)
{
	vector<int> res;

	wins = vector<int>(nPlayers);
	games = vector<int>(nPlayers);
	wins_against = vector<list<int> >(nPlayers);

	for (int i = 0; i != nPlayers; ++i)
	{
		res.push_back(i);
	}

	//make_heap(res.begin(), res.end(), memo_win_acc);
	//sort_heap(res.begin(), res.end(), memo_win_acc);
	//sort(res.begin(), res.end(), memo_win_acc);
	crude_sort(res.begin(), res.end());

	return res;
}

