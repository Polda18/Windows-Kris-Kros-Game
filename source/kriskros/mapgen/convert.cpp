/***********************************
 * Kris-Kros Game Kit
 *----------------------------------
 * Kris-Kros Map Generator source
 * File: convert.cpp
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
#include <cerrno>

#include "errcodes.h"
#include "commands.h"
#include "logger.h"
#include "errhdl.h"
#include "ftypes.h"
#include "mapidx.h"
#include "convert.h"

int mapgen::converter::convert(bool v, bool o, bool c, bool f, bool l,
							   std::string inFname,
							   std::string outFname,
							   std::string capFname,
							   std::string ftFname,
							   std::string lang)
{
	int rCode = 0;
	bool fail = false;

	// Initialization of input and output files
	std::ifstream inFile;
	std::ofstream outFile;

	// Conversion log file creation and purge
	std::string lFname = "convert";
	std::string lFullFname = lFname + ".log";

	std::ofstream lFile;
	lFile.open(lFullFname.c_str(), std::ofstream::trunc | std::ofstream::out);

	if(lFile.fail() || !lFile.is_open())
	{
		rCode = mapgen::error_handler::handle_io_errors(FILE_TYPE_LOG, FILE_READ);

		return rCode;
	}

	lFile << "<======== BEGINNING OF CONVERSION LOG FILE ========>" << std::endl << std::endl;

	if(lFile.fail())
	{
		rCode = mapgen::error_handler::handle_io_errors(FILE_TYPE_LOG, FILE_WRITE);

		return rCode;
	}

	// TODO: Conversion
	rCode = mapgen::converter::parse_pcx(inFile, outFile, lFile,
		inFname, outFname, v, o, c, f, l, &fail);

	// Temporary lines
	std::cout << "Not implemented yet" << std::endl;
	lFile << "Conversion not implemented yet!" << std::endl;
	if(lFile.fail())
	{
		rCode = mapgen::error_handler::handle_io_errors(FILE_TYPE_LOG, FILE_WRITE);

		return rCode;
	}
	// End temporary lines

	// End conversion log file properly
	lFile << std::endl << "<======== END OF CONVERSION LOG FILE ========>" << std::endl;

	if(lFile.fail())
		rCode = mapgen::error_handler::handle_io_errors(FILE_TYPE_LOG, FILE_WRITE);

	return rCode;
}

int mapgen::converter::parse_pcx(std::ifstream inFile, std::ofstream outFile, std::ofstream lFile,
								 std::string inFname, std::string outFname,
								 bool v, bool o, bool c, bool f, bool l, bool *fail)
{
	int rCode = 0;

	// TODO

	return rCode;
}

int mapgen::converter::write_map(std::ofstream outFile,
								 bool v, bool o, bool c, bool f, bool l, bool *fail)
{
	int rCode = 0;

	// TODO

	return rCode;
}
