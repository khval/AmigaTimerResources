/*
**	$Id$
**	Generated by IDLTool 53.35
**	Do not edit
**
**	AutoInit stub for ciab
**
**	Copyright (c) 2010 Hyperion Entertainment CVBA.
**	All Rights Reserved.
*/

#include <exec/types.h>
#include <exec/interrupts.h>
#include <exec/libraries.h>

#include <interfaces/ciab.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <stdlib.h>

struct ciabIFace * Iciab = NULL;
static struct Library * __ciabBase = NULL;
static struct ciabIFace * __Iciab = NULL;

/****************************************************************************/

extern struct Library * ciabBase;

/****************************************************************************/

void _INIT_5_Iciab(void)
{
    if (Iciab != NULL)
    {
        return; /* Someone was quicker */
    }
    if (ciabBase == NULL) /* Library base is NULL, we need to open it */
    {
        /* We were called before the base constructor.
         * This means we will be called _after_ the base destructor.
         * So we cant drop the interface _after_ closing the last library base,
         * we just open the library here which ensures that.
         */
        __ciabBase = ciabBase = IExec->OpenLibrary("ciab.resource", 0);
        if (ciabBase == NULL)
        {
            BPTR StdErr = IDOS->ErrorOutput();
            if (StdErr == ZERO)
                StdErr = IDOS->Output();
            IDOS->FPrintf(StdErr, "ERROR: Failed to open '%s'.\n", "ciab.resource");
            abort();
        }
    }

    __Iciab = Iciab = (struct ciabIFace *)IExec->GetInterface((struct Library *)ciabBase, "main", 1, NULL);
    if (Iciab == NULL)
    {
        BPTR StdErr = IDOS->ErrorOutput();
        if (StdErr == ZERO)
            StdErr = IDOS->Output();
        IDOS->FPrintf(StdErr, "ERROR: Failed to get '%s' V%ld interface for '%s'.\n", "main", 1, "ciab.resource");
        abort();
    }
}
#ifdef __GNUC__
__attribute__((section(".ctors.zzzy"))) static void
(*ciab_main_constructor_ptr)(void) USED = _INIT_5_Iciab;
#endif

/****************************************************************************/

void _EXIT_5_Iciab(void)
{
    if (__Iciab)
    {
        IExec->DropInterface ((struct Interface *)__Iciab);
    }
    if (__ciabBase)
    {
        IExec->CloseLibrary(__ciabBase);
    }
}
#ifdef __GNUC__
__attribute__((section(".dtors.zzzy"))) static void
(*ciab_main_destructor_ptr)(void) USED = _EXIT_5_Iciab;
#endif

/****************************************************************************/

