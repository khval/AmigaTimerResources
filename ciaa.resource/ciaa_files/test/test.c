
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define __USE_INLINE__

#include <proto/exec.h>
#include <exec/emulation.h>

struct Library *base;
struct Resource *ciaaResource;

struct Interrupt *newint = NULL;
struct Interrupt *oldint = NULL;

struct Interrupt *AddICRVector( struct Resource *ciaaResource, ULONG iCRBit, struct Interrupt * newint )
{
	struct Interrupt *result = (struct Interrupt *) EmulateTags( ((char *) ciaaResource -6) ,
				ET_SaveParamRegs, TRUE,
				ET_SuperState, TRUE,
				ET_RegisterA0, ciaaResource,
				ET_RegisterD0, iCRBit,
				ET_RegisterA1, newint,
				TAG_DONE );

	return result;
}

void RemICRVector( struct Resource *ciaaResource, ULONG iCRBit, struct Interrupt * newint )
{
	EmulateTags( ((char *) ciaaResource -6) ,		// LVO -6
				ET_SaveParamRegs, TRUE,
				ET_SuperState, TRUE,
				ET_RegisterA0, ciaaResource,
				ET_RegisterD0, iCRBit,
				ET_RegisterA1, newint,
				TAG_DONE );
}

void test_api()
{
	int iCRBit = 0;

	oldint = AddICRVector( ciaaResource, iCRBit, newint );

	if (oldint == NULL)
	{
		printf("we are the new owners :-)\n");

		RemICRVector( ciaaResource, iCRBit, newint );
	}
	else
	{
		printf("we are not the owner\n");
	}

}

int main()
{
	base = OpenLibrary("ciaa.resource",0L);

	if (base)
	{
		printf("ciaa is loaded ;-)\n");

		ciaaResource = OpenResource("ciaa.resource");

		if (ciaaResource)
		{
			printf("ciaaResource found :-)\n");

			test_api();
		}

		CloseLibrary( base );
	}

	return 0;
}