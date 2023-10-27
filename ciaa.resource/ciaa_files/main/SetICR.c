/* :ts=4
 *  $VER: SetICR.c $Revision$ (21-Sep-2023)
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

/****** ciaa/main/SetICR ******************************************
*
*   NAME
*      SetICR -- Description
*
*   SYNOPSIS
*      WORD SetICR(struct Library * resource, WORD mask);
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

WORD _ciaa_SetICR(struct ciaaIFace *Self, struct Library * resource, WORD mask)
{
	ULONG old_mask = local_chip ? local_chip -> icr  : 0;

	DebugPrintF("CIAA: SetICR( xxxxx, mask: %02x)\n", mask );
	DebugPrintF("(ICR: %08x)\n", ICR);

	if (mask)	*( (char *) (0x00BFE001 | ICR)) = mask;

	return old_mask;
}

