/***********************************
 * Kris-Kros Game Kit
 *----------------------------------
 * Kris-Kros Map Generator source
 * File: endian.h
 *
 * Made by Marek Pol·Ëek
 * Github.com/Polda18
 *
 * GNU-GPL v3.0
 * 2019
 ***********************************/

#include <climits>

#ifndef ENDIAN_H
#define ENDIAN_H

template <typename T>

bool is_big_endian(void);
T swap_endian(T u);

#endif