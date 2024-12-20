ifneq ($(KERNELRELEASE),)
# kbuild part of makefile
obj-m := hello6.o
ccflags-y += -g
else
# normal makefile
KDIR ?= $$HOME/repos/linux-stable

default:
	$(MAKE) -C $(KDIR) M=$$PWD
	cp hello6.ko hello.ko.unstripped
	$(CROSS_COMPILE)strip -g hello6.ko # strip only debugging info

clean:
	$(MAKE) -C $(KDIR) M=$$PWD clean
	%.s %.i: %.c # just use make hello.s instead of objdump
	$(MAKE) -C $(KDIR) M=$$PWD $@
endif
