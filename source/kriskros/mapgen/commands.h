/***********************************
 * Kris-Kros Game Kit
 *----------------------------------
 * Kris-Kros Map Generator source
 * File: commands.h
 *
 * Made by Marek Pol·Ëek
 * Github.com/Polda18
 *
 * GNU-GPL v3.0
 * 2019
 ***********************************/

#include <string>

#ifndef COMMANDS_H
#define COMMANDS_H

//---------------------------------
// Help commands
//---------------------------------
void display_help(std::string pPathFname);
void display_help_option(std::string option);

//---------------------------------
// Conversion command
//---------------------------------
bool convert(std::string iIdxFname, int language, std::string iCapFname);

//---------------------------------
// Error output command
//---------------------------------
std::string construct_error(std::string eMsg);

#endif