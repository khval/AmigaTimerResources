/* :ts=4
 *  $VER: RemICRVector.c $Revision$ (21-Sep-2023)
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

/****** ciab/main/RemICRVector ******************************************
*
*   NAME
*      RemICRVector -- Description
*
*   SYNOPSIS
*      VOID RemICRVector(struct Library * resource, WORD iCRBit, 
*          struct Interrupt * interrupt);
*
*   FUNCTION
*
*   INPUTS
*       resource - 
*       iCRBit - 
*       interrupt - 
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

WORD _ciab_AbleICR(struct ciaaIFace *Self, struct Library * resource, WORD mask);

extern struct chip *local_chip ;

VOID _ciab_RemICRVector(struct ciabIFace *Self, struct Library * resource, WORD iCRBit, struct Interrupt * interrupt)
{
	bool success = false;
	int b;

	DebugPrintF("RemICRVector( iCRBit: %d, interrupt: %08x)\n",iCRBit,interrupt);

	_ciab_AbleICR( Self, resource, 1<< iCRBit );

	if (local_chip)
	{
		for (b=0;b<2;b++)
		{

			if (local_chip -> interrupts[iCRBit] == interrupt)
			{
				local_chip -> interrupts[iCRBit] = NULL;
				success = true;
			}
		}
	}

	if (!success)
	{
		DebugPrintF("failed to remove Interrupt!\n");
	}
}

