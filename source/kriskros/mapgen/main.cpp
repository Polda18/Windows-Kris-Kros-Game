/***********************************
 * Kris-Kros Game Kit
 *----------------------------------
 * Kris-Kros Map Generator source
 * File: main.cpp
 *
 * Made by Marek Pol·Ëek
 * Github.com/Polda18
 *
 * GNU-GPL v3.0
 * 2019
 ***********************************/

// Global API libraries
#include <iostream>
#include <string>

// Resources
#include "resource.h"
#include "afxres.h"

// Local libraries
#include "commands.h"
#include "convert.h"
#include "errcodes.h"
#include "arghdl.h"

// TODO: Console API code
int main(int argc, char **argv)
{
	std::cout << "---------------------------------------" << std::endl;
	std::cout << "  Kris-Kros Map Generator, v1.0" << std::endl;
	std::cout << "  Made by Marek Polacek (@Polda18)" << std::endl << std::endl;
	
	std::cout << "  Licenced under GNU-GPL v3.0, 2019" << std::endl;
	std::cout << "---------------------------------------" << std::endl << std::endl;

	int rCode = 0;  // Return error code (error level, begins with 0 = no error)
	bool v, h, o, c, f, l;
	v = h = o = c = f = l = false;
	// Switches: verbose, help, output, caption, footer

	std::string outFname, hSwName, capFname, ftFname, inFname, lang;
	lang = inFname = ftFname = capFname = hSwName = outFname = "";
	// Arguments: language, input file, footer file, caption file, help file, output file

	if(argc > 1)
	{
		// Handle arguments given from command line
		rCode = mapgen::arghandler::handle_args(argc, argv,
			&inFname, &outFname, &capFname, &ftFname, &hSwName, &lang, &h, &o, &v, &c, &f, &l);

		// Check if there didn't occur any error
		if(rCode == 0)
		{
			if(h)
			{
				// Help switch enabled, ignore anything else
				if(hSwName.length() > 0)
					// Specified help file, display this one
					display_help_option(hSwName);
				else
					// No help file specified, display usage help
					display_help(argv[0]);
			}
			else
				// Help switch not enabled, let's try to convert
				rCode = mapgen::converter::convert(v, o, c, f, l,
				inFname, outFname, capFname, ftFname, lang);
		}
	}
	else
	{
		// No arguments given, display usage help
		display_help(argv[0]);
		//display_help_option("file");  // Temporary constructor
	}

	return rCode;
}