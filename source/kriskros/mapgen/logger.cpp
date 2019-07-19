/***********************************
 * Kris-Kros Game Kit
 *----------------------------------
 * Kris-Kros Map Generator source
 * File: logger.cpp
 *
 * Made by Marek Pol·Ëek
 * Github.com/Polda18
 *
 * GNU-GPL v3.0
 * 2019
 ***********************************/

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <errno.h>

#include "errcodes.h"
#include "commands.h"
#include "logger.h"

int mapgen::logger::log(std::string lFname, std::string lMsg)
{
	int rCode = 0;

	std::string lFullFname = lFname + ".log";

	time_t raw;
	time(&raw);

	struct tm *tInfo;
	char buff[80];

	timeinfo = localtime(&raw);
	strftime(buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", tInfo);

	std::string now(buff);
	// [YYYY-MM-DD HH:MM:SS] <lMsg>

	// TODO: write into log file

	return rCode;
}
