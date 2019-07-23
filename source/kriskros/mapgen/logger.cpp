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
#include <cerrno>

#include "errcodes.h"
#include "commands.h"
#include "ftypes.h"
#include "errhdl.h"
#include "logger.h"

int mapgen::logger::log(std::string lFname, std::string lMsg)
{
	int rCode = 0;

	std::string lFullFname = lFname + ".log";

	time_t raw;
	time(&raw);

	struct tm *tInfo;
	char buff[80];

	tInfo = localtime(&raw);
	strftime(buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", tInfo);

	std::string now(buff);

	std::ofstream lFile;
	lFile.open(lFullFname.c_str(), std::ofstream::app | std::ofstream::out);

	if(lFile.fail() || !lFile.is_open())
	{
		rCode = mapgen::error_handler::handle_io_errors(FILE_TYPE_LOG, FILE_READ);
	}

	if(rCode == 0)
		lFile << "[" << now << "] " << lMsg << std::endl;
		// [YYYY-MM-DD HH:MM:SS] <lMsg>

	if(rCode == 0 && lFile.fail())
	{
		rCode = mapgen::error_handler::handle_io_errors(FILE_TYPE_LOG, FILE_WRITE);
	}

	if(lFile.is_open())
		lFile.close();

	return rCode;
}
