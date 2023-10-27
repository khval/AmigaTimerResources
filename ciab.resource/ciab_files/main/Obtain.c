/* :ts=4
 *  $VER: Obtain.c $Revision$ (21-Sep-2023)
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

/****** ciab/main/Obtain ******************************************
*
*   NAME
*      Obtain -- Description
*
*   SYNOPSIS
*      ULONG Obtain(void);
*
*   FUNCTION
*
*   INPUTS
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

ULONG _ciab_Obtain(struct ciabIFace *Self)
{
    return Self -> Data.RefCount++;
}

