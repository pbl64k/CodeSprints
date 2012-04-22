
#include <iostream>
#include <istream>
#include <ostream>
#include <fstream>

#include <string>

using namespace std;

#define W 300
#define H 300
#define P (W * H)
#define C 3
#define S (P * C)

unsigned char *img;
unsigned char *newimg;

void transform(size_t ix)
{
	if (ix < ((W * C) + 1) || ix > ((S - (W * C)) - 2))
	{
		newimg[ix] = img[ix];

		return;
	}

	int np =
			(
				(-4 * static_cast<int>(img[ix - (C * W) - C])) +
				(-2 * static_cast<int>(img[ix - (C * W)])) +
				(-2 * static_cast<int>(img[ix - C])) +
				(1 * static_cast<int>(img[ix])) +
				(2 * static_cast<int>(img[ix + C])) +
				(2 * static_cast<int>(img[ix + (C * W)])) +
				(4 * static_cast<int>(img[ix + (C * W) + C]))
			)
			;

	newimg[ix] = static_cast<unsigned char>(max(0, min(255, np)));
}

int main()
{
	img = new unsigned char[S];
	newimg = new unsigned char[S];

	string ifn, ofn;

	cin >> ifn;
	cin >> ofn;

	ifstream ifs(ifn, ifstream::in | ifstream::binary);

	ifs.seekg(10);

	size_t off = 0;

	for (size_t i = 0; i != 4; ++i)
	{
		off += ifs.get() * (1 << i);
	}

	char header[65536];

	ifs.seekg(0);

	ifs.read(header, off);

	ifs.read(reinterpret_cast<char *>(img), S);

	for (size_t i = 0; i != S; ++i)
	{
		transform(i);
	}

	ofstream ofs(ofn, ofstream::out | ofstream::binary);

	ofs.write(header, off);

	ofs.write(reinterpret_cast<char *>(newimg), S);

	return 0;
}

