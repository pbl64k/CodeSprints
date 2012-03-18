
#include <iostream>
#include <istream>
#include <ostream>

#include <map>
#include <set>
#include <vector>

using namespace std;

typedef signed int mint;

class Evt
{
	public:
	mint timestamp_, id_, score_, height_;

	Evt()
	{
	}

	Evt(mint timestamp, mint id, mint score, mint height):
			timestamp_(timestamp), id_(id), score_(score), height_(height)
	{
	}
};

class W
{
	public:
	mint score_, evtNum_;
	set<mint> evts_;

	W():
			score_(0), evtNum_(0)
	{
	}
};

bool operator<(const W &a, const W &b)
{
	if (a.score_ < b.score_)
	{
		return true;
	}
	else if (a.score_ > b.score_)
	{
		return false;
	}
	else
	{
		if (a.evtNum_ > b.evtNum_)
		{
			return true;
		}
		else if (a.evtNum_ < b.evtNum_)
		{
			return false;
		}
		else
		{
			set<mint>::iterator aiter = a.evts_.begin();
			set<mint>::iterator biter = b.evts_.begin();

			while (aiter != a.evts_.end())
			{
				if ((*aiter) > (*biter))
				{
					return true;
				}
				else if ((*aiter) < (*biter))
				{
					return false;
				}

				++aiter;
				++biter;
			}

			return true;
		}
	}
}

class EvtMgr
{
	public:
	mint curId_, timeWindow_, maxHeight_, stId_;
	map<mint, map<mint, W> > *m_;
	vector<Evt> evts_;
	map<mint, mint> ts_;

	EvtMgr(mint timeWindow, mint maxHeight):
			curId_(0), timeWindow_(timeWindow), maxHeight_(maxHeight), stId_(0)
	{
		m_ = new map<mint, map<mint, W> >();
	}

	void addEvt(mint timestamp, mint score, mint height)
	{
		ts_[timestamp] = curId_;
		evts_.push_back(Evt(timestamp, ++curId_, score, height));
	}

	void reload(mint timestamp)
	{
		mint curStId = stId_;

		map<mint, mint>::iterator iter = ts_.lower_bound(timestamp - timeWindow_);

		stId_ = iter->second;

		if (curStId != stId_)
		{
			delete m_;

			m_ = new map<mint, map<mint, W> >();
		}

		W w = m(curId_ - 1, maxHeight_);

		cout << w.score_ << ' ' << w.evtNum_;

		for (set<mint>::iterator witer = w.evts_.begin(); witer != w.evts_.end(); ++witer)
		{
			cout << ' ' << (*witer);
		}

		cout << endl;
	}

	W m(mint id, mint maxHeight)
	{
		if ((id < stId_) || (maxHeight <= 0))
		{
			return W();
		}

		map<mint, map<mint, W> >::iterator fiter = m_->find(id);
		
		if (fiter != m_->end())
		{
			map<mint, W>::iterator siter = fiter->second.find(maxHeight);

			if (siter != fiter->second.end())
			{
				return siter->second;
			}
		}

		if (evts_[id].height_ > maxHeight)
		{
			(*m_)[id][maxHeight] = m(id - 1, maxHeight);
		}
		else
		{
			W w = m(id - 1, maxHeight - evts_[id].height_);

			w.score_ += evts_[id].score_;
			++w.evtNum_;
			w.evts_.insert(evts_[id].id_);

			(*m_)[id][maxHeight] = max(m(id - 1, maxHeight), w);
		}

		return (*m_)[id][maxHeight];
	}
};

int main()
{
	mint numEvents, timeWindow, maxHeight;

	cin >> numEvents >> timeWindow >> maxHeight;

	EvtMgr e(timeWindow, maxHeight);

	char evtCode;

	mint timestamp, score, height;

	for (mint i = 0; i != numEvents; ++i)
	{
		cin >> evtCode;

		if (evtCode == 'S')
		{
			cin >> timestamp >> score >> height;

			e.addEvt(timestamp, score, height);
		}
		else
		{
			cin >> timestamp;

			e.reload(timestamp);
		}
	}

	return 0;
}

