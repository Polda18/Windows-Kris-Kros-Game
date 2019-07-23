/***********************************
 * Kris-Kros Game Kit
 *----------------------------------
 * Kris-Kros Map Generator source
 * File: arghdl.cpp
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

#include "switches.h"
#include "commands.h"
#include "errcodes.h"
#include "logger.h"
#include "arghdl.h"

int mapgen::arghandler::handle_args(int argc, char **argv,
			std::string *inFname,
			std::string *outFname,
			std::string *capFname,
			std::string *ftFname,
			std::string *hSwName,
			std::string *lang,
			bool *h, bool *o, bool *v, bool *c, bool *f, bool *l)
{
	// Initialize return code
	int rCode = 0;

	// Initialize map out of given strings
	mapSwVal[mapgen::arghandler::argSwOutS]  = swOutS;
	mapSwVal[mapgen::arghandler::argSwOutL]  = swOutL;
	mapSwVal[mapgen::arghandler::argSwLangS] = swLangS;
	mapSwVal[mapgen::arghandler::argSwLangL] = swLangL;
	mapSwVal[mapgen::arghandler::argSwCapS]  = swCapS;
	mapSwVal[mapgen::arghandler::argSwCapL]  = swCapL;
	mapSwVal[mapgen::arghandler::argSwHelpS] = swHelpS;
	mapSwVal[mapgen::arghandler::argSwHelpL] = swHelpL;
	mapSwVal[mapgen::arghandler::argSwVerbS] = swVerbS;
	mapSwVal[mapgen::arghandler::argSwVerbL] = swVerbL;
	mapSwVal[mapgen::arghandler::argSwFootS] = swFootS;
	mapSwVal[mapgen::arghandler::argSwFootL] = swFootL;
	// More switches upon request

	// Iterate through arguments
	for(int i = 1; i < argc; ++i)
	{
		// Check for every argument type
		std::string argSw = "undef";
		// Argument switch initialization with some value to start with

		// Convert argument to string
		std::string argStr = std::string(argv[i]);

		// If the matched string is at the beginning, strip it
		if(argStr.find(mapgen::arghandler::argSwOutS) == 0)
			// Switch '-o<file.map>'
			argSw = mapgen::arghandler::argSw_resolve(rCode, SW_OUTPUT, false, argv[i]);
		else if(argStr.find(mapgen::arghandler::argSwOutL) == 0)
			// Switch '--output=<file.map>'
			argSw = mapgen::arghandler::argSw_resolve(rCode, SW_OUTPUT, true, argv[i]);
		else if(argStr.find(mapgen::arghandler::argSwLangS) == 0)
			// Switch '-l<cz|en>' (more languages upon requests)
			argSw = mapgen::arghandler::argSw_resolve(rCode, SW_LANG, false, argv[i]);
		else if(argStr.find(mapgen::arghandler::argSwLangL) == 0)
			// Switch '--lang=<cz|en>'
			argSw = mapgen::arghandler::argSw_resolve(rCode, SW_LANG, true, argv[i]);
		else if(argStr.find(mapgen::arghandler::argSwCapS) == 0)
			// Switch '-c<file.txt>'
			argSw = mapgen::arghandler::argSw_resolve(rCode, SW_CAPTION, false, argv[i]);
		else if(argStr.find(mapgen::arghandler::argSwCapL) == 0)
			// Switch '--caption=<file.txt>'
			argSw = mapgen::arghandler::argSw_resolve(rCode, SW_CAPTION, true, argv[i]);
		else if(argStr.find(mapgen::arghandler::argSwHelpS) == 0)
			// Switch '-h'
			argSw = mapgen::arghandler::argSw_resolve(rCode, SW_HELP, false, argv[i]);
		else if(argStr.find(mapgen::arghandler::argSwHelpL) == 0)
			// Switch '--help' or '--help=<switch>'
			argSw = mapgen::arghandler::argSw_resolve(rCode, SW_HELP, true, argv[i]);
		else if(argStr.find(mapgen::arghandler::argSwVerbS) == 0)
			// Switch '-v'
			argSw = mapgen::arghandler::argSw_resolve(rCode, SW_VERBOSE, false, argv[i]);
		else if(argStr.find(mapgen::arghandler::argSwVerbL) == 0)
			// Switch '--verbose'
			argSw = mapgen::arghandler::argSw_resolve(rCode, SW_VERBOSE, true, argv[i]);
		else if(argStr.find(mapgen::arghandler::argSwFootS) == 0)
			// Switch '-f<file.txt>'
			argSw = mapgen::arghandler::argSw_resolve(rCode, SW_FOOTER, false, argv[i]);
		else if(argStr.find(mapgen::arghandler::argSwFootL) == 0)
			// Switch '--footer=<file.txt>'
			argSw = mapgen::arghandler::argSw_resolve(rCode, SW_FOOTER, true, argv[i]);
		// More switches upon requests
		else
			// Undefined switch
			argSw = mapgen::arghandler::argSw_resolve(rCode, SW_UNDEFINED, false, argv[i]);

		// Simple switch - this time with leading dashes
		switch(mapSwVal[argSw])
		{
		case swOutS:
			// Switch '-o<file.txt>'; this switch is expected to contain following data
			if(i == (argc - 1) && !(*h))
			{
				// If this is last argument and help switch is not defined, call this input error:
				rCode = ERR_INPUT_ARG_MISSING;
				std::string eMsg = construct_error("No input file specified!");
				std::cout << eMsg << std::endl;

				int logErr = mapgen::logger::log("error", eMsg);
				if(logErr == ERR_WRITE_PROTECTED)
					rCode = logErr;
				else if(logErr == ERR_FILE_DAMAGED)
					rCode = logErr;
			}

			// Enable output switch and pass argument to resolve file name
			*o = true;
			*outFname = mapgen::arghandler::argVal_resolve(rCode, SW_OUTPUT, false, argv[i]);
			break;
		case swOutL:
			// Switch '--output=<file.txt>'
			// This switch is expected to contain following data
			if(i == (argc - 1) && !(*h))
			{
				// If this is last argument and help switch is not defined, call this input error:
				rCode = ERR_INPUT_ARG_MISSING;
				std::string eMsg = construct_error("No input file specified!");
				std::cout << eMsg << std::endl;

				int logErr = mapgen::logger::log("error", eMsg);
				if(logErr == ERR_WRITE_PROTECTED)
					rCode = logErr;
				else if(logErr == ERR_FILE_DAMAGED)
					rCode = logErr;
			}

			// Enable output switch and pass argument to resolve file name
			*o = true;
			*outFname = mapgen::arghandler::argVal_resolve(rCode, SW_OUTPUT, true, argv[i]);
			break;
		case swLangS:
			// Switch '-l<cz|en>'; this switch is expected to contain following data
			if(i == (argc - 1) && !(*h))
			{
				// If this is last argument and help switch is not defined, call this input error:
				rCode = ERR_INPUT_ARG_MISSING;
				std::string eMsg = construct_error("No input file specified!");
				std::cout << eMsg << std::endl;

				int logErr = mapgen::logger::log("error", eMsg);
				if(logErr == ERR_WRITE_PROTECTED)
					rCode = logErr;
				else if(logErr == ERR_FILE_DAMAGED)
					rCode = logErr;
			}

			// Enable lang switch and ass argument to resolve language code
			*l = true;
			*lang = mapgen::arghandler::argVal_resolve(rCode, SW_LANG, false, argv[i]);
			break;
		case swLangL:
			// Switch '--lang=<cz|en>'; this switch is expected to contain following data
			if(i == (argc - 1) && !(*h))
			{
				// If this is last argument and help switch is not defined, call this input error:
				rCode = ERR_INPUT_ARG_MISSING;
				std::string eMsg = construct_error("No input file specified!");
				std::cout << eMsg << std::endl;

				int logErr = mapgen::logger::log("error", eMsg);
				if(logErr == ERR_WRITE_PROTECTED)
					rCode = logErr;
				else if(logErr == ERR_FILE_DAMAGED)
					rCode = logErr;
			}

			// Enable lang switch and pass argument to resolve language code
			*l = true;
			*lang = mapgen::arghandler::argVal_resolve(rCode, SW_LANG, true, argv[i]);
			break;
		case swCapS:
			// Switch '-c<file.txt>'; this switch is expected to contain following data
			if(i == (argc - 1) && !(*h))
			{
				// If this is last argument and help switch is not defined, call this input error:
				rCode = ERR_INPUT_ARG_MISSING;
				std::string eMsg = construct_error("No input file specified!");
				std::cout << eMsg << std::endl;

				int logErr = mapgen::logger::log("error", eMsg);
				if(logErr == ERR_WRITE_PROTECTED)
					rCode = logErr;
				else if(logErr == ERR_FILE_DAMAGED)
					rCode = logErr;
			}

			// Enable caption switch and pass argument to resolve caption file name
			*c = true;
			*capFname = mapgen::arghandler::argVal_resolve(rCode, SW_CAPTION, false, argv[i]);
			break;
		case swCapL:
			// Switch '--caption=<file.txt>'; this switch is expected to contain following data
			if(i == (argc - 1) && !(*h))
			{
				// If this is last argument and help switch is not defined, call this input error:
				rCode = ERR_INPUT_ARG_MISSING;
				std::string eMsg = construct_error("No input file specified!");
				std::cout << eMsg << std::endl;

				int logErr = mapgen::logger::log("error", eMsg);
				if(logErr == ERR_WRITE_PROTECTED)
					rCode = logErr;
				else if(logErr == ERR_FILE_DAMAGED)
					rCode = logErr;
			}

			// Enable caption switch and pass argument to resolve caption file name
			*c = true;
			*capFname = mapgen::arghandler::argVal_resolve(rCode, SW_CAPTION, true, argv[i]);
			break;
		case swHelpS:
			// Switch '-h'; this switch isn't expected to contain following data
			// This switch can be last one, it changes completely function of program
			if(argStr.length() != argSw.length())
			{
				// It's not '-h' switch, call for undefined switch:
				rCode = ERR_ARG_INVALID;
				std::string eMsg = construct_error(
					"Invalid argument `" + argStr + "`!"
					);
				std::cout << eMsg << std::endl;

				int logErr = mapgen::logger::log("error", eMsg);
				if(logErr == ERR_WRITE_PROTECTED)
					rCode = logErr;
				else if(logErr == ERR_FILE_DAMAGED)
					rCode = logErr;

				// Invalid argument is fairly reason to end process with error return code output
				break;
			}

			// Enable help switch
			*h = true;
			break;
		case swHelpL:
			// Switch '--help' or '--help=<switch>'; this switch is expected to contain following data
			// This switch can be last one, it changes completely function of program
			
			// Enable help switch and pass argument to resolve help file query
			*h = true;
			if(argStr.length() > argSw.length())
			{
				if(argStr.find("=") != argSw.length())
				{
					// It's not '--help', call for undefined switch:
					rCode = ERR_ARG_INVALID;
					std::string eMsg = construct_error("Invalid argument `" + argStr + "`!");
					std::cout << eMsg << std::endl;

					int logErr = mapgen::logger::log("error", eMsg);
					if(logErr == ERR_WRITE_PROTECTED)
						rCode = logErr;
					else if(logErr == ERR_FILE_DAMAGED)
						rCode = logErr;
	
					// Invalid argument is fairly reason to end process with error return code output
					break;
				}

				*hSwName = mapgen::arghandler::argVal_resolve(rCode, SW_HELP, true, argv[i]);
				if(*hSwName == "")
				{
					// Help file query not specified, this is an error!
					rCode = ERR_ARG_INVALID;
					std::string eMsg = construct_error("Invalid argument `" + argStr + "`! Specify a switch to display a help!");
					std::cout << eMsg << std::endl;

					int logErr = mapgen::logger::log("error", eMsg);
					if(logErr == ERR_WRITE_PROTECTED)
						rCode = logErr;
					else if(logErr == ERR_FILE_DAMAGED)
						rCode = logErr;
				}
			}

			break;
		case swVerbS:
			// Switch '-v'; this switch isn't expected to contain following data
			// Same as '--verbose', so pass below
		case swVerbL:
			// Switch '--verbose'

			// First check for invalid argument
			if(argStr.length() != argSw.length())
			{
				// It's not '-v' switch, call for undefined switch:
				rCode = ERR_ARG_INVALID;
				std::string eMsg = construct_error(std::string("Invalid argument `") + argv[i] + "`!");
				std::cout << eMsg << std::endl;

				int logErr = mapgen::logger::log("error", eMsg);
				if(logErr == ERR_WRITE_PROTECTED)
					rCode = logErr;
				else if(logErr == ERR_FILE_DAMAGED)
					rCode = logErr;

				// Invalid argument is fairly reason to end process with error return code output
				break;
			}

			// Then check for last argument and help
			if(i == (argc - 1) && !(*h))
			{
				// If this is last argument and help switch is not defined, call this input error:
				rCode = ERR_INPUT_ARG_MISSING;
				std::string eMsg = construct_error("No input file specified!");
				std::cout << eMsg << std::endl;

				int logErr = mapgen::logger::log("error", eMsg);
				if(logErr == ERR_WRITE_PROTECTED)
					rCode = logErr;
				else if(logErr == ERR_FILE_DAMAGED)
					rCode = logErr;
			}

			// Enable verbose switch
			*v = true;
			break;
		case swFootS:
			// Switch '-f<file.txt>; this switch is expected to contain following data
			if(i == (argc - 1) && !(*h))
			{
				// If this is last argument and help switch is not defined, call this input error:
				rCode = ERR_INPUT_ARG_MISSING;
				std::string eMsg = construct_error("No input file specified!");
				std::cout << eMsg << std::endl;

				int logErr = mapgen::logger::log("error", eMsg);
				if(logErr == ERR_WRITE_PROTECTED)
					rCode = logErr;
				else if(logErr == ERR_FILE_DAMAGED)
					rCode = logErr;
			}

			// Enable footer switch and pass argument to resolve footer file name
			*f = true;
			*ftFname = mapgen::arghandler::argVal_resolve(rCode, SW_FOOTER, false, argv[i]);
			break;
		case swFootL:
			// Switch '--footer=<file.txt>; this switch is expected to contain following data
			if(i == (argc - 1) && !(*h))
			{
				// If this is last argument and help switch is not defined, call this input error:
				rCode = ERR_INPUT_ARG_MISSING;
				std::string eMsg = construct_error("No input file specified!");
				std::cout << eMsg << std::endl;

				int logErr = mapgen::logger::log("error", eMsg);
				if(logErr == ERR_WRITE_PROTECTED)
					rCode = logErr;
				else if(logErr == ERR_FILE_DAMAGED)
					rCode = logErr;
			}

			// Enable footer switch and pass argument to resolve footer file name
			*f = true;
			*ftFname = mapgen::arghandler::argVal_resolve(rCode, SW_FOOTER, true, argv[i]);
			break;
			// More switches upon requests
		default:
			// Eighter input file name, or unrecognised argument

			// If an error occured during resolve, call this an unexpected error and break:
			if(rCode == ERR_UNEXPECTED)
				break;

			// If we're below end, call this invalid argument error and break:
			if(i < argc - 1)
			{
				rCode = ERR_ARG_INVALID;
				std::string eMsg = construct_error("Invalid argument `" + argStr + "`!");
				std::cout << eMsg << std::endl;

				int logErr = mapgen::logger::log("error", eMsg);
				if(logErr == ERR_WRITE_PROTECTED)
					rCode = logErr;
				else if(logErr == ERR_FILE_DAMAGED)
					rCode = logErr;

				// Invalid argument is fairly reason to end process with error return code output
				break;
			}

			// Since this is last argument, pass it to input file
			*inFname = argStr;
		}
	}

	return rCode;
}

std::string mapgen::arghandler::argSw_resolve(int rCode, int aType, bool argL, char *arg)
{
	std::string rStr = "";
	// Resolved string, initially empty
	std::string argStr(arg);
	// Convert char pointer to string

	switch(aType)
	{
	case SW_OUTPUT:
		// Switch '-o' or '--output'
		if(argL)
			rStr = argStr.substr(0, mapgen::arghandler::argSwOutL.length());
		else
			rStr = argStr.substr(0, mapgen::arghandler::argSwOutS.length());

		// If the resolved string is empty, we call this unexpected error:
		if(rStr == "")
		{
			rCode = ERR_UNEXPECTED;
			std::string eMsg = construct_error(
				"Unexpected error! Please contact developer\nor write a bug report on GitHub:\nhttps://github.com/Polda18/Windows-Kris-Kros-Game"
				);
			std::cout << eMsg << std::endl;

			int logErr = mapgen::logger::log("error", eMsg);
			if(logErr == ERR_WRITE_PROTECTED)
				rCode = logErr;
			else if(logErr == ERR_FILE_DAMAGED)
				rCode = logErr;
		}
		break;
	case SW_LANG:
		// Switch '-l' or '--lang'
		if(argL)
			rStr = argStr.substr(0, mapgen::arghandler::argSwLangL.length());
		else
			rStr = argStr.substr(0, mapgen::arghandler::argSwLangS.length());

		// If the resolved string is empty, we call this unexpected error:
		if(rStr == "")
		{
			rCode = ERR_UNEXPECTED;
			std::string eMsg = construct_error(
				"Unexpected error! Please contact developer\nor write a bug report on GitHub:\nhttps://github.com/Polda18/Windows-Kris-Kros-Game"
				);
			std::cout << eMsg << std::endl;

			int logErr = mapgen::logger::log("error", eMsg);
			if(logErr == ERR_WRITE_PROTECTED)
				rCode = logErr;
			else if(logErr == ERR_FILE_DAMAGED)
				rCode = logErr;
		}
		break;
	case SW_CAPTION:
		// Switch '-c' or '--caption'
		if(argL)
			rStr = argStr.substr(0, mapgen::arghandler::argSwCapL.length());
		else
			rStr = argStr.substr(0, mapgen::arghandler::argSwCapS.length());

		// If the resolved string is empty, we call this unexpected error:
		if(rStr == "")
		{
			rCode = ERR_UNEXPECTED;
			std::string eMsg = construct_error(
				"Unexpected error! Please contact developer\nor write a bug report on GitHub:\nhttps://github.com/Polda18/Windows-Kris-Kros-Game"
				);
			std::cout << eMsg << std::endl;

			int logErr = mapgen::logger::log("error", eMsg);
			if(logErr == ERR_WRITE_PROTECTED)
				rCode = logErr;
			else if(logErr == ERR_FILE_DAMAGED)
				rCode = logErr;
		}
		break;
	case SW_HELP:
		// Switch '-h' or '--help'
		if(argL)
			rStr = argStr.substr(0, mapgen::arghandler::argSwHelpL.length());
		else
			rStr = argStr.substr(0, mapgen::arghandler::argSwHelpS.length());

		// If the resolved string is empty, we call this unexpected error:
		if(rStr == "")
		{
			rCode = ERR_UNEXPECTED;
			std::string eMsg = construct_error(
				"Unexpected error! Please contact developer\nor write a bug report on GitHub:\nhttps://github.com/Polda18/Windows-Kris-Kros-Game"
				);
			std::cout << eMsg << std::endl;

			int logErr = mapgen::logger::log("error", eMsg);
			if(logErr == ERR_WRITE_PROTECTED)
				rCode = logErr;
			else if(logErr == ERR_FILE_DAMAGED)
				rCode = logErr;
		}
		break;
	case SW_VERBOSE:
		// Switch '-v' or '--verbose'
		if(argL)
			rStr = argStr.substr(0, mapgen::arghandler::argSwVerbL.length());
		else
			rStr = argStr.substr(0, mapgen::arghandler::argSwVerbS.length());

		// If the resolved string is empty, we call this unexpected error:
		if(rStr == "")
		{
			rCode = ERR_UNEXPECTED;
			std::string eMsg = construct_error(
				"Unexpected error! Please contact developer\nor write a bug report on GitHub:\nhttps://github.com/Polda18/Windows-Kris-Kros-Game"
				);
			std::cout << eMsg << std::endl;

			int logErr = mapgen::logger::log("error", eMsg);
			if(logErr == ERR_WRITE_PROTECTED)
				rCode = logErr;
			else if(logErr == ERR_FILE_DAMAGED)
				rCode = logErr;
		}
		break;
	case SW_FOOTER:
		// Switch '-f' or '--footer'
		if(argL)
			rStr = argStr.substr(0, mapgen::arghandler::argSwFootL.length());
		else
			rStr = argStr.substr(0, mapgen::arghandler::argSwFootS.length());

		// If the resolved string is empty, we call this unexpected error:
		if(rStr == "")
		{
			rCode = ERR_UNEXPECTED;
			std::string eMsg = construct_error(
				"Unexpected error! Please contact developer\nor write a bug report on GitHub:\nhttps://github.com/Polda18/Windows-Kris-Kros-Game"
				);
			std::cout << eMsg << std::endl;

			int logErr = mapgen::logger::log("error", eMsg);
			if(logErr == ERR_WRITE_PROTECTED)
				rCode = logErr;
			else if(logErr == ERR_FILE_DAMAGED)
				rCode = logErr;
		}
		break;
	default:
		rStr = std::string(argStr);
		
		// If the resolved string is empty, we call this unexpected error:
		if(rStr == "")
		{
			rCode = ERR_UNEXPECTED;
			std::string eMsg = construct_error(
				"Unexpected error! Please contact developer\nor write a bug report on GitHub:\nhttps://github.com/Polda18/Windows-Kris-Kros-Game"
				);
			std::cout << eMsg << std::endl;

			int logErr = mapgen::logger::log("error", eMsg);
			if(logErr == ERR_WRITE_PROTECTED)
				rCode = logErr;
			else if(logErr == ERR_FILE_DAMAGED)
				rCode = logErr;
		}
	}

	return rStr;
}

std::string mapgen::arghandler::argVal_resolve(int rCode, int aType, bool argL, char *arg)
{
	std::string rStr = "";
	// Resolved string, initially empty
	std::string argStr(arg);
	// Convert char pointer to string
	
	switch(aType)
	{
	case SW_OUTPUT:
		// Switch '-o' or '--output'
		// Follows the same procedure as '-l' or '--lang', pass to next
	case SW_LANG:
		// Switch: '-l' or '--lang'
		// Follows the same procedure as '-c' or '--caption', pass to next
	case SW_CAPTION:
		// Switch: '-c' or '--caption'
		// Follows the same procedure as '-f' or '--footer', pass to next
	case SW_FOOTER:
		// Switch: '-f' or '--footer'
		if(argL)
			rStr = argStr.substr(argStr.find("=") + 1);
		else
			rStr = argStr.substr(2);
		break;
	case SW_HELP:
		// Switch '-h' or '--help'
		// Short has no argument, long has one optional
		if(argL)
		{
			if(argStr.length() > mapgen::arghandler::argSwHelpL.length())
				rStr = argStr.substr(argStr.find("=") + 1);
		}
		break;
		// Switch '-v' or '--verbose' does not have anything to resolve, pass
		// Default has no meaning, pass
	}

	return rStr;
}