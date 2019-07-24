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

#include <windows.h>

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
#include "pcxhead.h"
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

	// Conversion process
	rCode = mapgen::converter::parse_pcx(inFile, outFile, lFile,
		inFname, outFname, v, o, c, f, l, &fail);

	lFile << std::endl << "Conversion " << ((fail) ? "failed" : "was successful") << "." << std::endl;

	if(lFile.fail())
		rCode = mapgen::error_handler::handle_io_errors(FILE_TYPE_LOG, FILE_WRITE);

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
	bool lFileRO = false;
	std::string lMsg;

	// Check if log file is open. If not, fail the process.
	if(!lFile.is_open())
	{
		rCode = ERR_LOGFILE_NOT_OPEN;
		std::cerr << construct_error("Log file is not open! Contact developer Polda18 @GitHub.com\nhttps://github.com/Polda18/Windows-Kris-Kros-Game/issues");
		*fail = true;

		return rCode;
	}

	lMsg = "<<< Starting converson >>>";

	std::cout << lMsg << std::endl;
	lFile << lMsg << std::endl;
	
	// Writing to log file failed? Set log file RO state and continue
	if(lFile.fail())
		lFileRO = true;
	else
		lFileRO = false;

	// Resolve the file names
	std::string outDefFname = inFname.substr(0, inFname.rfind('.'));

	size_t inDirCheck = inFname.rfind('/');
	if(inDirCheck == std::string::npos)
		inDirCheck = inFname.rfind('\\');
	std::string inPureFname = inFname.substr(inDirCheck + 1);
	std::string outCurFname = ((o) ? outFname : (outDefFname + ".map"));
	
	size_t outDirCheck = outCurFname.rfind('/');
	if(outDirCheck == std::string::npos)
		outDirCheck = outCurFname.rfind('\\');
	std::string outPureFname = outCurFname.substr(outDirCheck + 1);

	// General log
	lMsg = "Opening PCX file `" + inPureFname + "` ... ";
	std::cout << lMsg;
	lFile << lMsg;

	// Writing to log file failed? Set log file RO state and continue
	if(lFile.fail())
		lFileRO = true;
	else
		lFileRO = false;

	// Open the PCX file to read
	inFile.open(inFname.c_str(), std::ifstream::in | std::ifstream::binary);

	// File failed to open, resolve the error
	if(inFile.fail() || !inFile.is_open())
	{
		// General log
		lMsg = "Error";
		std::cout << lMsg << std::endl;
		lFile << lMsg << std::endl;

		// Writing to log file failed? Set log file RO state and continue
		if(lFile.fail())
			lFileRO = true;
		else
			lFileRO = false;

		rCode = mapgen::error_handler::handle_io_errors(FILE_TYPE_BIN, FILE_READ, lFile);
		*fail = true;

		return rCode;
	}
	// File is open, continue

	// General log
	lMsg = "Done";
	std::cout << lMsg << std::endl;
	lFile << lMsg << std::endl;

	// Writing to log file failed? Set log file RO state and continue
	if(lFile.fail())
		lFileRO = true;
	else
		lFileRO = false;

	// General log
	lMsg = "Reading PCX file `" + inFname + "` ... ";
	std::cout << lMsg;
	lFile << lMsg;

	// Writing to log file failed? Set log file RO state and continue
	if(lFile.fail())
		lFileRO = true;
	else
		lFileRO = false;

	// File is empty, fail
	if(inFile.eof())
	{
		// General log
		lMsg = "Error";
		std::cout << lMsg << std::endl;
		lFile << lMsg << std::endl;

		// Writing to log file failed? Set log file RO state and continue
		if(lFile.fail())
			lFileRO = true;
		else
			lFileRO = false;

		rCode = ERR_FILE_FORMAT_INCORRECT;
		*fail = true;

		std::string eMsg = construct_error("Input file is empty!");
		std::cerr << eMsg << std::endl;
		lFile << eMsg << std::endl;

		// Writing to log file failed? Set log file RO state and continue
		if(lFile.fail())
			lFileRO = true;
		else
			lFileRO = false;

		// Log into separate error.log file
		int lCode = mapgen::logger::log("error", eMsg);
		if(lCode > 0)
			rCode = lCode;

		return rCode;
	}

	if(v)
		std::cout << "verbose enabled" << std::endl;
	lFile << "log verbosed" << std::endl;

	// Writing to log file failed? Set log file RO state and continue
	if(lFile.fail())
		lFileRO = true;
	else
		lFileRO = false;

	PCXHEAD *hPcx;

	// Verbosed log
	lMsg = "Reading PCX header";
	if(v)
		std::cout << lMsg << std::endl;
	lFile << lMsg << std::endl;

	// Writing to log file failed? Set log file RO state and continue
	if(lFile.fail())
		lFileRO = true;
	else
		lFileRO = false;

	// Verbosed log
	lMsg = "Header info: Manufacturer ... ";
	if(v)
		std::cout << lMsg;
	lFile << lMsg;

	// Writing to log file failed? Set log file RO state and continue
	if(lFile.fail())
		lFileRO = true;
	else
		lFileRO = false;

	inFile.read(&hPcx->Identifier, sizeof(BYTE));

	// File failed to read, resolve the error
	if(inFile.fail())
	{
		// Verbosed log
		lMsg = "Error";
		if(v)
			std::cout << lMsg << std::endl;
		lFile << lMsg << std::endl;

		// Writing to log file failed? Set log file RO state and continue
		if(lFile.fail())
			lFileRO = true;
		else
			lFileRO = false;

		rCode = mapgen::error_handler::handle_io_errors(FILE_TYPE_BIN, FILE_READ, lFile);
		*fail = true;

		return rCode;
	}

	// Identifier is not 0x0a => fail
	if(hPcx->Identifier != 0x0a)
	{
		// Verbosed log
		lMsg = "Error";
		if(v)
			std::cout << lMsg << std::endl;
		lFile << lMsg << std::endl;

		// Writing to log file failed? Set log file RO state and continue
		if(lFile.fail())
			lFileRO = true;
		else
			lFileRO = false;

		rCode = ERR_FILE_FORMAT_INCORRECT;
		*fail = true;

		std::string eMsg = construct_error("Input file is not a PCX file!");
		std::cerr << eMsg << std::endl;
		lFile << eMsg << std::endl;

		// Log file write failed? Just record RO state and continue
		if(lFile.fail())
			lFileRO = true;
		else
			lFileRO = false;

		// Log into separate error.log file
		int lCode = mapgen::logger::log("error", eMsg);
		if(lCode > 0)
			rCode = lCode;

		return rCode;
	}

	// Verbosed log
	lMsg = "Okay. ZSoft PC Paintbrush";
	if(v)
		std::cout << lMsg << std::endl;
	lFile << lMsg << std::endl;

	// Writing to log file failed? Set log file RO state and continue
	if(lFile.fail())
		lFileRO = true;
	else
		lFileRO = false;

	// Check unexpected end of file
	if(inFile.eof())
	{
		rCode = ERR_UNEXPECTED_EOF;
		*fail = true;

		std::string eMsg = construct_error("Unexpected end of file!");
		std::cerr << eMsg << std::endl;
		lFile << eMsg << std::endl;

		// Log file write failed? Just record RO state and continue
		if(lFile.fail())
			lFileRO = true;
		else
			lFileRO = false;

		// Log into separate error.log file
		int lCode = mapgen::logger::log("error", eMsg);
		if(lCode > 0)
			rCode = lCode;

		return rCode;
	}

	// Verbosed log
	lMsg = "Header info: Version ... ";
	if(v)
		std::cout << lMsg;
	lFile << lMsg;

	// Writing to log file failed? Set log file RO state and continue
	if(lFile.fail())
		lFileRO = true;
	else
		lFileRO = false;

	inFile.read(&hPcx->Version, sizeof(BYTE));

	// File failed to read, resolve the error
	if(inFile.fail())
	{
		// Verbosed log
		lMsg = "Error";
		if(v)
			std::cout << lMsg << std::endl;
		lFile << lMsg << std::endl;

		// Writing to log file failed? Set log file RO state and continue
		if(lFile.fail())
			lFileRO = true;
		else
			lFileRO = false;

		rCode = mapgen::error_handler::handle_io_errors(FILE_TYPE_BIN, FILE_READ, lFile);
		*fail = true;

		return rCode;
	}

	// Check PCX version
	switch(hPcx->Version)
	{
	case 0:
		// valid version

		// Verbosed log
		lMsg = "Okay. ZSoft PC Paintbrush v2.5";
		if(v)
			std::cout << lMsg << std::endl;
		lFile << lMsg << std::endl;

		// Writing to log file failed? Set log file RO state and continue
		if(lFile.fail())
			lFileRO = true;
		else
			lFileRO = false;

		break;
	case 2:
		// valid version

		// Verbosed log
		lMsg = "Okay. ZSoft PC Paintbrush v2.8 (modified palette)";
		if(v)
			std::cout << lMsg << std::endl;
		lFile << lMsg << std::endl;

		// Writing to log file failed? Set log file RO state and continue
		if(lFile.fail())
			lFileRO = true;
		else
			lFileRO = false;

		break;
	case 3:
		// valid version

		// Verbosed log
		lMsg = "Okay. ZSoft PC Paintbrush v2.8 (default palette)";
		if(v)
			std::cout << lMsg << std::endl;
		lFile << lMsg << std::endl;

		// Writing to log file failed? Set log file RO state and continue
		if(lFile.fail())
			lFileRO = true;
		else
			lFileRO = false;

		break;
	case 4:
		// valid version

		// Verbosed log
		lMsg = "Okay. ZSoft PC Paintbrush for Windows";
		if(v)
			std::cout <<lMsg << std::endl;
		lFile << lMsg << std::endl;

		// Writing to log file failed? Set log file RO state and continue
		if(lFile.fail())
			lFileRO = true;
		else
			lFileRO = false;

		break;
	case 5:
		// valid version

		// Verbosed log
		lMsg = "Okay. ZSoft PC Paintbrush v3.0+";
		if(v)
			std::cout << lMsg << std::endl;
		lFile << lMsg << std::endl;

		// Writing to log file failed? Set log file RO state and continue
		if(lFile.fail())
			lFileRO = true;
		else
			lFileRO = false;

		break;
	default:
		// invalid version, fail

		// Verbosed log
		lMsg = "Error";
		if(v)
			std::cout << lMsg << std::endl;
		lFile << lMsg << std::endl;

		// Writing to log file failed? Set log file RO state and continue
		if(lFile.fail())
			lFileRO = true;
		else
			lFileRO = false;

		rCode = ERR_FILE_FORMAT_INCORRECT;
		*fail = true;

		std::string eMsg = construct_error("Input file is not a PCX file!");
		std::cerr << eMsg << std::endl;
		lFile << eMsg << std::endl;

		// Log file write failed? Just record RO state and continue
		if(lFile.fail())
			lFileRO = true;
		else
			lFileRO = false;

		// Log into separate error.log file
		int lCode = mapgen::logger::log("error", eMsg);
		if(lCode > 0)
			rCode = lCode;

		return rCode;
	}

	// Check unexpected end of file
	if(inFile.eof())
	{
		rCode = ERR_UNEXPECTED_EOF;
		*fail = true;

		std::string eMsg = construct_error("Unexpected end of file!");
		std::cerr << eMsg << std::endl;
		lFile << eMsg << std::endl;

		// Log file write failed? Just record RO state and continue
		if(lFile.fail())
			lFileRO = true;
		else
			lFileRO = false;

		// Log into separate error.log file
		int lCode = mapgen::logger::log("error", eMsg);
		if(lCode > 0)
			rCode = lCode;

		return rCode;
	}

	// Verbosed log
	lMsg = "Header info: Encoding";
	if(v)
		std::cout << lMsg;
	lFile << lMsg;

	// Writing to log file failed? Set log file RO state and continue
	if(lFile.fail())
		lFileRO = true;
	else
		lFileRO = false;

	inFile.read(&hPcx->Encoding, 1);

	// File failed to read, resolve the error
	if(inFile.fail())
	{
		// Verbosed log
		lMsg = "Error";
		if(v)
			std::cout << lMsg << std::endl;
		lFile << lMsg << std::endl;

		// Writing to log file failed? Set log file RO state and continue
		if(lFile.fail())
			lFileRO = true;
		else
			lFileRO = false;

		rCode = mapgen::error_handler::handle_io_errors(FILE_TYPE_BIN, FILE_READ, lFile);
		*fail = true;

		return rCode;
	}

	// Encoding is not RLE
	if(hPcx->Encoding != 1)
	{
		// Verbosed log
		lMsg = "Error";
		if(v)
			std::cout << lMsg << std::endl;
		lFile << lMsg << std::endl;

		// Writing to log file failed? Set log file RO state and continue
		if(lFile.fail())
			lFileRO = true;
		else
			lFileRO = false;

		rCode = ERR_FILE_FORMAT_INCORRECT;
		*fail = true;

		std::string eMsg = construct_error("Input file is not a PCX file!");
		std::cerr << eMsg << std::endl;
		lFile << eMsg << std::endl;

		// Log file write failed? Just record RO state and continue
		if(lFile.fail())
			lFileRO = true;
		else
			lFileRO = false;

		// Log into separate error.log file
		int lCode = mapgen::logger::log("error", eMsg);
		if(lCode > 0)
			rCode = lCode;

		return rCode;
	}

	// Verbosed log
	lMsg = "Okay. RLE encoding";
	if(v)
		std::cout << lMsg << std::endl;
	lFile << lMsg << std::endl;

	// Writing to log file failed? Set log file RO state and continue
	if(lFile.fail())
		lFileRO = true;
	else
		lFileRO = false;

	// Check unexpected end of file
	if(inFile.eof())
	{
		rCode = ERR_UNEXPECTED_EOF;
		*fail = true;

		std::string eMsg = construct_error("Unexpected end of file!");
		std::cerr << eMsg << std::endl;
		lFile << eMsg << std::endl;

		// Writing to log file failed? Set log file RO state and continue
		if(lFile.fail())
			lFileRO = true;
		else
			lFileRO = false;

		// Log into separate error.log file
		int lCode = mapgen::logger::log("error", eMsg);
		if(lCode > 0)
			rCode = lCode;

		return rCode;
	}

	// Verbosed log
	lMsg = "Header info: BPP per plane ... ";
	if(v)
		std::cout << lMsg;
	lFile << lMsg;

	// Writing to log file failed? Set log file RO state and continue
	if(lFile.fail())
		lFileRO = true;
	else
		lFileRO = false;

	inFile.read(&hPcx->BitsPerPixel, 1);

	// File failed to read, resolve the error
	if(inFile.fail())
	{
		// Verbosed log
		lMsg = "Error";
		if(v)
			std::cout << lMsg << std::endl;
		lFile << lMsg << std::endl;

		// Writing to log file failed? Set log file RO state and continue
		if(lFile.fail())
			lFileRO = true;
		else
			lFileRO = false;

		rCode = mapgen::error_handler::handle_io_errors(FILE_TYPE_BIN, FILE_READ, lFile);
		*fail = true;

		return rCode;
	}

	// Bits per pixel have defined values
	switch(hPcx->BitsPerPixel)
	{
	case 1:
		// 1 bit per plane

		// Verbosed log
		lMsg = "Okay. 1 bit per plane";
		if(v)
			std::cout << lMsg << std::endl;
		lFile << lMsg << std::endl;

		// Writing to log file failed? Set log file RO state and continue
		if(lFile.fail())
			lFileRO = true;
		else
			lFileRO = false;

		break;
	case 2:
		// 2 bits per plane

		// Verbosed log
		lMsg = "Okay. 2 bits per plane";
		if(v)
			std::cout << lMsg << std::endl;
		lFile << lMsg << std::endl;

		// Writing to log file failed? Set log file RO state and continue
		if(lFile.fail())
			lFileRO = true;
		else
			lFileRO = false;

		break;
	case 4:
		// 4 bits per plane

		// Verbosed log
		lMsg = "Okay. 4 bits per plane";
		if(v)
			std::cout << lMsg << std::endl;
		lFile << lMsg << std::endl;

		// Writing to log file failed? Set log file RO state and continue
		if(lFile.fail())
			lFileRO = true;
		else
			lFileRO = false;

		break;
	case 8:
		// 8 bits per plane

		// Verbosed log
		lMsg = "Okay. 8 bits per plane";
		if(v)
			std::cout << lMsg << std::endl;
		lFile << lMsg << std::endl;

		// Writing to log file failed? Set log file RO state and continue
		if(lFile.fail())
			lFileRO = true;
		else
			lFileRO = false;

		break;
	default:
		// invalid values, fail

		// Verbosed log
		lMsg = "Error";
		if(v)
			std::cout << lMsg << std::endl;
		lFile << lMsg << std::endl;

		// Writing to log file failed? Set log file RO state and continue
		if(lFile.fail())
			lFileRO = true;
		else
			lFileRO = false;

		rCode = ERR_FILE_FORMAT_INCORRECT;
		*fail = true;

		std::string eMsg = construct_error("Input file is not a PCX file!");
		std::cerr << eMsg << std::endl;
		lFile << eMsg << std::endl;

		// Writing to log file failed? Set log file RO state and continue
		if(lFile.fail())
			lFileRO = true;
		else
			lFileRO = false;

		// Log into separate error.log file
		int lCode = mapgen::logger::log("error", eMsg);
		if(lCode > 0)
			rCode = lCode;

		return rCode;
	}

	// Check unexpected end of file
	if(inFile.eof())
	{
		rCode = ERR_UNEXPECTED_EOF;
		*fail = true;

		std::string eMsg = construct_error("Unexpected end of file!");
		std::cerr << eMsg << std::endl;
		lFile << eMsg << std::endl;

		// Log file write failed? Just record RO state and continue
		if(lFile.fail())
			lFileRO = true;
		else
			lFileRO = false;

		// Log into separate error.log file
		int lCode = mapgen::logger::log("error", eMsg);
		if(lCode > 0)
			rCode = lCode;

		return rCode;
	}

	// Verbosed log
	lMsg = "Header info: Left margin ... ";
	if(v)
		std::cout << lMsg;
	lFile << lMsg;

	// Writing to log file failed? Set log file RO state and continue
	if(lFile.fail())
		lFileRO = true;
	else
		lFileRO = false;

	inFile.read(&hPcx->XStart, 2);

	// File failed to read, resolve the error
	if(inFile.fail())
	{
		// Verbosed log
		lMsg = "Error";
		if(v)
			std::cout << lMsg << std::endl;
		lFile << lMsg << std::endl;

		// Writing to log file failed? Set log file RO state and continue
		if(lFile.fail())
			lFileRO = true;
		else
			lFileRO = false;

		rCode = mapgen::error_handler::handle_io_errors(FILE_TYPE_BIN, FILE_READ, lFile);
		*fail = true;

		return rCode;
	}

	// Check endianess
	if(is_big_endian())
		hPcx->XStart = reinterpret_cast<short>(switch_endian(hPcx->XStart));

	// Verbosed log
	lMsg = std::string(hPcx->XStart) + " pixels";
	if(v)
		std::cout << lMsg << std::endl;
	lFile << lMsg << std::endl;

	// Writing to log file failed? Set log file RO state and continue
	if(lFile.fail())
		lFileRO = true;
	else
		lFileRO = false;

	// Check unexpected end of file
	if(inFile.eof())
	{
		rCode = ERR_UNEXPECTED_EOF;
		*fail = true;

		std::string eMsg = construct_error("Unexpected end of file!");
		std::cerr << eMsg << std::endl;
		lFile << eMsg << std::endl;

		// Log file write failed? Just record RO state and continue
		if(lFile.fail())
			lFileRO = true;
		else
			lFileRO = false;

		// Log into separate error.log file
		int lCode = mapgen::logger::log("error", eMsg);
		if(lCode > 0)
			rCode = lCode;

		return rCode;
	}

	// Verbosed log
	lMsg = "Header info: Top margin ... ";
	if(v)
		std::cout << lMsg;
	lFile << lMsg;

	// Writing to log file failed? Set log file RO state and continue
	if(lFile.fail())
		lFileRO = true;
	else
		lFileRO = false;

	inFile.read(&hPcx->YStart, 2);

	// File failed to read, resolve the error
	if(inFile.fail())
	{
		// Verbosed log
		lMsg = "Error";
		if(v)
			std::cout << lMsg << std::endl;
		lFile << lMsg << std::endl;

		// Writing to log file failed? Set log file RO state and continue
		if(lFile.fail())
			lFileRO = true;
		else
			lFileRO = false;

		rCode = mapgen::error_handler::handle_io_errors(FILE_TYPE_BIN, FILE_READ, lFile);
		*fail = true;

		return rCode;
	}

	// Check endianess
	if(is_big_endian())
		hPcx->YStart = reinterpret_cast<short>(switch_endian(hPcx->YStart));

	// Verbosed log
	lMsg = std::string(hPcx->YStart) + " pixels";
	if(v)
		std::cout << lMsg << std::endl;
	lFile << lMsg << std::endl;

	// Writing to log file failed? Set log file RO state and continue
	if(lFile.fail())
		lFileRO = true;
	else
		lFileRO = false;

	// Check unexpected end of file
	if(inFile.eof())
	{
		rCode = ERR_UNEXPECTED_EOF;
		*fail = true;

		std::string eMsg = construct_error("Unexpected end of file!");
		std::cerr << eMsg << std::endl;
		lFile << eMsg << std::endl;

		// Log file write failed? Just record RO state and continue
		if(lFile.fail())
			lFileRO = true;
		else
			lFileRO = false;

		// Log into separate error.log file
		int lCode = mapgen::logger::log("error", eMsg);
		if(lCode > 0)
			rCode = lCode;

		return rCode;
	}

	// Verbosed log
	lMsg = "Header info: Right margin ... ";
	if(v)
		std::cout << lMsg;
	lFile << lMsg;

	// Writing to log file failed? Set log file RO state and continue
	if(lFile.fail())
		lFileRO = true;
	else
		lFileRO = false;

	inFile.read(&hPcx->XEnd, 2);

	// File failed to read, resolve the error
	if(inFile.fail())
	{
		// Verbosed log
		lMsg = "Error";
		if(v)
			std::cout << lMsg << std::endl;
		lFile << lMsg << std::endl;

		// Writing to log file failed? Set log file RO state and continue
		if(lFile.fail())
			lFileRO = true;
		else
			lFileRO = false;

		rCode = mapgen::error_handler::handle_io_errors(FILE_TYPE_BIN, FILE_READ, lFile);
		*fail = true;

		return rCode;
	}

	// Check endianess
	if(is_big_endian())
		hPcx->XEnd = reinterpret_cast<short>(switch_endian(hPcx->XEnd));

	// Verbosed log
	lMsg = std::string(hPcx->XEnd) + " pixels";
	if(v)
		std::cout << lMsg << std::endl;
	lFile << lMsg << std::endl;

	// Writing to log file failed? Set log file RO state and continue
	if(lFile.fail())
		lFileRO = true;
	else
		lFileRO = false;

	// Check unexpected end of file
	if(inFile.eof())
	{
		rCode = ERR_UNEXPECTED_EOF;
		*fail = true;

		std::string eMsg = construct_error("Unexpected end of file!");
		std::cerr << eMsg << std::endl;
		lFile << eMsg << std::endl;

		// Log file write failed? Just record RO state and continue
		if(lFile.fail())
			lFileRO = true;
		else
			lFileRO = false;

		// Log into separate error.log file
		int lCode = mapgen::logger::log("error", eMsg);
		if(lCode > 0)
			rCode = lCode;

		return rCode;
	}

	// Verbosed log
	lMsg = "Header info: Bottom margin ... ";
	if(v)
		std::cout << lMsg;
	lFile << lMsg;

	// Writing to log file failed? Set log file RO state and continue
	if(lFile.fail())
		lFileRO = true;
	else
		lFileRO = false;

	inFile.read(&hPcx->YEnd, 2);

	// File failed to read, resolve the error
	if(inFile.fail())
	{
		// Verbosed log
		lMsg = "Error";
		if(v)
			std::cout << lMsg << std::endl;
		lFile << lMsg << std::endl;

		// Writing to log file failed? Set log file RO state and continue
		if(lFile.fail())
			lFileRO = true;
		else
			lFileRO = false;

		rCode = mapgen::error_handler::handle_io_errors(FILE_TYPE_BIN, FILE_READ, lFile);
		*fail = true;

		return rCode;
	}

	// Check endianess
	if(is_big_endian())
		hPcx->YEnd = reinterpret_cast<short>(switch_endian(hPcx->YEnd));

	// Verbosed log
	lMsg = std::string(hPcx->YEnd) + " pixels";
	if(v)
		std::cout << lMsg << std::endl;
	lFile << lMsg << std::endl;

	// Writing to log file failed? Set log file RO state and continue
	if(lFile.fail())
		lFileRO = true;
	else
		lFileRO = false;

	// Check unexpected end of file
	if(inFile.eof())
	{
		std::string eMsg = construct_error("Unexpected end of file!");
		std::cerr << eMsg << std::endl;
		lFile << eMsg << std::endl;

		// Log file write failed? Just record RO state and continue
		if(lFile.fail())
			lFileRO = true;
		else
			lFileRO = false;

		// Log into separate error.log file
		int lCode = mapgen::logger::log("error", eMsg);
		if(lCode > 0)
			rCode = lCode;

		return rCode;
	}

	//todo

	if(lFileRO)
		std::cout << "There was an issue with logging into `convert.log` file"
		<< std::endl << "during the conversion. Make sure you didn't make it read only." << std::endl;

	return rCode;
}

int mapgen::converter::write_map(std::ofstream outFile, std::string *content,
								 bool v, bool o, bool c, bool f, bool l, bool *fail)
{
	int rCode = 0;

	// TODO

	return rCode;
}
