obj-m := lfs.o
KVERSION := $(shell uname -r)
KDIR := /lib/modules/$(KVERSION)/build

default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
