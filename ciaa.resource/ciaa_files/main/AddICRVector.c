/* :ts=4
 *  $VER: AddICRVector.c $Revision$ (21-Sep-2023)
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

#define __USE_INLINE__

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

/****** ciaa/main/AddICRVector ******************************************
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

extern WORD _ciaa_SetICR(struct ciaaIFace *Self, struct Library * resource, WORD mask);

struct Interrupt * _ciaa_AddICRVector(struct ciaaIFace *Self, struct Library * resource, WORD iCRBit,  struct Interrupt * interrupt)
{
	DebugPrintF("CIAA: AddICRVector( xxxxx, ICR_bit: %d , interrupt: %08x\n", iCRBit, interrupt);

	if (NallePuh_is_running)
	{
		if (local_chip -> interrupts[iCRBit]) return local_chip -> interrupts[iCRBit];
		local_chip -> interrupts[iCRBit] = interrupt;

		disasm( interrupt -> is_Code );

	}
	else
	{
		gready.is_Node.ln_Type = NT_INTERRUPT;
		gready.is_Node.ln_Pri = 0;
		gready.is_Node.ln_Name = (char *) gready_name;
		gready.is_Code = 0x0;
		gready.is_Data = 0x0;
		return &gready;
	}
}

