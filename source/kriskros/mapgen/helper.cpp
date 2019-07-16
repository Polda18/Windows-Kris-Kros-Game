/***********************************
 * Kris-Kros Game Kit
 *----------------------------------
 * Kris-Kros Map Generator source
 * File: helper.cpp
 *
 * Made by Marek Pol·Ëek
 * Github.com/Polda18
 *
 * GNU-GPL v3.0
 * 2019
 ***********************************/

#include <iostream>
#include <string>

#include "switches.h"
#include "helper.h"

namespace mapgen
{
	namespace helper
	{
		namespace
		{
			// Anonymous namespace for private functions
			void _caption(std::string caption)
			{
				std::cout << "=== Help file for: " << caption << " ==="
					<< std::endl << std::endl;
			}

			void _endhelp(void)
			{
				std::cout << "=== End of help file ===" << std::endl;
			}

			void _filenames(void)
			{
				std::cout << "It is wise to write file names without spaces." << std::endl;
				std::cout << "You can however wrap it with double quotes (`\"`)" << std::endl;
				std::cout << "to allow spaces in file name on Windows." << std::endl << std::endl;
			}

			void help_output(void)
			{
				_caption("(`o` | `output`)");

				std::cout << "Use switch `o` or `output` to change output filename" << std::endl;
				std::cout << "(original PCX index file name will be linked inside)."
					<< std::endl << std::endl;

				std::cout << "Usage: `-ofile.map` or `--output=file.map`" << std::endl << std::endl;

				std::cout << "Resulting effect is putting linked PCX index map" << std::endl;
				std::cout << "in generated text map using `PCXMAP[filename.pcx]`" << std::endl;
				std::cout << "at the beginning of the file (more info can be read" << std::endl;
				std::cout << "in `howto.htm` file shipped in downloaded ZIP)."
					<< std::endl << std::endl;

				_filenames();
				_endhelp();
			}

			void help_lang()
			{
				_caption("(`l` | `lang`)");

				std::cout << "Use switch `l` or `lang` to change output language" << std::endl;
				std::cout << "(default is English)." << std::endl << std::endl;

				std::cout << "Usage: `-l<code>` or `--lang=<code>`" << std::endl << std::endl;

				std::cout << "Replace `<code>` with one of these:" << std::endl;
				std::cout << "  cz  => Czech" << std::endl;
				std::cout << "  en  => English" << std::endl << std::endl;

				std::cout << "This code will be used in resulting text map." << std::endl;
				std::cout << "Kris-Kros game currently support only those" << std::endl;
				std::cout << "two languages. If you want more, post request" << std::endl;
				std::cout << "to linked Github repository:" <<std::endl;
				std::cout << "https://www.github.com/Polda18/Windows-Kris-Kros-Game.git"
					<< std::endl << std::endl;

				_endhelp();
			}

			void help_caption()
			{
				_caption("(`c` | `caption`)");

				std::cout << "Use switch `c` or `caption` to attach caption text file."
					<< std::endl << std::endl;

				std::cout << "Usage: `-c<caption.txt>` or `--caption=<caption.txt>`"
					<< std::endl << std::endl;

				std::cout << "Replace `<caption.txt>` with filename of your caption." << std::endl;
				std::cout << "This file will be linked in resulting text map." << std::endl;
				std::cout << "Caption files are text files with standard extension" << std::endl;
				std::cout << "associated in Windows. It supports markup language" << std::endl;
				std::cout << "specific for Kris-Kros game app to include solution." << std::endl;
				std::cout << "If you want no caption, do not use this switch."
					<< std::endl << std::endl;

				_filenames();
				_endhelp();
			}

			void help_help()
			{
				_caption("(`h` | `help`)");

				std::cout << "This switch (`h` or `help`) is rather interesting," << std::endl;
				std::cout << "because it's usage can be with or without parameter."
					<< std::endl << std::endl;

				std::cout << "Usage: `-h` or `--help` for quick overview" << std::endl;
				std::cout << "       `--help=<switch>` for detailed help" << std::endl << std::endl;

				std::cout << "If you want to display detailed help, replace" << std::endl;
				std::cout << "`<switch>` with the switch you want without" << std::endl;
				std::cout << "leading dashes. Also don't forget that switches" << std::endl;
				std::cout << "are case-sensitive! Currently, all switches are" << std::endl;
				std::cout << "lower-case, so do not try to run program with" << std::endl;
				std::cout << "upper-case switches. File names are from nature" << std::endl;
				std::cout << "of Windows case-insensitive, however, that doesn't apply" << std::endl;
				std::cout << "to Unix based OSes where filenames are case-sensitive."
					<< std::endl << std::endl;

				_endhelp();
			}

			void help_verbose()
			{
				_caption("(`v` | `verbose`)");

				std::cout << "Use switch `v` or `verbose` to enable detailed output."
					<< std::endl << std::endl;

				std::cout << "Usage: `-v` or `--verbose`" << std::endl << std::endl;

				std::cout << "When to use verbose output? While developing," << std::endl;
				std::cout << "detailed verbose output is especially useful" << std::endl;
				std::cout << "for debugging purposes. Normally, this program" << std::endl;
				std::cout << "only puts verbose output to log file (`convert.log`)." << std::endl;
				std::cout << "This switch causes it to output it to command line" << std::endl;
				std::cout << "window as well (all output is logged in the log file)." << std::endl;
				std::cout << "To view this log file, enter `type convert.log`" << std::endl;
				std::cout << "into command line interface after completion" << std::endl;
				std::cout << "of the process. Use `|` pipe modifier to read" << std::endl;
				std::cout << "from beginning on Windows 9x: `type convert.log | more`" << std::endl;
				std::cout << "Windows 9x doesn't have buffer enabled by default."
					<< std::endl << std::endl;

				_endhelp();
			}
			// More switches upon request

			void help_undef()
			{
				_caption("`undefined`");

				std::cout << "Sorry, it looks like you want to display help" << std::endl;
				std::cout << "for undefined switch. There's no help file" << std::endl;
				std::cout << "for this undefined entry. Pick one of these:" << std::endl;
				std::cout << " -  (`o` | `output`)" << std::endl;
				std::cout << " -  (`l` | `lang`)" << std::endl;
				std::cout << " -  (`c` | `caption`)" << std::endl;
				std::cout << " -  (`v` | `verbose`)" << std::endl;
				std::cout << " -  (`h` | `help`)" << std::endl << std::endl;
				// More switches upon request

				std::cout << "Usage: `--help=<switch>` where `<switch>` is one of listed."
					<< std::endl << std::endl;

				_endhelp();
			}
		}
		
		// Only public function
		void option_help(int sw)
		{
			switch(sw)
			{
				// Switcher of switches (pun intended)
			case SW_OUTPUT:
				help_output();
				break;
			case SW_LANG:
				help_lang();
				break;
			case SW_CAPTION:
				help_caption();
				break;
			case SW_HELP:
				help_help();
				break;
			case SW_VERBOSE:
				help_verbose();
				break;
				// More switches upon request
			default:
				help_undef();
			}
		}
	}
}
