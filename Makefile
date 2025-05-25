GPPPARAMS = -m32
ASMPARAMS = --32
LDPARAMS = -melf_i386

objects = kernel.o loader.o

%.o : %.cpp
	g++ $(GPPPARAMS) -o $@ -c $<

%.o : %.s
	as $(ASMPARAMS) -o $@ $<

mykernel.bin: linker.ld $(objects)
	ld $(LDPARAMS) -T $< -o $@ $(objects)

install: mykernel.bin
	sudo cp $< /boot/mykernel.bin