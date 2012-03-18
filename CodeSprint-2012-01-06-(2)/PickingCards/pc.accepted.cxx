
#include <map>
#include <utility>

#include <iostream>
#include <istream>
#include <ostream>

using namespace std;

#define M 1000000007LL

typedef long long mint;

mint cc(mint n, map<mint, mint> &freqs)
{
    mint res = 1;
    mint opts = 0;
    mint cur = 0;

    for (map<mint, mint>::iterator i = freqs.begin(); i != freqs.end(); ++i)
    {
        mint num = i->first;

        for (; cur != num; ++cur)
        {
            res = (res * opts) % M;

            --opts;

            if (opts < 0)
            {
                return 0;
            }
        }

        opts = (opts + i->second) % M;
    }

    for (; cur != n - 1; ++cur)
    {
        res = (res * opts) % M;

        --opts;

        if (opts < 0)
        {
            return 0;
        }
    }

    return res;
}

int main()
{
    mint t;

    cin >> t;

    for (; t; --t)
    {
        mint n;

        cin >> n;

        map<mint, mint> freqs;

        for (mint i = 0; i != n; ++i)
        {
            mint c;

            cin >> c;

            freqs[c] = (freqs[c] + 1) % M;
        }

        /*
        for (map<mint, mint>::iterator j = freqs.begin(); j != freqs.end(); ++j)
        {
            cout << "(" << j->first << ", " << j->second << ") ";
        }
        */

        cout << cc(n, freqs) << endl;
    }

    return 0;
}

