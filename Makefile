GPPPARAMS = -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore
ASMPARAMS = --32
LDPARAMS = -melf_i386

objects = loader.o kernel.o

%.o : %.cpp
	g++ $(GPPPARAMS) -o $@ -c $<

%.o : %.s
	as $(ASMPARAMS) -o $@ $<

sentinelOS.bin: linker.ld $(objects)
	ld $(LDPARAMS) -T $< -o $@ $(objects)

install: sentinelOS.bin
	sudo cp $< /boot/sentinelOS.bin

sentinelOS.iso : sentinelOS.bin
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp $< iso/boot
	echo 'set timeout=0' >> iso/boot/grub/grub.cfg
	echo 'set default=0' >> iso/boot/grub/grub.cfg
	echo '' >> iso/boot/grub/grub.cfg
	echo 'menuentry "sentinel OS" {' >> iso/boot/grub/grub.cfg
	echo '	multiboot /boot/sentinelOS.bin' >> iso/boot/grub/grub.cfg
	echo '	boot' >> iso/boot/grub/grub.cfg
	echo '}' >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=$@ iso
	rm -rf iso

run: sentinelOS.iso
	(killall VirtualBoxVM && sleep 1) || true
	VirtualBoxVM --startvm "SentinelOS" & 

.PHONY: clear
clear:
	rm -rf $(objects) sentinelOS.bin sentinelOS.iso