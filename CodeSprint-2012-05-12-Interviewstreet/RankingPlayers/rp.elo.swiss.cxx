
map<int, pair<double, int> > rating;

double def_rating = 1500.0;
double var = 400.0;
double K = 30.0;
int games_per_round = 1;
int max_game_coeff = 7;
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

	int round = 0;

	while (games < max_games)
	{
		++round;

		sort(result.begin(), result.end(), cmp_rating);

		//cout << "Round " << round << endl;

		int round_games = 0;

		list<int> players(result.begin(), result.end());

		while (players.begin() != players.end())
		{
			int p1 = players.front();

			players.pop_front();

			// bye

			if (players.begin() == players.end())
			{
				break;
			}

			int p2 = players.front();

			players.pop_front();

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

		if (round_games == 0)
		{
			break;
		}
	}

	sort(result.begin(), result.end(), cmp_rating);

	return result;
}

