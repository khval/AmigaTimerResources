
; Emulated by AmigaOS4.1

wait:
	btst	#6,$bfe001
	bne	wait
	rts

