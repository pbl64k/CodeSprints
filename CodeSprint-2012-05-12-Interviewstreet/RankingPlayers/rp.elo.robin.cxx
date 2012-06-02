
map<int, pair<double, int> > rating;

double def_rating = 1500.0;
double var = 400.0;
double K = 50.0;
int games_per_round = 3;
int max_game_coeff = 15;
double overkill_threshold = 0.95;

double expect(double r1, double r2)
{
	return 1.0 / (1.0 + pow(10.0, ((r2 - r1) / var)));
}

bool cmp_rating(int p1, int p2)
{
	return rating[p1].first > rating[p2].first;
}

vector<int> game(int nPlayers)
{
	int games = 0;
	int max_games = nPlayers * max_game_coeff;

	vector<int> result;

	for (int i = 0; i != nPlayers; ++i)
	{
		result.push_back(i);
		rating[i] = make_pair(def_rating, 0);
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

			double rt1 = rating[p1].first;
			double rt2 = rating[p2].first;

			double E1 = (0.0 + games_per_round) * expect(rt1, rt2);
			double E2 = (0.0 + games_per_round) - E1;

			if (E1 > (0.0 + games_per_round) * overkill_threshold || E2 > (0.0 + games_per_round) * overkill_threshold)
			{
				continue;
			}

			//cout << "Playing " << min(p1, p2) << " (" << rating[min(p1, p2)].first << ") vs " << max(p1, p2) << " (" << rating[max(p1, p2)].first << ")" << endl;

			++round_games;

			++rating[p1].second;
			++rating[p2].second;

			double pts1 = 0;

			for (int jj = 0; jj != games_per_round; ++jj)
			{
				++games;

				pts1 += (gameResult(p1, p2) == p1) ? 1.0 : 0.0;
			}

			double pts2 = (0.0 + games_per_round) - pts1;

			rating[p1].first += K * (pts1 - E1);
			rating[p2].first += K * (pts2 - E2);
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

	sort(result.begin(), result.end(), cmp_rating);

	return result;
}

