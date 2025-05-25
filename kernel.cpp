
void printf(char* str)
{
    unsigned short* videoMemory = (unsigned short*) 0xb8000;
    for(int i = 0; str[i] != '\0'; ++i)
    {
        videoMemory[i] = (videoMemory[i] & 0xFF00) | str[i];
    }
}

static void kernelMain(void* multiboot_structure, unsigned int magicNumber)
{
    printf("Hello world");

    while(true);
}