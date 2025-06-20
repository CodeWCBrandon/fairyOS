#include "gdt.h"

//constructor
GlobalDescriptorTable::GlobalDescriptorTable(): 
nullSegmentSelector(0, 0, 0),
unusedSegmentSelector(0, 0, 0),
codeSegmentSelector(0, 64*1028*1028, 0x9A),
dataSegmentSelector(0, 64*1028*1028, 0x92)
{
    //address and size (limit) for the GDT (LGDT)
    uint32_t i[2]; 
    i[0] = (uint32_t)this; // address
    i[1] = sizeof(GlobalDescriptorTable) << 16; // size at the high byte

    asm volatile("lgdt (%0)" : : "p" (((uint8_t *) i) + 2)); // loading the GDT
}
