SRC		= $(PWD)
BD		= $(PWD)
CXX		= g++

FILES	= ysa.cpp dugum.cpp katman.cpp 
LINKS	= -fPIC
OUTPUT	= libysa.so

all:   
	rm -rf	$(BD)/include
	mkdir	$(BD)/include
	cp 	*.hpp	$(BD)/include/
	$(CXX) -c --debug  -Wall -fPIC $(FILES) 
	$(CXX) -shared *.o -o $(BD)/$(OUTPUT)

clean:	
	rm $(MAIN_OUTPUT) 

install:
