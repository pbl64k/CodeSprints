
map<pair<int, int>, bool> memoR;
vector<int> wins;
map<pair<int, int>, bool> played;

int gNPlayers;

bool xWins(int w, int p1, int p2)
{
	int w1 = 0;
	int w2 = 0;

	/*
	while (abs(w1 - w2) < w && w1 < (w + 1) && w2 < (w + 1))
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
	*/
	while (w1 < w && w2 < w)
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

bool xWinsMemo(int w, int p1, int p2)
{
	if (memoR.find(pair<int, int>(p1, p2)) != memoR.end())
	{
		return memoR[pair<int, int>(p1, p2)];
	}

	bool res = xWins(w, p1, p2);

	memoR[pair<int, int>(p1, p2)] = res;
	memoR[pair<int, int>(p2, p1)] = !res;

	return res;
}

bool xWins1StepMemo(int w, int p1, int p2)
{
	//cout << p1 << " " << p2 << endl;
	if (memoR.find(pair<int, int>(p1, p2)) != memoR.end())
	{
		return memoR[pair<int, int>(p1, p2)];
	}
	
	for (int ii = 0; ii != gNPlayers; ++ii)
	{
		//cout << ii << endl;
		if (memoR.find(pair<int, int>(p1, ii)) != memoR.end() && memoR.find(pair<int, int>(ii, p2)) != memoR.end())
		{
			if (memoR[pair<int, int>(p1, ii)] == memoR[pair<int, int>(ii, p2)])
			{
				bool res = memoR[pair<int, int>(p1, ii)];

				memoR[pair<int, int>(p1, p2)] = res;
				memoR[pair<int, int>(p2, p1)] = !res;

				/*
				for (int jj = 0; jj != gNPlayers; ++jj)
				{
					if (memoR.find(pair<int, int>(p2, jj)) != memoR.end())
					{
						if (memoR[pair<int, int>(p2, jj)] == res)
						{
							memoR[pair<int, int>(p1, jj)] = res;
							memoR[pair<int, int>(jj, p1)] = !res;
						}
					}
				}
				*/

				return res;
			}
		}
	}

	bool res = xWins(w, p1, p2);

	memoR[pair<int, int>(p1, p2)] = res;
	memoR[pair<int, int>(p2, p1)] = !res;

	/*
	for (int jj = 0; jj != gNPlayers; ++jj)
	{
		if (memoR.find(pair<int, int>(p2, jj)) != memoR.end())
		{
			if (memoR[pair<int, int>(p2, jj)] == res)
			{
				memoR[pair<int, int>(p1, jj)] = res;
				memoR[pair<int, int>(jj, p1)] = !res;
			}
		}
	}
	*/

	return res;
}

bool bestOfOne(int p1, int p2)
{
	return xWins(1, p1, p2);
}

bool bestOfThree(int p1, int p2)
{
	return xWins(2, p1, p2);
}

bool bestOfMemo(int p1, int p2)
{
	return xWinsMemo(3, p1, p2);
}

bool best1Step(int p1, int p2)
{
	return xWins1StepMemo(3, p1, p2);
}

bool bestWins(int p1, int p2)
{
	return wins[p1] > wins[p2];
}

void rrBot(int i, int j)
{
	if (bestOfMemo(i, j))
	{
		++wins[i];
	}
	else
	{
		++wins[j];
	}
}

void rrMulti(int n, int i, int j)
{
	for (int cnt = 0; cnt != n; ++cnt)
	{
		if (gameResult(i, j) == i)
		{
			++wins[i];
		}
		else
		{
			++wins[j];
		}
	}
}

void rrMultiCheat(int nPlayers, int round, int n, int i, int j)
{
	nPlayers = nPlayers;
	if (round > 4) //(round >= nPlayers / 9)
	{
		/*
		if ((wins[i] >= ((2 * round) / 3)) && (wins[j] <= (round / 3)))
		{
			wins[i] += n;
			return;
		}
		else if ((wins[j] >= ((2 * round) / 3)) && (wins[i] <= (round / 3)))
		{
			wins[j] += n;
			return;
		}
		*/
		if (((wins[i] - wins[j]) > (round / 24)) && ((wins[i] - wins[j]) > 3))
		{
			wins[i] += n;
			return;
		}
		else if (((wins[j] - wins[i]) > (round / 24)) && ((wins[j] - wins[i]) > 3))
		{
			wins[j] += n;
			return;
		}
	}

	rrMulti(n, i, j);
}

void rrStep(int i, int j)
{
	if (best1Step(i, j))
	{
		++wins[i];
	}
	else
	{
		++wins[j];
	}
}

vector<int> gameRoundRobin(int nPlayers)
{
	vector<int> res;

	gNPlayers = nPlayers;

	for (int i = 0; i != nPlayers; ++i)
	{
		res.push_back(i);
	}

	wins = vector<int>(nPlayers);

	/*
	for (int i = 0; i != nPlayers; ++i)
	{
		for (int j = i + 1; j != nPlayers; ++j)
		{
			// Best-of-three round robin
			//rrBot(i, j);
			// Double round robin
			rrMulti(2, i, j);
			// Single round robin
			//rrMulti(1, i, j);
		}
	}
	*/

	deque<int> sideA;
	deque<int> sideB;

	for (int i = 1; i != nPlayers; ++i)
	{
		if (i % 2 == 1)
		{
			sideA.push_back(i);
		}
		else
		{
			sideB.push_back(i);
		}
	}

	if (sideA.size() > sideB.size())
	{
		sideB.push_front(sideA.back());
		sideA.pop_back();
	}
	else
	{
		sideB.push_back(nPlayers);
	}

	//random_shuffle(sideA.begin(), sideA.end());
	//random_shuffle(sideB.begin(), sideB.end());

	for (int round = 0; round != ((nPlayers - 1) + (nPlayers % 2)); ++round)
	{
		sideA.push_front(0);

		deque<int>::iterator pa = sideA.begin();
		deque<int>::iterator pb = sideB.begin();

		while (pb != sideB.end())
		{
			int i = *pa;
			int j = *pb;
			//cout << "Playing " << min(i, j) << " vs " << max(i, j) << endl;

			// byes for double rr
			if (i == nPlayers)
			{
				//wins[j] += 2;
				wins[j] += 1;
				++pa; ++pb;
				continue;
			}
			else if (j == nPlayers)
			{
				//wins[i] += 2;
				wins[i] += 1;
				++pa; ++pb;
				continue;
			}

			// Best-of-three round robin
			//rrBot(i, j);
			// Double round robin
			//rrMulti(2, i, j);
			// Single round robin
			//rrMulti(1, i, j);
			// Multiple round robin with cheats
			//rrMultiCheat(nPlayers, round, 2, i, j);
			rrMultiCheat(nPlayers, round, 1, i, j);
			//rrStep(i, j);

			++pa;
			++pb;
		}

		sideA.pop_front();

		// ROTAYSHUN!

		sideA.push_front(sideB.front());
		sideB.pop_front();
		sideB.push_back(sideA.back());
		sideA.pop_back();
	}

	/*
	for (int i = 0; i != nPlayers; ++i)
	{
		cout << "Player " << i << " won " << wins[i] << " times." << endl;
	}
	*/

	//sort(res.begin(), res.end(), bestOfMemo);
	sort(res.begin(), res.end(), bestWins);

	return res;
}

vector<int> gameSwiss(int nPlayers)
{
	gNPlayers = nPlayers;

	vector<int> res;

	//int rounds = 20;
	//int rounds = 100;
	int rounds = (nPlayers - 1) + (nPlayers % 2);

	for (int i = 0; i != nPlayers; ++i)
	{
		res.push_back(i);
	}

	wins = vector<int>(nPlayers);

	for (int round = 0; round != rounds; ++round)
	{
		//cout << "Round " << (round + 1) << endl;
		sort(res.begin(), res.end(), bestWins);

		/*
		for (vector<int>::iterator res_iter = res.begin(); res_iter != res.end(); ++res_iter)
		{
			cout << (*res_iter) << ":" << wins[*res_iter] << " ";
		}
		cout << endl;
		*/

		list<int> ps(res.begin(), res.end());

		while (ps.begin() != ps.end())
		{
			int p1 = ps.front();
			ps.pop_front();

			int p2 = -1;

			//cout << "Player 1 is " << p1 << endl;
			for (list<int>::iterator ps_iter = ps.begin(); ps_iter != ps.end(); ++ps_iter)
			{
				if (played.find(pair<int, int>(p1, *ps_iter)) == played.end())
				{
					p2 = *ps_iter;
					ps.erase(ps_iter);
					break;
				}
			}

			if (p2 == -1)
			{
				// bye
				wins[p1] += 1;
			}
			else
			{
				//cout << "Playing " << p1 << " vs " << p2 << endl;
				//rrMultiCheat(nPlayers, round, 2, p1, p2);
				rrStep(p1, p2);
				played[pair<int, int>(p1, p2)] = true;
				played[pair<int, int>(p2, p1)] = true;
			}
		}
	}

	return res;
}

vector<int> gameSort(int nPlayers)
{
	vector<int> res;

	for (int i = 0; i != nPlayers; ++i)
	{
		res.push_back(i);
	}

	gNPlayers = nPlayers;

	//random_shuffle(res.begin(), res.end());
	sort(res.begin(), res.end(), best1Step);

	return res;
}

vector<int> game(int nPlayers)
{
	//return gameSort(nPlayers);
	//return gameSwiss(nPlayers);
	return gameRoundRobin(nPlayers);
}

