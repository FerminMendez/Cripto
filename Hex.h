#ifndef HEX
#define HEX

#include <bitset>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "math.h"
#include "Hex.h"
using namespace std;

class Hex
{
public:
	string val;
	Hex();
	Hex(int n);
	Hex(string s);
	Hex(char c);

	string getHex();
	int hex_to_int();
	Hex operator+(Hex &h2);
	Hex operator+(int n);
	Hex operator-(Hex &h2);
	Hex operator-(int n);
	Hex operator^(Hex &h2);
};

Hex::Hex()
{
	string s = "";
	val = s;
}

Hex::Hex(int n)
{
	n = n % 256;
	stringstream ss;
	ss << hex << n;
	val = ss.str();
}

Hex::Hex(string s)
{
	val = s;
}
Hex::Hex(char c)
{
	stringstream ss;
	ss << hex << (int)c;
	val = ss.str();
}

string Hex::getHex()
{
	return val;
}
int Hex::hex_to_int()
{
	int result = 0;
	for (int i = 0; i < val.length(); i++)
	{
		if (val[i] >= 48 && val[i] <= 57)
		{
			result += (val[i] - 48) * pow(16, val.length() - i - 1);
		}
		else if (val[i] >= 65 && val[i] <= 70)
		{
			result += (val[i] - 55) * pow(16, val.length() - i - 1);
		}
		else if (val[i] >= 97 && val[i] <= 102)
		{
			result += (val[i] - 87) * pow(16, val.length() - i - 1);
		}
	}
	return ((result%256)+256)%256;
}

Hex Hex::operator+(Hex &h2)
{
	Hex x(this->hex_to_int() + h2.hex_to_int());
	return x;
}

Hex Hex::operator+(int n)
{
	Hex x(this->hex_to_int() + n);
	return x;
}

Hex Hex::operator-(Hex &h2)
{
	Hex x(this->hex_to_int() - h2.hex_to_int());
	return x;
}

Hex Hex::operator-(int n)
{
	Hex x(this->hex_to_int() - n);
	return x;
}


Hex Hex::operator^(Hex &h2)
{
	Hex x(this->hex_to_int()^h2.hex_to_int());
	return x;
}

#endif
