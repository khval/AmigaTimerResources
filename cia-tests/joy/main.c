
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define __USE_INLINE__

#include <proto/exec.h>
#include <proto/dos.h>

#ifdef CUSTOM
#undef CUSTOM
#endif

#define CUSTOM	0xDFF000

#define POTGOR 0x16

#define CIAA		0xBFE001
#define CIAB		0xBFD000

#define PRA 0

#define TALO	0x400
#define TAHI	0x500
#define TBLO	0x600
#define TBHI	0x700
#define TOLO	0x800
#define TOMID	0x900
#define TODHI	0xA00
#define ICR	0xD00
#define CRA	0xE00
#define CRB	0xF00

/*
void disa()
{
	char opcodeName[LEN_DISASSEMBLE_OPCODE_STRING],operands[LEN_DISASSEMBLE_OPERANDS_STRING];
	APTR ptr = getreg;

	struct DebugIFace *IDebug = (struct DebugIFace *) GetInterface( SysBase,"debug",1,TAG_END);

	if (IDebug)
	{
		do
		{
			ptr = DisassembleNative(ptr, opcodeName, operands);
			Printf("%08lx --- %s %s\n",ptr, opcodeName, operands);
		}
		while ( (ULONG) ptr < (ULONG) disa);

		DropInterface((struct Interface*) IDebug); IDebug = 0;
	}
	else
	{
		Printf("IDebug failed\n");
	}
}
*/

u_short getreg(u_short *a)
{
	u_short t;
	t = *a;

//	printf("GET: %08lx -- value: %d\n",a, t);
	return t;
}

void setreg(char v,u_short *a)
{
	*a =v;
}

#define get_reg(a,v) v = getreg( (u_short *) (a) )
#define set_reg(v,a) setreg( (char) v, (u_short *) (a) )

unsigned int bin (char *input)
{
	char *i;
	unsigned int v = 0;
	for (i=input;*i;i++) v = v<<1 | (*i - '0');
	return v;
}

void B_SET(int bit, char *addr);
bool B_TST(int nit, char *addr);

#define BSET(bit,addr) B_SET(bit, (char*) addr)
#define BTST(bit,addr) B_TST(bit, (char*) addr)

#define IS_ACTIVE_LOW( VAR, BIT ) (0 == ( VAR & (1 << BIT) ))

void test(int chip)
{
	ULONG D0;

	ULONG inv_POTGOR =
		1L<<14 |
		1L << 12 |
		1L <<10 |
		1L << 8 ;

// busy wait

	for(;;)
	{
		if(SetSignal(0L,SIGBREAKF_CTRL_C) & SIGBREAKF_CTRL_C)
		{
			Printf("CTRL-C pressed!\n");
			break;
    	        }

		get_reg(CUSTOM+POTGOR,D0);

		if (D0 ^ inv_POTGOR ) printf("CUSTOM+POTGOR; %08lx\n",D0);

		if ( IS_ACTIVE_LOW( D0,14) ) 	// pin 9
		{
			Printf("Port 2 button 2\n");
		}

		if ( IS_ACTIVE_LOW( D0,10) ) 	// pin 9
		{
			Printf("Port 1 Right mouse button\n");
		}

/*
		get_reg(CIAA | PRA,D0);

		if (D0) Printf("CIAA | PRA; %08llx\n",D0);

		if ( D0 &  (1 << 7) ) 	// pin 9
		{
			Printf("Port 2 button 1\n");
		}

		if ( D0 &  (1 << 6) ) 	// pin 9
		{
			Printf("Port 1 button 1\n");
		}
*/

		Delay(2);
	}
}

int main()
{	
	test(CIAA);
	return 0;
}

void B_SET(int bit, char *addr)
{
	unsigned int temp;
	get_reg(addr, temp);
	temp |= 1<<bit;
	set_reg(temp,addr);
}


bool B_TST(int bit, char *addr)
{
	char temp = 0x12;
	get_reg(addr, temp);
	return temp & (1<<bit) ? true : false;
}

