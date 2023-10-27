VERSION		EQU	53
REVISION	EQU	1

DATE	MACRO
		dc.b '21.9.2023'
		ENDM

VERS	MACRO
		dc.b 'ciab.resource 53.1'
		ENDM

VSTRING	MACRO
		dc.b 'ciab.resource 53.1 (21.9.2023)',13,10,0
		ENDM

VERSTAG	MACRO
		dc.b 0,'$VER: ciab.resource 53.1 (21.9.2023)',0
		ENDM
