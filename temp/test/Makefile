SRC		= $(PWD)
BD		= $(PWD)
CXX		= g++

MAIN_FILES	= training.cpp ysa.cpp image.cpp json11.cpp
RUN_FILES	= run.cpp ysa.cpp image.cpp	json11.cpp
DETECT_FILES	= detect.cpp

LINKS_CV	= -lopencv_imgproc -lopencv_highgui -lopencv_objdetect -lopencv_core -lopencv_videoio
LINKS		= -lm 

MAIN_OUTPUT	= training
RUN_OUTPUT	= run
DETECT_OUTPUT	= detect

all:    
	$(CXX)  --debug -Wall $(MAIN_FILES) -o $(BD)/$(MAIN_OUTPUT) $(LINKS) 
	$(CXX)  --debug -Wall  $(RUN_FILES) -o $(BD)/$(RUN_OUTPUT)  $(LINKS)
	#$(CXX)	--debug -Wall $(DETECT_FILES) -o $(BD)/$(DETECT_OUTPUT)  $(LINKS)

clean:	
	rm $(MAIN_OUTPUT) 
	rm $(RUN_OUTPUT) 
install:
