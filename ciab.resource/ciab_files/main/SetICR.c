/* :ts=4
 *  $VER: SetICR.c $Revision$ (21-Sep-2023)
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

/****** ciab/main/SetICR ******************************************
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

WORD _ciab_SetICR(struct ciabIFace *Self,
       struct Library * resource,
       WORD mask)
{
	ULONG old_mask = local_chip ? local_chip -> icr  : 0;

	*( (char *) (0x00BFE001 | ICR)) = mask;

	return old_mask;
}

