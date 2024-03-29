/***********************************
 * Kris-Kros Game Kit
 *----------------------------------
 * Kris-Kros Map Generator source
 * File: pcxhead.h
 *
 * Made by Marek Pol��ek
 * Github.com/Polda18
 *
 * GNU-GPL v3.0
 * 2019
 ***********************************/

#include <windows.h>

#ifndef PCXHEAD_H
#define PCXHEAD_H

typedef struct _PcxHeader
{
	BYTE	Identifier;        // PCX Id Number (Always 0x0A)
	BYTE	Version;           // Version Number
	BYTE	Encoding;          // Encoding Format
	BYTE	BitsPerPixel;      // Bits per Pixel
	WORD	XStart;            // Left of image
	WORD	YStart;            // Top of Image
	WORD	XEnd;              // Right of Image
	WORD	YEnd;              // Bottom of image
	WORD	HorzRes;           // Horizontal Resolution
	WORD	VertRes;           // Vertical Resolution
	BYTE	Palette[48];       // 16-Color EGA Palette
	BYTE	Reserved1;         // Reserved (Always 0)
	BYTE	NumBitPlanes;      // Number of Bit Planes
	WORD	BytesPerLine;      // Bytes per Scan-line
	WORD	PaletteType;       // Palette Type
	WORD	HorzScreenSize;    // Horizontal Screen Size
	WORD	VertScreenSize;    // Vertical Screen Size
	BYTE	Reserved2[54];     // Reserved (Always 0)
} PCXHEAD;

#endif