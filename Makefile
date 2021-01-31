
BD 	= $(PWD)/build
LIB	= ./ysa
APP = ./test

install:
	make -C  $(LIB) BD=$(BD)
	make -C  $(APP)	BD=$(BD)

clean: