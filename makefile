INSTALLPATH = /SDK/local/newlib
INCLUDEINSTALLPATH= /SDK/local/common
CC 			= ppc-amigaos-gcc
CXX			= ppc-amigaos-g++
AR 			= ppc-amigaos-ar
RANLIB 		= ppc-amigaos-ranlib
COPY		= cp -v
MAKEDIR		= mkdir
STRIP 		= ppc-amigaos-strip
PROTECT		= true
DELETE		= rm

SRCS = Source/mglDebugger.cpp Source/MiniGLIFacePatcher.cpp Source/GLContextIFacePatcher.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = mglDebugger.exe

.PHONY: clean

$(TARGET): $(OBJS)
	@echo Linking $<
	@$(CC) -o $@ $(OBJS) -Wall -Werror

%.o : %.cpp
	@echo Compiling $<
	@$(CXX) -Wall -Werror -c $< -o $*.o

clean:
	@echo Cleaning project
	@$(DELETE) mglDebugger.exe
	@$(DELETE) Source/*.o

