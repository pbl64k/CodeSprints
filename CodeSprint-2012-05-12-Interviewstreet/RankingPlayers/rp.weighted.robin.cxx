
int games_per_round = 1;
int max_game_coeff = 100;

vector<int> wins;
vector<list<int> > wins_against;

int score(int p)
{
	int sc = 0;

	for (list<int>::iterator opp_iter = wins_against[p].begin(); opp_iter != wins_against[p].end(); ++opp_iter)
	{
		sc += wins[*opp_iter];
	}

	return sc;
}

bool cmp_weighted_wins(int p1, int p2)
{
	return score(p1) > score(p2);
}

vector<int> game(int nPlayers)
{
	int games = 0;
	int max_games = nPlayers * max_game_coeff;

	wins = vector<int>(nPlayers);
	wins_against = vector<list<int> >(nPlayers);

	vector<int> result;

	for (int i = 0; i != nPlayers; ++i)
	{
		result.push_back(i);
	}

	// initializing the round-robin

	deque<int> side_a;
	deque<int> side_b;

	for (int i = 1; i != nPlayers; ++i)
	{
		if (i % 2 == 1)
		{
			side_a.push_back(i);
		}
		else
		{
			side_b.push_back(i);
		}
	}

	if (side_a.size() > side_b.size())
	{
		side_b.push_front(side_a.back());
		side_a.pop_back();
	}
	else
	{
		side_b.push_back(nPlayers);
	}

	int round = 0;

	while (games < max_games)
	{
		++round;

		//cout << "Round " << round << endl;

		side_a.push_front(0);

		deque<int>::iterator pa = side_a.begin();
		deque<int>::iterator pb = side_b.begin();

		int round_games = 0;

		for (; pb != side_b.end(); ++pa, ++pb)
		{
			int p1 = *pa;
			int p2 = *pb;

			// byes
			if (p1 == nPlayers || p2 == nPlayers)
			{
				continue;
			}

			//cout << "Playing " << min(p1, p2) << " vs " << max(p1, p2) << endl;

			++round_games;

			for (int i = 0; i != games_per_round; ++i)
			{
				++games;

				bool p1_won;

				if (score(p1) >= 25 && (score(p1) >= score(p2) * 2))
				{
					p1_won = true;
				}
				else if (score(p2) >= 25 && (score(p2) >= score(p1) * 2))
				{
					p1_won = false;
				}
				else
				{
					p1_won = gameResult(p1, p2) == p1;
				}

				if (p1_won)
				{
					++wins[p1];
					wins_against[p1].push_front(p2);
				}
				else
				{
					++wins[p2];
					wins_against[p2].push_front(p1);
				}
			}
		}

		side_a.pop_front();

		if (round_games == 0)
		{
			break;
		}

		// ROTAYSHUN!

		side_a.push_front(side_b.front());
		side_b.pop_front();
		side_b.push_back(side_a.back());
		side_a.pop_back();
	}

	sort(result.begin(), result.end(), cmp_weighted_wins);

	return result;
}

