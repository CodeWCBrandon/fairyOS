#include "types.h"

void clear()
{
    uint16_t* videoMemory = (uint16_t*) 0xb8000;
    for(int32_t i = 0; i < 80 * 25; ++i)
    {
        videoMemory[i] = (0x0F << 8) | ' ';
    }
}

void printf(char* str)
{
    clear();
    uint16_t* videoMemory = (uint16_t*) 0xb8000;
    for(int32_t i = 0; str[i] != '\0'; ++i)
    {
        videoMemory[i] = (videoMemory[i] & 0xFF00) | str[i];
    }
}

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors()
{
    for(constructor* i = &start_ctors; i != &end_ctors; ++i)
    {
        (*i)();
    }
}

extern "C" void kernelMain(void* multiboot_structure, uint32_t magicNumber)
{
    printf("Hello world");

    while(true);
}