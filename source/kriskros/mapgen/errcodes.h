/***********************************
 * Kris-Kros Game Kit
 *----------------------------------
 * Kris-Kros Map Generator source
 * File: errcodes.h
 *
 * Made by Marek Pol·Ëek
 * Github.com/Polda18
 *
 * GNU-GPL v3.0
 * 2019
 ***********************************/

#ifndef ERRCODES_H
#define ERRCODES_H

#define ERR_ARG_INVALID                 1
#define ERR_INPUT_ARG_MISSING           2
#define ERR_WRITE_PROTECTED             3
#define ERR_FILE_FORMAT_INCORRECT       4
#define ERR_FILE_NOT_FOUND              5
#define ERR_FILE_DAMAGED                6
#define ERR_FOLDER_NOT_FOUND            7
#define ERR_INSUFFICIENT_PERMISSION     8
#define ERR_TOO_MANY_FILES_OPEN         9
#define ERR_FILE_IS_FOLDER             10
#define ERR_FILE_NAME_TOO_LONG         11
#define ERR_FILE_TOO_BIG               12
#define ERR_MEMORY_FULL                13
#define ERR_DISK_FULL                  14
#define ERR_PERMISSION_DENIED          15
#define ERR_INTERRUPTED                16
// Next error codes based on requests

#define ERR_UNEXPECTED               99
// Unexpected error, return code may be raised if reached in future (highly unlikely)

#endif