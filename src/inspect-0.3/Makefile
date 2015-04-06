

all:  scheduler  


scheduler:
	make -C ./src
	mv ./src/inspect .

distclean:
	make -C ./src clean
	rm -f target 
	rm -f inspect

clean:
	make -C ./src/  clean
	rm -f target
	rm -f inspect



