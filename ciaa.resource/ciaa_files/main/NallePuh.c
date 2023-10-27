/* :ts=4
 *  $VER: NallePuh.c $Revision$ (21-Sep-2023)
 *
 *  This file is part of ciaa.
 *
 *  Copyright (c) 2023 LiveForIt Software.
 *  MIT License.
 *
 * $Id$
 *
 * $Log$
 *
 *
 */

#include <stdbool.h>

#include <exec/exec.h>
#include <proto/exec.h>
#include <dos/dos.h>
#include <exec/types.h>
#include <exec/interrupts.h>
#include <exec/libraries.h>
#include <proto/ciaa.h>
#include <stdarg.h>

#include "../emu_cia.h"

/****** ciaa/main/NallePuh ******************************************
*
*   NAME
*      NallePuh -- Description
*
*   SYNOPSIS
*      struct Interrupt **NallePuh(ULONG state);
*
*   FUNCTION
*
*   INPUTS
*       state - 
*         if bit 15 is set, then set bits,
*         if bit 15 is clear, then clear bits.
*         bit 0 is NallePuh is running if set.
*
*   RESULT
*       This function does returns a list of 
*       Interrupt
*
*   EXAMPLE
*
*   NOTES
*
*   BUGS
*
*   SEE ALSO
*
*****************************************************************************
*
*/

int NallePuh_flags = 0;

extern struct Interrupt *cia_bitlist[4];
extern struct chip *local_chip;

BOOL _ciaa_NallePuh(struct ciaaIFace *Self, ULONG state, APTR chip)
{
	int bits = (state & 0x7FFF);
	NallePuh_flags = (state & 0x8000) ? (NallePuh_flags | bits) : (NallePuh_flags & ~bits);
	local_chip = chip;

	return cia_bitlist;
}

