
map<pair<int, int>, bool> memo_w;

bool win_n(int n, int p1, int p2)
{
	int w1 = 0;
	int w2 = 0;

	while (w1 < n && w2 < n)
	{
		if (gameResult(p1, p2) == p1)
		{
			++w1;
		}
		else
		{
			++w2;
		}
	}

	return w1 > w2;
}

bool win_2(int p1, int p2)
{
	return win_n(2, p1, p2);
}

bool win_3(int p1, int p2)
{
	return win_n(3, p1, p2);
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

void cleva_sort(int n, vector<int>::iterator st, vector<int>::iterator fn)
{
	if (fn - st < 2)
	{
		return;
	}

	//cout << (fn - st) << endl;

	//bool f = (fn - st) > 4;
	bool f = true;

	vector<vector<int>> parts(n + 1);

	vector<int>::iterator ls = fn - 1;

	// pick a pivot
	vector<int>::iterator md = st + ((fn - st) / 2);

	bool st_md = memo_win_sm(f, *st, *md);
	bool md_ls = memo_win_sm(f, *md, *ls);

	if (st_md && md_ls) // st > md > ls
	{
		swap(*st, *md);
	}
	else if (!st_md && md_ls) // st < md > ls
	{
		if (memo_win_sm(f, *ls, *st)) // st < ls < md
		{
			swap(*ls, *st);
		}
	}
	else if (st_md && !md_ls) // st > md < ls
	{
		if (memo_win_sm(f, *st, *ls)) // st > ls > md
		{
			swap(*ls, *st);
		}
	}
	else // st < md < ls
	{
		swap(*st, *md);
	}

	// partition
	parts[n / 2].push_back(*st);

	for (vector<int>::iterator iter = st + 1; iter != fn; ++iter)
	{
		int wins = 0;

		for (int i = 0; i != n; ++i)
		{
			if (gameResult(*iter, *st) == (*iter))
			{
				++wins;
			}
		}

		parts[n - wins].push_back(*iter);
	}

	// recursion
	for (int i = 0; i <= n; ++i)
	{
		cleva_sort(n, parts[i].begin(), parts[i].end());
	}

	//merge
	for (int i = 0; i <= n; ++i)
	{
		st = copy(parts[i].begin(), parts[i].end(), st);
	}
}

vector<int> game(int nPlayers)
{
	vector<int> res;

	for (int i = 0; i != nPlayers; ++i)
	{
		res.push_back(i);
	}

	//make_heap(res.begin(), res.end(), memo_win_3);
	//sort_heap(res.begin(), res.end(), memo_win_3);
	//sort(res.begin(), res.end(), memo_win_3);
	cleva_sort(2, res.begin(), res.end());

	return res;
}

