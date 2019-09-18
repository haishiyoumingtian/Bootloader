#include "sys.h"

//…Ë÷√’ª∂•µÿ÷∑
//addr:’ª∂•µÿ÷∑
__asm void MSR_MSP(u32 addr) 
{
    MSR MSP, r0 			//set Main Stack value
    BX r14
}
