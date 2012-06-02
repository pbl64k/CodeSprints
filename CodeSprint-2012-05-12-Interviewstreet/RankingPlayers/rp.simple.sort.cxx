
int cnt = 0;
int limit = 0;

map<pair<int, int>, bool> memo_w;

bool win_n(int n, int p1, int p2)
{
	if (cnt >= limit)
	{
		return true;
	}

	++cnt;

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

void crude_sort(vector<int>::iterator st, vector<int>::iterator fn)
{
	if (fn - st < 2)
	{
		return;
	}

	bool f = (fn - st) > 4;

	vector<int>::iterator orig_st = st;
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
	for (vector<int>::iterator iter = st + 1; iter != fn; ++iter)
	{
		if (memo_win_sm(f, *iter, *st))
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
	limit = 100 * nPlayers;

	vector<int> res;

	for (int i = 0; i != nPlayers; ++i)
	{
		res.push_back(i);
	}

	//make_heap(res.begin(), res.end(), memo_win_3);
	//sort_heap(res.begin(), res.end(), memo_win_3);
	//sort(res.begin(), res.end(), memo_win_3);
	crude_sort(res.begin(), res.end());

	return res;
}

