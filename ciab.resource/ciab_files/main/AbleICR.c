/* :ts=4
 *  $VER: AbleICR.c $Revision$ (21-Sep-2023)
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

#define __USE_INLINE__

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

/****** ciab/main/AbleICR ******************************************
*
*   NAME
*      AbleICR -- Description
*
*   SYNOPSIS
*      WORD AbleICR(struct Library * resource, WORD mask);
*
*   FUNCTION
*
*   INPUTS
*       resource - 
*       mask - 
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

extern struct chip *local_chip;

WORD _ciab_AbleICR(struct ciabIFace *Self, struct Library * resource, WORD mask)
{
	int old_interrupt_mask = 0;
	int bits = mask & 0x7F;

	if (local_chip)
	{
		old_interrupt_mask = local_chip -> interrupt_mask;
	
		local_chip -> interrupt_mask = mask & 0x80 ? 
			local_chip -> interrupt_mask | bits : 
			local_chip -> interrupt_mask & ~bits;
	}

	return old_interrupt_mask;
}

