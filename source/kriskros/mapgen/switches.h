/***********************************
 * Kris-Kros Game Kit
 *----------------------------------
 * Kris-Kros Map Generator source
 * File: switches.h
 *
 * Made by Marek Pol·Ëek
 * Github.com/Polda18
 *
 * GNU-GPL v3.0
 * 2019
 ***********************************/

#include <map>
#include <string>

#ifndef SWITCHES_H
#define SWITCHES_H

#define SW_UNDEFINED          0
#define SW_OUTPUT             1
#define SW_LANG               2
#define SW_CAPTION            3
#define SW_HELP               4
#define SW_VERBOSE            5

static enum swVal
{
	swUndef,
	swOutS,
	swOutL,
	swLangS,
	swLangL,
	swCapS,
	swCapL,
	swHelpS,
	swHelpL,
	swVerbS,
	swVerbL
};
static std::map<std::string, swVal> mapSwVal;

#endif
