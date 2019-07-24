/***********************************
 * Kris-Kros Game Kit
 *----------------------------------
 * Kris-Kros Map Generator source
 * File: endian.cpp
 *
 * Made by Marek Pol·Ëek
 * Github.com/Polda18
 *
 * GNU-GPL v3.0
 * 2019
 ***********************************/

#include <climits>

#include "endian.h"

bool is_big_endian(void)
{
	union
	{
		unsigned int i;
		unsigned char c[sizeof(unsigned int)];
	} beInt = {0x01020304};

	return (beInt.c[0] == 0x01);
}

T swap_endian(T u)
{
	static_assert(CHAR_BIT == 8, "CHAR_BIT != 8");

	union
	{
		T u;
		unsigned char s[sizeof(T)]
	} source, dest;

	source.u = u;
	int lIdx = sizeof(T) - 1;

	for(int i = 0; i < sizeof(T); ++i)
		dest.s[i] = source.s[lIdx - i];

	return dest.u;
}
