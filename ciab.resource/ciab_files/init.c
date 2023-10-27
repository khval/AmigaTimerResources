/* :ts=4
 *  $VER: init.c $Revision$ (21-Sep-2023)
 *
 *  This file is part of ciab.
 *
 *  Copyright (c) 2023 Hyperion Entertainment CVBA.
 *  All Rights Reserved.
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

/* Version Tag */
#include "ciab.resource_rev.h"
STATIC CONST UBYTE USED verstag[] = VERSTAG;

#include "emu_cia.h"

/* Uncomment this line (and see below) if your library has a 68k jump table */
extern APTR VecTable68K[]; 

struct DebugIFace *IDebug = NULL;

struct Interrupt *cia_bitlist[4];

struct chip *local_chip = NULL;

struct ExecIFace *IExec = NULL;

struct _library
{
    struct Library libNode;
    BPTR segList;
    /* If you need more data fields, add them here */
};

struct __attribute__((__packed_)) __JMP__
{
	short ins;
	short addr[2];
};

void set_jmp( struct __JMP__ *jmp, ULONG dest_addr )
{
	jmp -> ins = 0x4EF9;
	jmp -> addr[0] = (dest_addr >> 16) & 0xFFFF;
	jmp -> addr[1] = (dest_addr) & 0xFFFF;
}


#define res_func_count 20

STATIC struct __attribute__((__packed_)) _res_
{
	struct __JMP__ tab[res_func_count];
	struct Node res;
} Resource;


/*
 * The system (and compiler) rely on a symbol named _start which marks
 * the beginning of execution of an ELF file. To prevent others from 
 * executing this library, and to keep the compiler/linker happy, we
 * define an empty _start symbol here.
 *
 * On the classic system (pre-AmigaOS 4.x) this was usually done by
 * moveq #0,d0
 * rts
 *
 */
int32 _start(void);

int32 _start(void)
{
    /* If you feel like it, open DOS and print something to the user */
    return RETURN_FAIL;
}


/* Open the library */
STATIC struct Library *libOpen(struct LibraryManagerInterface *Self, ULONG version)
{
    struct _library *libBase = (struct _library *)Self->Data.LibBase; 

    if (version > VERSION)
    {
        return NULL;
    }

    /* Add any specific open code here 
       Return 0 before incrementing OpenCnt to fail opening */


    /* Add up the open count */
    libBase->libNode.lib_OpenCnt++;
    return (struct Library *)libBase;

}


/* Close the library */
STATIC APTR libClose(struct LibraryManagerInterface *Self)
{
    struct _library *libBase = (struct _library *)Self->Data.LibBase;
    /* Make sure to undo what open did */


    /* Make the close count */
    ((struct Library *)libBase)->lib_OpenCnt--;

    return 0;
}


/* Expunge the library */
STATIC APTR libExpunge(struct LibraryManagerInterface *Self)
{
    /* If your library cannot be expunged, return 0 */
    struct ExecIFace *IExec
        = (struct ExecIFace *)(*(struct ExecBase **)4)->MainInterface;
    APTR result = (APTR)0;
    struct _library *libBase = (struct _library *)Self->Data.LibBase;
    if (libBase->libNode.lib_OpenCnt == 0)
    {
       result = (APTR)libBase->segList;
        /* Undo what the init code did */

	if (IDebug)
	{
		IExec -> DropInterface( (struct Interface *) IDebug );
		IDebug = NULL;
	}

        IExec->Remove((struct Node *)libBase);
        IExec->DeleteLibrary((struct Library *)libBase);
        IExec->RemResource( &Resource.res );
    }
    else
    {
        result = (APTR)0;
        libBase->libNode.lib_Flags |= LIBF_DELEXP;
    }
    return result;
}

