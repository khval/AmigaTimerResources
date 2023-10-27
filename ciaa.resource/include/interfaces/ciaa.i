#ifndef CIAA_INTERFACE_DEF_H
#define CIAA_INTERFACE_DEF_H
/*
** This file is machine generated from idltool
** Do not edit
*/ 

#include <exec/types.i>
#include <exec/exec.i>
#include <exec/interfaces.i>

STRUCTURE ciaaIFace, InterfaceData_SIZE
	    FPTR Iciaa_Obtain
	    FPTR Iciaa_Release
	    FPTR ciaaIFace_Expunge_UNIMPLEMENTED
	    FPTR ciaaIFace_Clone_UNIMPLEMENTED
	    FPTR Iciaa_AddICRVector
	    FPTR Iciaa_RemICRVector
	    FPTR Iciaa_AbleICR
	    FPTR Iciaa_SetICR
	    FPTR Iciaa_NallePuh
	LABEL ciaaIFace_SIZE

#endif
