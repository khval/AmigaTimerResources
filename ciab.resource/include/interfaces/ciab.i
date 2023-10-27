#ifndef CIAB_INTERFACE_DEF_H
#define CIAB_INTERFACE_DEF_H
/*
** This file is machine generated from idltool
** Do not edit
*/ 

#include <exec/types.i>
#include <exec/exec.i>
#include <exec/interfaces.i>

STRUCTURE ciabIFace, InterfaceData_SIZE
	    FPTR Iciab_Obtain
	    FPTR Iciab_Release
	    FPTR ciabIFace_Expunge_UNIMPLEMENTED
	    FPTR ciabIFace_Clone_UNIMPLEMENTED
	    FPTR Iciab_AddICRVector
	    FPTR Iciab_RemICRVector
	    FPTR Iciab_AbleICR
	    FPTR Iciab_SetICR
	    FPTR Iciab_NallePuh
	LABEL ciabIFace_SIZE

#endif
