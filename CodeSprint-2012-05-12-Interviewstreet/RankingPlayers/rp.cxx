
int games = 4;
double thr = 0.59;
double diff_thr = 0.2;

map<int, map<int, double> > wins;
map<int, map<int, double> > losses;

void mark(map<int, map<int, double> > &tbl, int p1, int p2, double res)
{
	tbl[p1][p2] = res;

	for (map<int, double>::iterator iter = tbl[p2].begin(); iter != tbl[p2].end(); ++iter)
	{
		tbl[p1][iter->first] = max(tbl[p1][iter->first], res * iter->second);
	}
}

int play_n(int n, int p1, int p2)
{
	int w = 0;

	for (int i = 0; i != n; ++i)
	{
		w += gameResult(p1, p2) == p1 ? 1 : 0;
	}

	return w;
}

bool heur(int p1, int p2)
{
	/*
	if (wins[p1][p2] - losses[p1][p2] >= diff_thr && wins[p1][p2] >= thr)
	{
		return true;
	}
	else if (wins[p2][p1] - losses[p2][p1] >= diff_thr && wins[p2][p1] >= thr)
	{
		return false;
	}
	*/

	double res = (0.0 + play_n(games, p1, p2)) / games;

	if (res > 0.5)
	{
		mark(wins, p1, p2, res);
		mark(losses, p2, p1, 1 - res);

		return true;
	}
	else
	{
		mark(wins, p2, p1, 1 - res);
		mark(losses, p1, p2, res);

		return false;
	}
}

void merge_sort(vector<int>::iterator st, vector<int>::iterator fn)
{
	if (fn - st < 2)
	{
		return;
	}

	vector<int>::iterator md = st + ((fn - st) / 2);

	merge_sort(st, md);
	merge_sort(md, fn);

	inplace_merge(st, md, fn, heur);
}

vector<int> game(int nPlayers)
{
	vector<int> res;

	for (int i = 0; i != nPlayers; ++i)
	{
		res.push_back(i);
	}

	make_heap(res.begin(), res.end(), heur);
	sort_heap(res.begin(), res.end(), heur);
	//sort(res.begin(), res.end(), heur);
	//merge_sort(res.begin(), res.end());

	return res;
}

