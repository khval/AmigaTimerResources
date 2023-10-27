
#include <stdlib.h>
#include <stdio.h>
#include <proto/dos.h>
#include <proto/exec.h>


int main()
{
	int irq;
	struct ExecBase *SysBase = *( (struct ExecBase**)  0x4);

	printf("HW IRQ IPL0,IPL1,IPL2\n");

	for (irq=0;irq<7;irq++)
	{
		ULONG **code = (void **) 0x64;

		printf("AT %08x IRQ: %02d -- code: %08x\n",code+irq,irq+1, code[irq]);

	}

	printf("SysBase->IntVects is at 0x%08x\n", &SysBase->IntVects);

	for (irq=0;irq<16;irq++)
	{
		struct IntVector	*iv = &SysBase->IntVects[irq];
		struct Interrupt	*is = (struct Interrupt *) iv->iv_Node;

		if (is)
		{
			printf("IRQ: %02d -- name: %s\n",irq+1, is -> is_Node.ln_Name);
		}
		else
		{
			printf("IRQ: %02d -- NONE\n",irq+1);
		}
	}
}