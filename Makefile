SYSROOT = /home/andrew/dev/dragonboard/sysroot

SHELL = /bin/bash
CXX = $(SYSROOT)/../gcc-linaro-7.3.1-2018.05-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu-g++
AR = $(SYSROOT)/../gcc-linaro-7.3.1-2018.05-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu-ar
CXXFLAGS = -std=c++17 -Wall -g
INC = -I.
LIBS = -pthread -L$(SYSROOT)/usr/lib/aarch64-linux-gnu/ -l:libsoc.so.2
TARGET = libsoc-cpp
SOURCES = $(wildcard src/*.cpp)
OBJS = $(SOURCES:.cpp=.o)
INSTALL_DIR = /usr/lib

all: $(TARGET).so $(TARGET).a

static: $(TARGET).a
shared: $(TARGET).so

$(TARGET).so: $(SOURCES)
	$(CXX) $(CXXFLAGS) -fPIC -shared $(INC) --sysroot=$(SYSROOT) $^ -o $@ $(LIBS)

$(TARGET).a: $(OBJS)
	$(AR) rvs $@ $(OBJS)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INC) --sysroot=$(SYSROOT) $(LIBS)

install:
	cp $(TARGET).so $(INSTALL_DIR)
	cp $(TARGET).a $(INSTALL_DIR)

uninstall:
	rm $(INSTALL_DIR)/$(TARGET).so $(INSTALL_DIR)/$(TARGET).a

clean:
	rm $(TARGET).so $(TARGET).a src/*.o
	
cleanobjects:
	rm src/*.o