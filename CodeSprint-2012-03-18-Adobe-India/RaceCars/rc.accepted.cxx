
#include <iostream>
#include <istream>
#include <ostream>

#include <cmath>
#include <deque>
#include <map>
#include <utility>

using namespace std;

typedef signed long long mint;

typedef mint speed;
typedef mint position;
//typedef double fine_pos;
typedef signed int number;

template<typename T> T signum(T a)
{
	return abs(a) / a;
}

class fine_pos
{
	public:
	mint num_, den_;

	fine_pos(): num_(0), den_(1)
	{
	}

	fine_pos(mint num, mint den): num_(num * signum(den)), den_(abs(den))
	{
	}

	bool operator<(const fine_pos &b)
	{
		return num_ * b.den_ < b.num_ * den_;
	}

	bool operator<=(const fine_pos &b)
	{
		return num_ * b.den_ <= b.num_ * den_;
	}
};

map<speed, pair<position, number> *> speeds;

inline fine_pos solve(speed a1, position b1, speed a2, position b2)
{
	//cout << "a1 " << a1 << " b1 " << b1 << " a2 " << a2 << " b2 " << b2 << endl;
	//cout << "numer " << (b2 - b1) << endl;
	//cout << "denom " << (a1 - a2) << endl;
	//cout << "Intersect! " << ((b2 - b1) / (a1 - a2)) << endl;
	return fine_pos(b2 - b1, a1 - a2);
}

class cnt
{
	public:
	fine_pos pl_, pr_;
	position pos_;
	speed sp_;
	number n_;

	cnt(): pl_(0, 1), pr_(0, 1), pos_(0), sp_(0), n_(0)
	{
	}

	cnt(fine_pos pl, fine_pos pr, position pos, speed sp, number n):
			pl_(pl), pr_(pr), pos_(pos), sp_(sp), n_(n)
	{
	}
};

deque<cnt> conts;

int main()
{
	number N;

	cin >> N;

	position pos;
	speed sp;

	map<speed, pair<position, number> *>::iterator speeds_iter;
	map<speed, pair<position, number> *>::reverse_iterator speeds_riter;

	for (; N; --N)
	{
		cin >> pos;
		cin >> sp;

		if ((speeds_iter = speeds.find(sp)) == speeds.end())
		{
			pair<position, number> *p = new pair<position, number>(pos, 1);

			speeds[sp] = p;
		}
		else
		{
			if (speeds_iter->second->first < pos)
			{
				speeds_iter->second->first = pos;
				speeds_iter->second->second = 1;
			}
			else if (speeds_iter->second->first == pos)
			{
				++(speeds_iter->second->second);
			}
		}
	}

	/*
	for (speeds_riter = speeds.rbegin(); speeds_riter != speeds.rend(); ++speeds_riter)
	{
		cout << speeds_riter->first << ' ' << speeds_riter->second->first << ' ' << speeds_riter->second->second << endl;
	}
	*/

	speeds_riter = speeds.rbegin();

	conts.push_front(cnt(fine_pos(0, 1), fine_pos(10000000, 1), speeds_riter->second->first, speeds_riter->first, speeds_riter->second->second));

	++speeds_riter;

	deque<cnt>::iterator conts_iter;

	fine_pos intersect;

	for (; speeds_riter != speeds.rend(); ++speeds_riter)
	{
		for (conts_iter = conts.begin(); conts_iter != conts.end(); ++conts_iter)
		{
			intersect = solve(speeds_riter->first, speeds_riter->second->first, conts_iter->sp_, conts_iter->pos_);

			if (conts_iter->pr_ < intersect)
			{
				continue;
			}
			else if ((conts_iter->pl_ <= intersect) && (intersect <= conts_iter->pr_))
			{
				cnt old = (*conts_iter);

				conts.erase(conts.begin(), ++conts_iter);

				conts.push_front(cnt(intersect, old.pr_, old.pos_, old.sp_, old.n_));
				conts.push_front(cnt(fine_pos(0, 1), intersect, speeds_riter->second->first, speeds_riter->first, speeds_riter->second->second));

				//cout << "bloirng! " << conts.size() << endl;
				break;
			}
			/*
			else
			{
				cout << "I: " << intersect << " l: " << conts_iter->second.pl_ << " delta: " << (intersect - conts_iter->second.pl_) << " Y: " << ((intersect - conts_iter->second.pl_) >= -1e-12) << endl;
			}
			*/
		}
	}

	number result = 0;

	for (conts_iter = conts.begin(); conts_iter != conts.end(); ++conts_iter)
	{
		result += conts_iter->n_;
	}

	cout << result << endl;

	return 0;
}

