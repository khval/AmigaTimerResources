
#define __USE_INLINE__

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include <proto/exec.h>
#include <exec/emulation.h>

#include <string.h>

bool is_branch(char *opcodeName)
{
	if (strncasecmp(opcodeName,"BEQ",3)==0) return true;
	if (strncasecmp(opcodeName,"BNE",3)==0) return true;
	if (strncasecmp(opcodeName,"BLE",3)==0) return true;
	if (strncasecmp(opcodeName,"BGT",3)==0) return true;
	return false;
}

void disasm(APTR nextaddress)
{
	char opcodeName[LEN_DISASSEMBLE_OPCODE_STRING];
	char operands[LEN_DISASSEMBLE_OPERANDS_STRING];
	APTR targetAddress;

	DebugPrintF("----- DISASM -----\n");

	if (nextaddress == 0)
	{
		DebugPrintF("NO ADDRESS\n");
	}
	else
	{
		if (IsNative(nextaddress))
		{
			DebugPrintF("Code is native, not emulated\n");
		}
		else
		{
			APTR minaddress = 0;

			DebugPrintF("Code is emulated\n");

			int n = 0;
			do
			{
				targetAddress = nextaddress;
				nextaddress = Disassemble68k(targetAddress, opcodeName, operands);

				if (nextaddress == NULL)
				{
					DebugPrintF("--- NEXT ADDRESS IS NULL --- \n");
					return;
				}

				DebugPrintF("%08lx: %s %s\n",targetAddress, opcodeName,operands);

				if (is_branch(opcodeName))
				{

					unsigned int num = 0;;
					if (strncasecmp(operands,"0x",2) == 0)
					{
						char *ptr = (char *) operands + 2;
					
						for (;*ptr;ptr++)
						{
							num <<= 4;
							if ((*ptr>='0')&&(*ptr<='9')) num |= (*ptr-'0');
							if ((*ptr>='a')&&(*ptr<='f')) num |= (*ptr-'a'+10);
						}
						if ( (APTR) num>minaddress) minaddress =  (APTR) num;
					}
				}

			}
			while ( (nextaddress <= minaddress)  || ( (strcasecmp(opcodeName,"RTS")!=0) && (n++<100)))  ;
		}
	}

	DebugPrintF("----- EXIT DISASM -----\n");
}

