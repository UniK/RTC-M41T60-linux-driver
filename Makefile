ifneq ($(KERNELVERSION),)
obj-m	:= rtc.o


else
KDIR	:= /lib/modules/$(shell uname -r)/build
PWD	:= $(shell pwd)

default: rtc

rtc:
	@echo "Building module ..."
	@(cd $(KDIR) && make -C $(KDIR) SUBDIRS=$(PWD) modules)

clean:
	-rm -f *.o *.ko .*.cmd .*.flags *.mod.c Modules.symvers
	-rm -rf .tmp_versions
	-rm -rf *~

endif
