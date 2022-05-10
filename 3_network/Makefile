obj-m += network.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) modules
	make main

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) clean
	rm -f main
