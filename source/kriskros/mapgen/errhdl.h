/***********************************
 * Kris-Kros Game Kit
 *----------------------------------
 * Kris-Kros Map Generator source
 * File: errhdl.h
 *
 * Made by Marek Pol·Ëek
 * Github.com/Polda18
 *
 * GNU-GPL v3.0
 * 2019
 ***********************************/

#ifndef ERRHDL_H
#define ERRHDL_H

namespace mapgen
{
	namespace error_handler
	{
		int handle_io_errors(int fType, int fOp);
	}
}

#endif
