/***********************************
 * Kris-Kros Game Kit
 *----------------------------------
 * Kris-Kros Map Generator source
 * File: errhdl.cpp
 *
 * Made by Marek Pol·Ëek
 * Github.com/Polda18
 *
 * GNU-GPL v3.0
 * 2019
 ***********************************/

#include <iostream>
#include <fstream>
#include <string>
#include <cerrno>

#include "errcodes.h"
#include "commands.h"
#include "ftypes.h"
#include "errhdl.h"

int mapgen::error_handler::handle_io_errors(int fType, int fOp, std::ofstream lFile = NULL)
{
	int rCode = 0;

	//todo
	switch(fType)
	{
	case FILE_TYPE_LOG:
		// Log file encountered
		switch(fOp)
		{
		case FILE_READ:
			switch(errno)
			{
			case EISDIR:
				// Trying to open directory instead of file
				rCode = ERR_FILE_IS_FOLDER;
				std::cerr << construct_error("Trying to open folder instead of log file!") << std::endl;
				break;
			case EINTR:
				// Interrupted
				rCode = ERR_INTERRUPTED;
				std::cerr << construct_error("Interrupted!") << std::endl;
				break;
			case EBADF:
				// Bad file number (might be caused by damaged file, pass below)
			case EDEADLOCK:
				// Dead lock (considered damaged file)
				rCode = ERR_FILE_DAMAGED;
				std::cerr << construct_error("Log file could not open! It might be damaged!") << std::endl;
				break;
			case ENAMETOOLONG:
				// Name too long
				rCode = ERR_FILE_NAME_TOO_LONG;
				std::cerr << construct_error("Log file name is too long!") << std::endl;
				break;
			case ENFILE:
				// Too many files open on system (same as below, pass)
			case EMFILE:
				// Too many files on thread
				rCode = ERR_TOO_MANY_FILES_OPEN;
				std::cerr << construct_error("Too many files are open!") << std::endl;
				break;
			case ENOMEM:
				// Memory full
				rCode = ERR_MEMORY_FULL;
				std::cerr << construct_error("No free memory can be found! Log file open failed!") << std::endl;
				break;
			case EFBIG:
				// File is too big to open
				rCode = ERR_FILE_TOO_BIG;
				std::cerr << construct_error("Log file couldn't be open! Too big file!") << std::endl;
				break;
			case EACCES:
				// Access fail (read-only file or folder)
				// Same as below, pass down
			case EROFS:
				// Read-only file system
				rCode = ERR_WRITE_PROTECTED;
				std::cerr << construct_error("Log file or container folder is write protected!") << std::endl;
				break;
			case EPERM:
				// Permission denied
				rCode = ERR_PERMISSION_DENIED;
				std::cerr << construct_error("Log file requires elevated permissions to open!") << std::endl;
				break;
				// If anyone finds anything else that could apply, please, let me know
				// github.com/Polda18/Windows-Kris-Kros-Game/issues
			default:
				// Anything else failed? Unexpected error
				rCode = ERR_UNEXPECTED;
				std::cerr << construct_error("Unexpected error! Please contact developer\nPolda18 @GitHub.com") << std::endl;
			}
			break;
		case FILE_WRITE:
			switch(errno)
			{
			case EPERM:
				// Permission denied
				rCode = ERR_PERMISSION_DENIED;
				std::cerr << construct_error("Log file requires elevated permissions to write!") << std::endl;
				break;
			case EINTR:
				// Interrupted
				rCode = ERR_INTERRUPTED;
				std::cerr << construct_error("Interrupted!") << std::endl;
				break;
			case EDEADLOCK:
				// Deadlock, file may be damaged
				// pass down
			case EIO:
				// Input/output error - in this case input
				rCode = ERR_FILE_DAMAGED;
				std::cerr << construct_error("Log file write failed! It might be damaged!") << std::endl;
				break;
			case ENOMEM:
				// Memory full
				rCode = ERR_MEMORY_FULL;
				std::cerr << construct_error("No free memory can be found! Log file write failed!") << std::endl;
				break;
			case ENOSPC:
				// No free space on disk
				rCode = ERR_DISK_FULL;
				std::cerr << construct_error("No free space on disk!") << std::endl;
				break;
			case EACCES:
				// Access fail (read-only file or folder)
				// Same as below, pass down
			case EROFS:
				// Read-only file system
				rCode = ERR_WRITE_PROTECTED;
				std::cerr << construct_error("Log file or container folder is write protected!") << std::endl;
				break;
				// If anyone finds anything else that could apply, please, let me know
				// github.com/Polda18/Windows-Kris-Kros-Game/issues
			default:
				// Anything else failed? Unexpected error
				rCode = ERR_UNEXPECTED;
				std::cerr << construct_error("Unexpected error! Please contact developer:\ngithub.com/Polda18/Windows-Kris-Kros-Game/issues") << std::endl;
			}
			break;
		default:
			// This is invalid statement!
			rCode = ERR_UNEXPECTED;
			std::cerr << construct_error("Internal error! Please contact developer:\ngithub.com/Polda18/Windows-Kris-Kros-Game/issues") << std::endl;
		}
		break;
	case FILE_TYPE_BIN:
		// Binary PCX file encountered
		switch(fOp)
		{
		case FILE_READ:
			//todo switch(errno)
			break;
		case FILE_WRITE:
			//todo switch(errno)
			break;
		default:
			// This is invalid statement!
			rCode = ERR_UNEXPECTED;
			std::cerr << construct_error("Internal error! Please contact developer:\ngithub.com/Polda18/Windows-Kris-Kros-Game/issues") << std::endl;
		}
		break;
	case FILE_TYPE_TXT:
		// Text MAP file encountered
		switch(fOp)
		{
		case FILE_READ:
			//todo switch(errno)
			break;
		case FILE_WRITE:
			//todo switch(errno)
			break;
		default:
			// This is invalid statement!
			rCode = ERR_UNEXPECTED;
			std::cerr << construct_error("Internal error! Please contact developer:\ngithub.com/Polda18/Windows-Kris-Kros-Game/issues") << std::endl;
		}
		break;
	default:
		// This is invalid statement!
		rCode = ERR_UNEXPECTED;
		std::cerr << construct_error("Internal error! Please contact developer:\ngithub.com/Polda18/Windows-Kris-Kros-Game/issues") << std::endl;
	}

	return rCode;
}