/* The ROMTAG Init Function */
STATIC struct Library *libInit(struct Library *LibraryBase, APTR seglist, struct Interface *exec)
{
    struct _library *libBase = (struct _library *)LibraryBase;

    IExec = (struct ExecIFace *)exec;

    libBase->libNode.lib_Node.ln_Type = NT_LIBRARY;
    libBase->libNode.lib_Node.ln_Pri  = 0;
    libBase->libNode.lib_Node.ln_Name = "ciab.resource";
    libBase->libNode.lib_Flags        = LIBF_SUMUSED|LIBF_CHANGED;
    libBase->libNode.lib_Version      = VERSION;
    libBase->libNode.lib_Revision     = REVISION;
    libBase->libNode.lib_IdString     = VSTRING;

    libBase->segList = (BPTR)seglist;

	IDebug = (struct DebugIFace *) IExec -> GetInterface( exec -> Data.LibBase ,  "debug", 1, TAG_END );

	// clear cia bitlist
	{
		static char *ptr;
		for (ptr = (char *) cia_bitlist;  ptr < (char *) cia_bitlist + sizeof(cia_bitlist); ptr++) *ptr = 0;
	}

	// set up resource
	{
		char *jmp_addr;
		int i;
		Resource.res.ln_Pri  = 0;
		Resource.res.ln_Type = NT_RESOURCE;
		Resource.res.ln_Name = "ciab.resource";

		for (i=0;i<res_func_count;i++)
		{
			jmp_addr = ((char *) &Resource.res) - ((i+1) * 6);
			set_jmp( (struct __JMP__ *) jmp_addr, (ULONG) VecTable68K[i+4] );
		}
	}

	IExec->AddResource( &Resource.res );

       return (struct Library *)libBase;
}

/* ------------------- Manager Interface ------------------------ */
/* These are generic. Replace if you need more fancy stuff */
STATIC uint32 _manager_Obtain(struct LibraryManagerInterface *Self)
{
	uint32 res;
	__asm__ __volatile__(
	"1:  lwarx  %0,0,%1\n"
	"addic  %0,%0,1\n"
	"stwcx.  %0,0,%1\n"
	"bne-  1b"
	: "=&r" (res)
	: "r" (&Self->Data.RefCount)
	: "cc", "memory");

	return res;
}

STATIC uint32 _manager_Release(struct LibraryManagerInterface *Self)
{
	uint32 res;
	__asm__ __volatile__(
	"1:  lwarx  %0,0,%1\n"
	"addic  %0,%0,-1\n"
	"stwcx.  %0,0,%1\n"
	"bne-  1b"
	: "=&r" (res)
	: "r" (&Self->Data.RefCount)
	: "cc", "memory");

	return res;
}

/* Manager interface vectors */
STATIC CONST APTR lib_manager_vectors[] =
{
	_manager_Obtain,
	_manager_Release,
	NULL,
	NULL,
	libOpen,
	libClose,
	libExpunge,
	NULL,
	(APTR)-1
};

/* "__library" interface tag list */
STATIC CONST struct TagItem lib_managerTags[] =
{
	{ MIT_Name,			(Tag)"__library"		},
	{ MIT_VectorTable,	(Tag)lib_manager_vectors},
	{ MIT_Version,		1						},
	{ TAG_DONE,			0						}
};

/* ------------------- Library Interface(s) ------------------------ */

#include "ciab_vectors.c"

/* Uncomment this line (and see below) if your library has a 68k jump table */
/* extern APTR VecTable68K[]; */

STATIC CONST struct TagItem main_v1_Tags[] =
{
	{ MIT_Name,			(Tag)"main"			},
	{ MIT_VectorTable,	(Tag)main_v1_vectors	},
	{ MIT_Version,		1					},
	{ TAG_DONE,			0					}
};

STATIC CONST CONST_APTR libInterfaces[] =
{
	lib_managerTags,
	main_v1_Tags,
	NULL
};

STATIC CONST struct TagItem libCreateTags[] =
{
	{ CLT_DataSize,		sizeof(struct _library)	},
	{ CLT_InitFunc,		(Tag)libInit			},
	{ CLT_Interfaces,	(Tag)libInterfaces		},
	/* Uncomment the following line if you have a 68k jump table */
	/* { CLT_Vector68K, (Tag)VecTable68K }, */
	{TAG_DONE,		 0 }
};


/* ------------------- ROM Tag ------------------------ */
STATIC CONST struct Resident lib_res USED =
{
	RTC_MATCHWORD,
	(struct Resident *)&lib_res,
	(APTR)(&lib_res + 1),
	RTF_NATIVE|RTF_AUTOINIT, /* Add RTF_COLDSTART if you want to be resident */
	VERSION,
	NT_LIBRARY, /* Make this NT_DEVICE if needed */
	0, /* PRI, usually not needed unless you're resident */
	"ciab.resource",
	VSTRING,
	(APTR)libCreateTags
};

