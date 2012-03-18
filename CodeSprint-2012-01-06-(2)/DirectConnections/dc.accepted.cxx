
#include <algorithm>
#include <map>

#include <iostream>
#include <istream>
#include <ostream>

using namespace std;

#define M 1000000007LL

typedef long long mint;

class any_node
{
	public:

	mint min_x_, max_x_;

	mint cities_;
	mint dist_l_, dist_r_;

	any_node(mint min_x, mint max_x, mint cities, mint dist_l, mint dist_r): min_x_(min_x), max_x_(max_x), cities_(cities), dist_l_(dist_l), dist_r_(dist_r)
	{
	}

	virtual ~any_node()
	{
	}

	virtual any_node *ins(any_node *l) = 0;
	virtual any_node *drop(mint x) = 0;
	virtual mint part(mint x) = 0;
	virtual bool in(mint x) = 0;
};

class node : public any_node
{
	public:

	bool banzai_;

	any_node *left_;
	any_node *right_;

	node(any_node *l, any_node *r): any_node(min(l->min_x_, r->min_x_), max(l->max_x_, r->max_x_), 0, 0, 0), banzai_(true)
	{
		if (l->max_x_ < r->min_x_)
		{
			left_ = l;
			right_ = r;
		}
		else
		{
			left_ = r;
			right_ = l;
		}

		cities_ = r->cities_ + l->cities_;
		//dist_ = (((((((l->cities_ * r->cities_) % M) * (r->min_x_ - l->max_x_)) % M) + l->dist_) % M) + r->dist_) % M;
		dist_l_ = (((left_->dist_l_ + right_->dist_l_) % M) + (((right_->min_x_ - left_->min_x_) * right_->cities_) % M)) % M;
		dist_r_ = (((left_->dist_r_ + right_->dist_r_) % M) + (((right_->max_x_ - left_->max_x_) * left_->cities_) % M)) % M;
	}

	virtual ~node()
	{
		if (banzai_)
		{
			delete left_;
			delete right_;
		}
	}

	virtual any_node *ins(any_node *l)
	{
		if (left_->max_x_ > l->min_x_)
		{
			left_ = left_->ins(l);
		}
		else if (right_->min_x_ < l->max_x_)
		{
			right_ = right_->ins(l);
		}
		else
		{
			left_ = left_->ins(l);
		}

		min_x_ = min(left_->min_x_, right_->min_x_);
		max_x_ = max(left_->max_x_, right_->max_x_);
		cities_ = right_->cities_ + left_->cities_;
		//dist_ = (((((((left_->cities_ * right_->cities_) % M) * (right_->min_x_ - left_->max_x_)) % M) + right_->dist_) % M) + left_->dist_) % M;
		dist_l_ = (((left_->dist_l_ + right_->dist_l_) % M) + (((right_->min_x_ - left_->min_x_) * right_->cities_) % M)) % M;
		dist_r_ = (((left_->dist_r_ + right_->dist_r_) % M) + (((right_->max_x_ - left_->max_x_) * left_->cities_) % M)) % M;

		return this;
	}

	virtual any_node *drop(mint x)
	{
		if ((max_x_ < x) || (min_x_ > x))
		{
			return this;
		}

		left_ = left_->drop(x);
		right_ = right_->drop(x);

		banzai_ = false;

		if ((left_ == NULL) && (right_ == NULL))
		{
			delete this;

			return NULL;
		}
		else if ((left_ == NULL) && (right_ != NULL))
		{
			delete this;

			return right_;
		}
		else if ((left_ != NULL) && (right_ == NULL))
		{
			delete this;

			return left_;
		}
		else
		{
			min_x_ = min(left_->min_x_, right_->min_x_);
			max_x_ = max(left_->max_x_, right_->max_x_);
			cities_ = right_->cities_ + left_->cities_;
			//dist_ = (((((((left_->cities_ * right_->cities_) % M) * (right_->min_x_ - left_->max_x_)) % M) + right_->dist_) % M) + left_->dist_) % M;
			dist_l_ = (((left_->dist_l_ + right_->dist_l_) % M) + (((right_->min_x_ - left_->min_x_) * right_->cities_) % M)) % M;
			dist_r_ = (((left_->dist_r_ + right_->dist_r_) % M) + (((right_->max_x_ - left_->max_x_) * left_->cities_) % M)) % M;

			banzai_ = true;

			return this;
		}
	}

