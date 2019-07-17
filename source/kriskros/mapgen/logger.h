/***********************************
 * Kris-Kros Game Kit
 *----------------------------------
 * Kris-Kros Map Generator source
 * File: logger.h
 *
 * Made by Marek Pol·Ëek
 * Github.com/Polda18
 *
 * GNU-GPL v3.0
 * 2019
 ***********************************/

#include <string>

#ifndef LOGGER_H
#define LOGGER_H

namespace mapgen
{
	namespace logger
	{
		int log(std::string lFname, std::string lMsg);
	}
}

#endif