obj-m = int.o

KDIR = /usr/src/tegra
PWD = $(shell pwd)

default:
	make -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	make -C $(KDIR) SUBDIRS=$(PWD) clean
