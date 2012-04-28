
#include <iostream>
#include <istream>
#include <ostream>

#include <utility>

using namespace std;

template<typename T> class heap
{
	public:
	signed int n_, i_;
	T *h_;

	heap(signed int n): n_(n), i_(0), h_(new T[n_])
	{
	}

	virtual ~heap()
	{
		delete[] h_;
	}

	void insert(T x)
	{
		signed int i = i_;

		h_[i_++] = x;

		signed int p;

		while (i > 0)
		{
			p = parent(i);

			if (h_[i] < h_[p])
			{
				swap(h_[i], h_[p]);

				i = p;
			}
			else
			{
				break;
			}
		}
	}

	T extract()
	{
		T res = h_[0];

		--i_;

		if (i_ > 0)
		{
			swap(h_[0], h_[i_]);

			signed int i = 0;

			while (true)
			{
				signed int l = lchild(i);
				signed int r = rchild(i);

				if (l > (i_ - 1) || (r > (i_ - 1) && h_[l] >= h_[i]) || (h_[l] >= h_[i] && h_[r] >= h_[i]))
				{
					break;
				}

				if (r > (i_ - 1))
				{
					swap(h_[i], h_[l]);

					i = l;

					continue;
				}

				if (h_[l] < h_[r])
				{
					swap(h_[i], h_[l]);

					i = l;
				}
				else
				{
					swap(h_[i], h_[r]);

					i = r;
				}
			}
		}

		return res;
	}

	signed int lchild(signed int i)
	{
		return i * 2 + 1;
	}

	signed int rchild(signed int i)
	{
		return i * 2 + 2;
	}

	signed int parent(signed int i)
	{
		return (i - 1) / 2;
	}
};

int main()
{
	size_t N;

	cin >> N;

	heap<long long> h(N);

	long long w;

	for (; N; --N)
	{
		cin >> w;

		h.insert(w);
	}

	long long eff = 0;

	while (h.i_ > 1)
	{
		long long a, b, r;

		a = h.extract();
		b = h.extract();

		r = a + b;

		h.insert(r);

		eff += r;
	}

	cout << eff << endl;

	return 0;
}

