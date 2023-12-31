#ifndef CIAA_INTERFACE_DEF_H
#define CIAA_INTERFACE_DEF_H

/*
** This file was machine generated by idltool 53.35.
** Do not edit
*/ 

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef EXEC_EXEC_H
#include <exec/exec.h>
#endif
#ifndef EXEC_INTERFACES_H
#include <exec/interfaces.h>
#endif

#ifndef EXEC_INTERRUPTS_H
#include <exec/interrupts.h>
#endif
#ifndef EXEC_LIBRARIES_H
#include <exec/libraries.h>
#endif

#ifdef __cplusplus
#ifdef __USE_AMIGAOS_NAMESPACE__
namespace AmigaOS {
#endif
extern "C" {
#endif

struct ciaaIFace
{
	struct InterfaceData Data;

	APICALL ULONG (*Obtain)(struct ciaaIFace *Self);
	APICALL ULONG (*Release)(struct ciaaIFace *Self);
	APTR Expunge_UNIMPLEMENTED;
	APTR Clone_UNIMPLEMENTED;
	APICALL struct Interrupt * (*AddICRVector)(struct ciaaIFace *Self, struct Library * resource, WORD iCRBit, struct Interrupt * interrupt);
	APICALL VOID (*RemICRVector)(struct ciaaIFace *Self, struct Library * resource, WORD iCRBit, struct Interrupt * interrupt);
	APICALL WORD (*AbleICR)(struct ciaaIFace *Self, struct Library * resource, WORD mask);
	APICALL WORD (*SetICR)(struct ciaaIFace *Self, struct Library * resource, WORD mask);
	APICALL struct Interupt ** (*NallePuh)(struct ciaaIFace *Self, ULONG state, APTR chip);
};

#ifdef __cplusplus
}
#ifdef __USE_AMIGAOS_NAMESPACE__
}
#endif
#endif

#endif /* CIAA_INTERFACE_DEF_H */
