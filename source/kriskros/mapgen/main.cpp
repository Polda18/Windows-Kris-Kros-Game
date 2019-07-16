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
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <string>

// Resources
#include "resource.h"
#include "afxres.h"

// Local libraries
#include "commands.h"
#include "convert.h"
#include "errcodes.h"

// TODO: Console API code
int main(int argc, char **argv)
{
	std::cout << "---------------------------------------" << std::endl;
	std::cout << "  Kris-Kros Map Generator, v1.0" << std::endl;
	std::cout << "  Made by Marek Polacek (@Polda18)" << std::endl << std::endl;
	
	std::cout << "  Licenced under GNU-GPL v3.0, 2019" << std::endl;
	std::cout << "---------------------------------------" << std::endl << std::endl;

	int rCode = 0;  // Return error code (error level, begins with 0 = no error)
	bool v, h, o, c;
	// Switches: verbose, help, output, caption

	if(argc > 1)
	{
		//TODO: check arguments
		for(int i = 1; i < argc; ++i)
		{
			std::cout << "argv[" << i << "]=\"" << argv[i] << "\"" << std::endl;
		}
		std::cout << "> Not implemented yet ..." << std::endl;
		// Temporary constructor
	}
	else
	{
		// No arguments given, display help
		display_help(argv[0]);
		//display_help_option("u");  // Temporary constructor
	}

	return rCode;
}