
int consistentHash(string s)
{
	/*
	// FNV

	unsigned long res = 14695981039346656037L;

	for (string::iterator s_iter = s.begin(); s_iter != s.end(); ++s_iter)
	{
		unsigned long c = static_cast<int>(*s_iter);

		res *= 1099511628211L;

		res ^= c;
	}

	return static_cast<int>(res & 0xffffffff) ^ static_cast<int>(res >> 32);
	*/

	// Jenkins

	int res = 0;

	for (string::iterator s_iter = s.begin(); s_iter != s.end(); ++s_iter)
	{
		int c = static_cast<int>(*s_iter);

		res += c;
		res += res << 10;
		res ^= res >> 6;
	}

	res += res << 3;
	res ^= res >> 11;
	res += res << 15;

	return res;
}

