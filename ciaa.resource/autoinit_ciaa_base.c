/*
**	$Id$
**	Generated by IDLTool 53.35
**	Do not edit
**
**	AutoInit stub for ciaa
**
**	Copyright (c) 2010 Hyperion Entertainment CVBA.
**	All Rights Reserved.
*/

#include <exec/types.h>
#include <exec/interrupts.h>
#include <exec/libraries.h>

#include <interfaces/ciaa.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <stdlib.h>

/****************************************************************************/

struct Library * ciaaBase = NULL;
static struct Library * __ciaaBase = NULL;

/****************************************************************************/

void _INIT_5_ciaaBase(void)
{
    if (ciaaBase != NULL)
    {
        return; /* Someone was quicker, e.g. an interface constructor */
    }
    __ciaaBase = ciaaBase = IExec->OpenLibrary("ciaa.resource", 0);
    if (ciaaBase == NULL)
    {
        BPTR StdErr = IDOS->ErrorOutput();
        if (StdErr == ZERO)
            StdErr = IDOS->Output();
        IDOS->FPrintf(StdErr, "ERROR: Failed to open '%s'.\n", "ciaa.resource");
        abort();
    }
}

#ifdef __GNUC__
__attribute__((section(".ctors.zzzz"))) static void
(*ciaa_base_constructor_ptr)(void) USED = _INIT_5_ciaaBase;
#endif

/****************************************************************************/

void _EXIT_5_ciaaBase(void)
{
    if (__ciaaBase != NULL)
    {
        IExec->CloseLibrary(__ciaaBase);
    }
}

#ifdef __GNUC__
__attribute__((section(".dtors.zzzz"))) static void
(*ciaa_base_destructor_ptr)(void) USED = _EXIT_5_ciaaBase;
#endif

/****************************************************************************/
