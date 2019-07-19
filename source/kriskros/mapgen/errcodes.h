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

#define ERR_ARG_INVALID               1
#define ERR_FILE_FORMAT_INCORRECT     2
#define ERR_FILE_NOT_FOUND            3
#define ERR_FILE_WRITE_PROTECTED      4
#define ERR_FILE_DAMAGED              5
#define ERR_FOLDER_NOT_FOUND          6
#define ERR_FOLDER_WRITE_PROTECTED    7
#define ERR_FOLDER_DAMAGED            8
#define ERR_INSUFFICIENT_PERMISSION   9
// Next error codes based on requests

#define ERR_UNEXPECTED               99
// Unexpected error, return code may be raised if reached in future (highly unlikely)

#endif