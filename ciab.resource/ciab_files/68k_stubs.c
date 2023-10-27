
#include <exec/libraries.h>
#include <exec/emulation.h>

#define __USE_INLINE__

#include <stdio.h>
#include <proto/exec.h>

#include <exec/types.h>
#include <exec/exec.h>
#include <exec/interrupts.h>

#include <resources/cia.h>

extern struct Interrupt * _ciab_AddICRVector(struct ciabIFace *Self, struct Library * resource, WORD iCRBit, struct Interrupt * interrupt);
extern VOID _ciab_RemICRVector(struct ciabIFace *Self, struct Library * resource, WORD iCRBit,  struct Interrupt * interrupt);
extern WORD _ciab_AbleICR(struct ciabIFace *Self, struct Library * resource,  WORD mask);
extern WORD _ciab_SetICR(struct ciabIFace *Self, struct Library * resource, WORD mask);

STATIC APTR stub_Open_ppc(ULONG *regarray);
STATIC APTR stub_Close_ppc(ULONG *regarray);
STATIC APTR stub_Expunge_ppc(ULONG *regarray);
STATIC ULONG stub_Reserved_ppc(ULONG *regarray);

STATIC void stub_AddICRVector_ppc(ULONG *regarray);
STATIC void stub_RemICRVector_ppc(ULONG *regarray);
STATIC void stub_AbleICR_ppc(ULONG *regarray);
STATIC void stub_SetICR_ppc(ULONG *regarray);

const struct EmuTrap stub_Open = { TRAPINST, TRAPTYPE, (void *) stub_Open_ppc };
const struct EmuTrap stub_Close = { TRAPINST, TRAPTYPE, (void *) stub_Close_ppc };
const struct EmuTrap stub_Expunge = { TRAPINST, TRAPTYPE, (void *) stub_Expunge_ppc };
const struct EmuTrap stub_Reserved = { TRAPINST, TRAPTYPE, (void *) stub_Reserved_ppc };

const struct EmuTrap stub_AddICRVector = { TRAPINST, TRAPTYPE, (void *) stub_AddICRVector_ppc };
const struct EmuTrap stub_RemICRVector = { TRAPINST, TRAPTYPE, (void *) stub_RemICRVector_ppc };
const struct EmuTrap stub_AbleICR = { TRAPINST, TRAPTYPE, (void *) stub_AbleICR_ppc };
const struct EmuTrap stub_SetICR = { TRAPINST, TRAPTYPE, (void *) stub_SetICR_ppc };

const ULONG VecTable68K[] = {
	(ULONG) &stub_Open,
	(ULONG) &stub_Close,
	(ULONG) &stub_Expunge,
	(ULONG) &stub_Reserved,

	(ULONG) &stub_AddICRVector,
	(ULONG) &stub_RemICRVector,
	(ULONG) &stub_AbleICR,
	(ULONG) &stub_SetICR,
	(ULONG) ~0
};

STATIC APTR stub_Open_ppc(ULONG *regarray)
{
	struct Library *Base = (struct Library *) regarray[REG68K_A6/4];
	struct ExtendedLibrary *ExtLib = (struct ExtendedLibrary *) ((ULONG)Base + Base->lib_PosSize);
	struct LibraryManagerInterface *Self = (struct LibraryManagerInterface *) ExtLib->ILibrary;

	regarray[REG68K_D0/4] = (ULONG) Self -> Open( 0);

	return (APTR) regarray[REG68K_D0/4];
}

STATIC APTR stub_Close_ppc(ULONG *regarray)
{
	struct Library *Base = (struct Library *) regarray[REG68K_A6/4];
	struct ExtendedLibrary *ExtLib = (struct ExtendedLibrary *) ((ULONG)Base + Base->lib_PosSize);
	struct LibraryManagerInterface *Self = (struct LibraryManagerInterface *) ExtLib->ILibrary;

	regarray[REG68K_D0/4] = (ULONG) Self -> Close();

	return (APTR) regarray[REG68K_D0/4];
}

STATIC APTR stub_Expunge_ppc(ULONG *regarray)
{
	return NULL;
}

STATIC ULONG stub_Reserved_ppc(ULONG *regarray)
{
	return 0UL;
}

STATIC void stub_AddICRVector_ppc(ULONG *regarray)
{
	 regarray[REG68K_D0/4] = (ULONG) _ciab_AddICRVector(NULL,
		(struct Library *) regarray[REG68K_A6/4],
		(ULONG) regarray[REG68K_D0/4],
		(struct Interrupt *) regarray[REG68K_A1/4]);
}

STATIC void stub_RemICRVector_ppc(ULONG *regarray)
{
	 _ciab_RemICRVector(NULL,
		(struct Library *) regarray[REG68K_A6/4],
		(WORD) regarray[REG68K_D0/4],
		(struct Interrupt *) regarray[REG68K_A1/4]);
}

STATIC void stub_AbleICR_ppc(ULONG *regarray)
{
	 regarray[REG68K_D0/4] = _ciab_AbleICR(NULL,
		(struct Library *) regarray[REG68K_A6/4],
		(WORD) regarray[REG68K_D0/4]);
}

STATIC void stub_SetICR_ppc(ULONG *regarray)
{
	 regarray[REG68K_D0/4] = _ciab_SetICR(NULL,
		(struct Library *) regarray[REG68K_A6/4],
		(WORD) regarray[REG68K_D0/4]);;
}

