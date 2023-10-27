
# supported CPU

cpu=68020

all: left_mouse_button.o
		vlink -bamigahunk -o left_mouse_button.hunk -s left_mouse_button.o

left_mouse_button.o: left_mouse_button.s
		vasmm68k_mot  -m${cpu} -Iinclude -Fvobj -o left_mouse_button.o left_mouse_button.s $(module_options)

clean:
	delete #?.o