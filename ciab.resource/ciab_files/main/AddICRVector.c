/* :ts=4
 *  $VER: AddICRVector.c $Revision$ (21-Sep-2023)
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

#include <stdbool.h>

#include <exec/exec.h>
#include <proto/exec.h>
#include <dos/dos.h>
#include <exec/types.h>
#include <exec/interrupts.h>
#include <exec/libraries.h>
#include <proto/ciab.h>
#include <stdarg.h>

#include "../emu_cia.h"

/****** ciab/main/AddICRVector ******************************************
*
*   NAME
*      AddICRVector -- Description
*
*   SYNOPSIS
*      struct Interrupt * AddICRVector(struct Library * resource, 
*          WORD iCRBit, struct Interrupt * interrupt);
*
*   FUNCTION
*
*   INPUTS
*       resource - 
*       iCRBit - 
*       interrupt - 
*
*   RESULT
*       The result ...
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

char *gready_name = "gready hamster";
struct Interrupt gready;

extern int NallePuh_flags;

#define NallePuh_is_running  (NallePuh_flags & 1)

extern struct chip *local_chip ;

struct Interrupt * _ciab_AddICRVector(struct ciabIFace *Self, struct Library * resource, WORD iCRBit, struct Interrupt * interrupt)
{
	if (NallePuh_is_running)
	{
		if (local_chip -> interrupts[iCRBit]) return local_chip -> interrupts[iCRBit];
		local_chip -> interrupts[iCRBit] = interrupt;
	}
	else
	{
		gready.is_Node.ln_Type = NT_INTERRUPT;
		gready.is_Node.ln_Pri = 0;
		gready.is_Node.ln_Name = (char *) gready_name;
		return &gready;
	}
}

