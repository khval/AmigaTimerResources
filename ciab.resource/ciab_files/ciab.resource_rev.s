VERSION = 53
REVISION = 1

.macro DATE
.ascii "21.9.2023"
.endm

.macro VERS
.ascii "ciab.resource 53.1"
.endm

.macro VSTRING
.ascii "ciab.resource 53.1 (21.9.2023)"
.byte 13,10,0
.endm

.macro VERSTAG
.byte 0
.ascii "$VER: ciab.resource 53.1 (21.9.2023)"
.byte 0
.endm
