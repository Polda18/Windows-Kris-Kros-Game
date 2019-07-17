/***********************************
 * Kris-Kros Game Kit
 *----------------------------------
 * Kris-Kros Map Generator source
 * File: commands.cpp
 *
 * Made by Marek Pol·Ëek
 * Github.com/Polda18
 *
 * GNU-GPL v3.0
 * 2019
 ***********************************/

#include <iostream>
#include <string>

#include "commands.h"
#include "errcodes.h"
#include "switches.h"
#include "helper.h"

//---------------------------------
// Help commands
//---------------------------------

void display_help(std::string pFpathFname)
{
	// Windows 9x puts full path filename into the argv[0]
	// Because of that we need to do directory separation
	// It's also required in case of remote call
	// (relative or absolute path of the executable)
	// in later versions of Windows that put command line
	// external command call in argv[0] instead
	std::string pFname;  // Initialize the filename string var
	size_t pFnameLpidx = pFpathFname.rfind("/");
						// Get index of last path directory '/' separator
	if(pFnameLpidx == std::string::npos)
	{
		// Since Windows uses '\' for directory separator,
		// Check for '/' is just for conditional purpose
		// if program is called remotely using '/' delim.
		pFnameLpidx = pFpathFname.rfind("\\");
					// Get index of last path directory '\' separator
		pFname = pFpathFname.substr(pFnameLpidx + 1);
					// Save purely just file name
	}
	else
	{
		pFname = pFpathFname.substr(pFnameLpidx + 1);
				// Save purely just file name
	}

	std::string pName;  // Initialize the program name
				// (filename without executable extension)
	size_t pNameLeidx = pFname.rfind(".");
						// Get index of last '.' separator (extension sep.)
	pName = pFname.substr(0, pNameLeidx);
				// Save purely just program name without extension
	
	std::cout << "Usage: " << pName << " [options] input.pcx" << std::endl;
	std::cout << "where `input.pcx` is the name of the input PCX index map." << std::endl << std::endl;
	
	std::cout << "Options:" <<std::endl;
	std::cout << "  -ofile.map, --output=file.map  > Output to a different file name" << std::endl;
	std::cout << "                                   (`file.map`) than input" << std::endl;
	std::cout << "  -lcode, --lang=code            > Change language (default English)" << std::endl;
	std::cout << "                                   Codes: `en` (English)" << std::endl;
	std::cout << "                                          `cz` (Czech)" << std::endl;
	std::cout << "                                          (more to be added upon request)" << std::endl;
	std::cout << "  -cfile.txt, --caption=file.txt > Add caption text file right away" << std::endl;
	std::cout << "                                   (default not used)" << std::endl;
	std::cout << "  -v, --verbose                  > Verbose (detailed) output" << std::endl;
	std::cout << "  -ffile.txt, --footer=file.txt  > Add footer text file right away" << std::endl;
	std::cout << "  -h, --help                     > Display this usage" << std::endl;
	std::cout << "      --help=option              > Display detailed help on specified `option`" << std::endl;
	std::cout << "                                   (do not include preceding dashes and parms)" << std::endl << std::endl;
	
	//TODO: include GitHub repository link
	std::cout << "If you have suggestion(s), please send them to GitHub issue tracker" << std::endl;
	std::cout << "(https://www.github.com/Polda18/Windows-Kris-Kros-Game)" << std::endl;
}

void display_help_option(std::string option)
{
	// Initialize map of strings to enumeration values
	mapSwVal["o"]        = swOutS;
	mapSwVal["output"]   = swOutL;
	mapSwVal["l"]        = swLangS;
	mapSwVal["lang"]     = swLangL;
	mapSwVal["c"]        = swCapS;
	mapSwVal["caption"]  = swCapL;
	mapSwVal["h"]        = swHelpS;
	mapSwVal["help"]     = swHelpL;
	mapSwVal["v"]        = swVerbS;
	mapSwVal["verbose"]  = swVerbL;
	mapSwVal["f"]        = swFootS;
	mapSwVal["footer"]   = swFootL;
	// More switches upon request

	switch(mapSwVal[option])
	{
	case swOutS:
		// Switch 'o'
		// Same as 'output', so pass below
	case swOutL:
		// Switch 'output'
		mapgen::helper::option_help(SW_OUTPUT);
		break;  // Stop signature before next switch
	case swLangS:
		// Switch 'l'
		// Same as 'lang', so pass below
	case swLangL:
		// Switch 'lang'
		mapgen::helper::option_help(SW_LANG);
		break;
	case swCapS:
		// Switch 'c'
		// Same as 'caption', so pass below
	case swCapL:
		// Switch 'caption'
		mapgen::helper::option_help(SW_CAPTION);
		break;
	case swHelpS:
		// Switch 'h'
		// Same as 'help', so pass below
	case swHelpL:
		// Switch 'help'
		mapgen::helper::option_help(SW_HELP);
		break;
	case swVerbS:
		// Switch 'v'
		// Same as 'verbose', so pass below
	case swVerbL:
		// Switch 'verbose'
		mapgen::helper::option_help(SW_VERBOSE);
		break;
	case swFootS:
		// Switch 'f'
		// Same as 'footer', so pass below
	case swFootL:
		// Switch 'footer'
		mapgen::helper::option_help(SW_FOOTER);
		break;
		// More switches upon request
	default:
		// Unrecognised switch
		// Call for undefined switch help
		mapgen::helper::option_help(SW_UNDEFINED);
	}
}

//---------------------------------
// Conversion command
//---------------------------------

bool convert(std::string iIdxFname, int language, std::string iCapFname)
{
	bool rCode = true;

	//TODO

	return rCode;
}

//---------------------------------
// Error output command
//---------------------------------

std::string construct_error(std::string eMsg)
{
	return "ERROR! >>> " + eMsg;
}