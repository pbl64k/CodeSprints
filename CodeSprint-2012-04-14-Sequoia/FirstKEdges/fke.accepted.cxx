
#include <iostream>
#include <istream>
#include <ostream>

#include <utility>
#include <vector>

using namespace std;

int main()
{
	int N, M;

	cin >> N >> M;

	vector<vector<int>> cluster(N);
	vector<int> node(N);

	int i;

	for (i = 0; i != N; ++i)
	{
		cluster[i].push_back(i);
		node[i] = i;
	}

	vector<pair<int, int>> edges(M);

	int from, to;

	for (i = 0; i != M; ++i)
	{
		cin >> from >> to;

		edges[i] = pair<int, int>(from, to);
	}

	int clusters = N;
	vector<int> answers;

	answers.push_back(clusters);

	for (vector<pair<int, int>>::reverse_iterator edge_iter = edges.rbegin(); edge_iter != edges.rend() - 1; ++edge_iter)
	{
		from = edge_iter->first;
		to = edge_iter->second;

		if (node[from] != node[to])
		{
			--clusters;

			vector<int> &old_cluster = cluster[node[to]];

			for (vector<int>::iterator n_iter = old_cluster.begin(); n_iter != old_cluster.end(); ++n_iter)
			{
				cluster[node[from]].push_back(*n_iter);
				node[*n_iter] = node[from];
			}
		}

		answers.push_back(clusters);
	}

	for (vector<int>::reverse_iterator answ_iter = answers.rbegin(); answ_iter != answers.rend(); ++answ_iter)
	{
		cout << (*answ_iter) << endl;
	}

	return 0;
}

