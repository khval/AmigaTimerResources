/* :ts=4
 *  $VER: NallePuh.c $Revision$ (21-Sep-2023)
 *
 *  This file is part of ciab.
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


#include <exec/exec.h>
#include <proto/exec.h>
#include <dos/dos.h>
#include <exec/types.h>
#include <exec/interrupts.h>
#include <exec/libraries.h>
#include <proto/ciab.h>
#include <stdarg.h>

/****** ciab/main/NallePuh ******************************************
*
*   NAME
*      NallePuh -- Description
*
*   SYNOPSIS
*      void NallePuh(ULONG state);
*
*   FUNCTION
*
*   INPUTS
*       state - 
*
*   RESULT
*       This function does not return a result
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

BOOL _ciab_NallePuh(struct ciabIFace *Self, ULONG state, APTR chip)
{
	int bits = (state & 0x7FFF);
	NallePuh_flags = (state & 0x8000) ? (NallePuh_flags | bits) : (NallePuh_flags & ~bits);

	local_chip = chip;
	
	return TRUE;
}

