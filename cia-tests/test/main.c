
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define __USE_INLINE__

#include <proto/exec.h>
#include <proto/dos.h>

#define CIAA 0xBFE001
#define CIAB 0xBFD000

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

u_char getreg(u_char *a)
{
	u_char t;
	t = *a;
	return t;
}

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

void setreg(char v,char *a)
{
	*a =v;
}

#define get_reg(a,v) v = getreg( (char *) a )
#define set_reg(v,a) setreg( (char) v, (char *) a )

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


void test(int chip)
{
	int led = 0;
	int TIME;
	unsigned int D0,D1,D2,D3,D4,D6;
	unsigned int A0,A1,A2,A3,A4,A5;

	get_reg(chip+CRA, D0);
	D0 &=	bin("11000000");
	D0 |=	bin("00001000");
	set_reg(D0,chip+CRA);

	TIME = 20<<8;

	printf("set CIA+TALO: %d\n", TIME & 0xFF);

	set_reg(TIME & 0xFF,chip+TALO);

	printf("set CIA+TAHI: %d\n", TIME >>8);

	set_reg( (TIME>>8), chip+TAHI);

// busy wait

	for(;;)
	{
		if(SetSignal(0L,SIGBREAKF_CTRL_C) & SIGBREAKF_CTRL_C)
		{
			Printf("CTRL-C pressed!\n");
			break;
    	        }

		if (!BTST(0,chip+ICR)) 
		{
			Delay(1);
			continue;
		}

		led = ~led;
		Printf("Led %s\n", led ? "on" : "off"  );

		BSET(0,chip+CRA);

		Delay(1);
	}

	TIME = 0;

	D0 = bin("00000000");
	set_reg(D0,chip+CRA);

	set_reg(TIME & 0xFF,chip+TALO);
	set_reg( (TIME>>8), chip+TAHI);

}

int main()
{	


	test(CIAB);


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

//	printf("%08x\n",temp );

	return temp & (1<<bit) ? true : false;
}

