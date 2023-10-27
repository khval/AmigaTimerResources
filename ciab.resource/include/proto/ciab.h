#ifndef PROTO_CIAB_H
#define PROTO_CIAB_H

/*
**	$Id$
**
**	Prototype/inline/pragma header file combo
**
**	Copyright (c) 2010 Hyperion Entertainment CVBA.
**	All Rights Reserved.
*/

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef EXEC_INTERRUPTS_H
#include <exec/interrupts.h>
#endif
#ifndef EXEC_LIBRARIES_H
#include <exec/libraries.h>
#endif

/****************************************************************************/

#ifndef __NOLIBBASE__
 #if defined(__cplusplus) && defined(__USE_AMIGAOS_NAMESPACE__)
  extern struct AmigaOS::Library * ciabBase;
 #else
  extern struct Library * ciabBase;
 #endif
#endif /* __NOLIBBASE__ */

/****************************************************************************/

#ifdef __amigaos4__
 #include <interfaces/ciab.h>
 #ifdef __USE_INLINE__
  #include <inline4/ciab.h>
 #endif /* __USE_INLINE__ */
 #ifndef CLIB_CIAB_PROTOS_H
  #define CLIB_CIAB_PROTOS_H 1
 #endif /* CLIB_CIAB_PROTOS_H */
 #ifndef __NOGLOBALIFACE__
  #if defined(__cplusplus) && defined(__USE_AMIGAOS_NAMESPACE__)
   extern struct AmigaOS::ciabIFace * Iciab;
  #else
   extern struct ciabIFace * Iciab;
  #endif
 #endif /* __NOGLOBALIFACE__ */
#else /* __amigaos4__ */
 #ifndef CLIB_CIAB_PROTOS_H
  #include <clib/ciab_protos.h>
 #endif /* CLIB_CIAB_PROTOS_H */
 #if defined(__GNUC__)
  #ifndef __PPC__
   #include <inline/ciab.h>
  #else /* __PPC__ */
   #include <ppcinline/ciab.h>
  #endif /* __PPC__ */
 #elif defined(__VBCC__)
  #ifndef __PPC__
   #include <inline/ciab_protos.h>
  #endif /* __PPC__ */
 #else /* __GNUC__ */
  #include <pragmas/ciab_pragmas.h>
 #endif /* __GNUC__ */
#endif /* __amigaos4__ */

/****************************************************************************/

#endif /* PROTO_CIAB_H */
