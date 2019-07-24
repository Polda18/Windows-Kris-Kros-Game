/***********************************
 * Kris-Kros Game Kit
 *----------------------------------
 * Kris-Kros Map Generator source
 * File: convert.h
 *
 * Made by Marek Pol·Ëek
 * Github.com/Polda18
 *
 * GNU-GPL v3.0
 * 2019
 ***********************************/

#include <fstream>
#include <string>

#ifndef CONVERT_H
#define CONVERT_H

typedef struct
{
	int x,y;
} map_pos_t;

namespace mapgen
{
	namespace converter
	{
		namespace tags
		{
			static const std::string map_begin_tag     = "BEGINMAP";
			static const std::string map_begin_pcx     = "PCX";
			static const std::string map_begin_lang    = "LANG";
			static const std::string map_begin_caption = "CAPTION";
			static const std::string map_begin_footer  = "FOOTER";

			static const std::string map_end_tag       = "ENDMAP";
			static const std::string map_comment_tag   = "COMMENT";
			
			static const std::string map_index_tag     = "INDEX";
		}
		
		int convert(bool v, bool o, bool c, bool f, bool l,
			std::string inFname,
			std::string outFname,
			std::string capFname,
			std::string ftFname,
			std::string lang);
		int parse_pcx(std::ifstream inFile, std::ofstream outFile, std::ofstream lFile,
			std::string inFname, std::string outFname,
			bool v, bool o, bool c, bool f, bool l, bool *fail);
		int write_map(std::ofstream outFile, std::string *content,
			bool v, bool o, bool c, bool f, bool l, bool *fail);
	}
}

#endif