	virtual mint part(mint x)
	{
		mint left_part, right_part;

		if (left_->in(x))
		{
			left_part = left_->part(x);
		}
		else
		{
			if (x < left_->min_x_)
			{
				left_part = ((((left_->min_x_ - x) * left_->cities_) % M) + left_->dist_l_) % M;
			}
			else
			{
				left_part = ((((x - left_->max_x_) * left_->cities_) % M) + left_->dist_r_) % M;
			}
		}

		if (right_->in(x))
		{
			right_part = right_->part(x);
		}
		else
		{
			if (x < right_->min_x_)
			{
				right_part = ((((right_->min_x_ - x) * right_->cities_) % M) + right_->dist_l_) % M;
			}
			else
			{
				right_part = ((((x - right_->max_x_) * right_->cities_) % M) + right_->dist_r_) % M;
			}
		}

		return left_part + right_part % M;
	}

	virtual bool in(mint x)
	{
		return (min_x_ <= x) && (x <= max_x_);
	}
};

class leaf : public any_node
{
	public:

	leaf(mint x): any_node(x, x, 1, 0, 0)
	{
	}

	virtual ~leaf()
	{
	}

	virtual any_node *ins(any_node *l)
	{
		return new node(this, l);
	}

	virtual any_node *drop(mint x)
	{
		if (min_x_ == x)
		{
			delete this;

			return NULL;
		}

		return this;
	}

	virtual mint part(mint x)
	{
		if (x > max_x_)
		{
			return x - max_x_;
		}

		return min_x_ - x;
	}

	virtual bool in(mint x)
	{
		return x == max_x_;
	}
};

class tree
{
	public:

	any_node *root_;

	tree(): root_(NULL)
	{
	}

	~tree()
	{
		if (root_ != NULL)
		{
			delete root_;
		}
	}

	void ins(mint x)
	{
		leaf *nl = new leaf(x);

		if (root_ == NULL)
		{
			root_ = nl;

			return;
		}

		root_ = root_->ins(nl);
	}

	void drop(mint x)
	{
		/*
		if (root_ == NULL)
		{
			return;
		}
		*/

		root_ = root_->drop(x);
	}

	mint part(mint x)
	{
		if (root_ == NULL)
		{
			return 0;
		}

		return root_->part(x);
	}
};

int main()
{
	mint t;

	cin >> t;

	for (; t; --t)
	{
		mint n;

		cin >> n;

		mint *x = new mint[n];
		mint *p = new mint[n];

		for (mint i = 0; i != n; ++i)
		{
			cin >> x[i];
		}

		for (mint i = 0; i != n; ++i)
		{
			cin >> p[i];
		}

		tree coord;
		map<pair<mint, mint>, mint> pop;

		for (mint i = 0; i != n; ++i)
		{
			pair<mint, mint> key(p[i], 0);
			
			map<pair<mint, mint>, mint>::iterator k;

			while ((k = pop.find(key)) != pop.end())
			{
				++key.second;
			}

			pop[key] = x[i];

			coord.ins(x[i]);
		}

		mint total = 0;

		for (map<pair<mint, mint>, mint>::reverse_iterator i = pop.rbegin(); i != pop.rend(); ++i)
		{
			coord.drop(i->second);

			total = (((coord.part(i->second) * (i->first).first) % M) + total) % M;
		}

		cout << total << endl;

		delete[] x;
		delete[] p;
	}

	return 0;
}

