/***********************************
 * Kris-Kros Game Kit
 *----------------------------------
 * Kris-Kros Map Generator source
 * File: arghdl.h
 *
 * Made by Marek Pol·Ëek
 * Github.com/Polda18
 *
 * GNU-GPL v3.0
 * 2019
 ***********************************/

#include <string>

#ifndef ARGHDL_H
#define ARGHLD_H

namespace mapgen
{
	namespace arghandler
	{
		const std::string argSwOutS  = "-o";
		const std::string argSwOutL  = "--output=";
		const std::string argSwLangS = "-l";
		const std::string argSwLangL = "--lang=";
		const std::string argSwCapS  = "-c";
		const std::string argSwCapL  = "--caption=";
		const std::string argSwHelpS = "-h";
		const std::string argSwHelpL = "--help";
		const std::string argSwVerbS = "-v";
		const std::string argSwVerbL = "--verbose";
		const std::string argSwFootS = "-f";
		const std::string argSwFootL = "--footer=";
		
		int handle_args(int argc, char **argv,
			std::string *inFname,
			std::string *outFname,
			std::string *capFname,
			std::string *ftFname,
			std::string *hSwName,
			std::string *lang,
			bool *h, bool *o, bool *v, bool *c, bool *f, bool *l);

		std::string argSw_resolve(int rCode, int aType, bool argL, char *arg);
		std::string argVal_resolve(int rCode, int aType, bool argL, char *arg);
	}
}

#endif