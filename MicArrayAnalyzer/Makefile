AUDACITY_DIR = /home/luca/audacity-src-1.3.12-beta
OBJS = MicArrayAnalyzer.o
OBJS_DEBUG = MicArrayAnalyzerd.o
MOD = MicArrayAnalyzer.so
MOD_DEBUG = MicArrayAnalyzerd.so
BIN_DIR = output
SRC_DIR = src
OBJ_DIR = $(BIN_DIR)
INC_DIR = $(SRC_DIR)

PREFIX=/usr/local/share/audacity
INST_DIR=/usr/local/share/audacity/modules

WX = wx-config --unicode=yes --static=no --debug=yes

CXXFLAGS += `/usr/local/bin/wx-config --unicode=yes --static=no --debug=yes --cxxflags`
LDFLAGS += `/usr/local/bin/wx-config --unicode=yes --static=no --debug=yes --libs`
#LDFLAGS += -pthread -lwx_baseu-2.8 -lwx_gtk2u_adv-2.8 -lwx_gtk2u_html-2.8 -lwx_baseu_net-2.8  -lwx_gtk2u_core-2.8
LDFLAGS += -pthread -lwx_baseud-2.8 -lwx_gtk2ud_adv-2.8 -lwx_gtk2ud_html-2.8 -lwx_baseud_net-2.8 -lwx_gtk2ud_core-2.8 -lfftw3f

CC = g++

INCLUDES = -I$(INC_DIR)\
           -I/usr/include \
           -I$(AUDACITY_DIR)/mac \
           -I$(AUDACITY_DIR)/src \
           -I$(AUDACITY_DIR)/src/effects \
           -I$(AUDACITY_DIR)/src/widgets \
           -I$(AUDACITY_DIR)/lib-src/libsndfile/src \
           -I$(AUDACITY_DIR)/lib-src/portaudio-v19/include \
           -I$(AUDACITY_DIR)/lib-src/portmixer/include \
           -I$(AUDACITY_DIR)/lib-src/portsmf \

CXXFLAGS += -Wall -O0 $(INCLUDES)
CXXFLAGS += -DAUDACITY_DLL_API=

SYS = $(shell uname -s)

ifeq ($(SYS),Darwin)
   CXXFLAGS += -arch i386 -arch ppc -isysroot /Developer/SDKs/MacOSX10.4u.sdk
   LDFLAGS += -dylib -undefined suppress
else
   CXXFLAGS += -fPIC #-g -O0 
   LDFLAGS += -shared -Wl,-rpath,/usr/lib #-g
endif

_DEPS = dialogs.h gui.h icons.h images.h micarrayanalyzer.h module.h myartprovider.h tinyxml.h tinystr.h del_interface.h dpoint.h meshandinterpol.h virtualmikes.h reviver_assert.h multivolver.h convolver.h gtprogind.h afaudio.h
DEPS = $(patsubst %,$(INC_DIR)/%,$(_DEPS))

_OBJ = dialogs.o myartprovider.o micarrayanalyzer.o gui.o module.o tinyxml.o tinystr.o tinyxmlerror.o tinyxmlparser.o del_impl.o reviver_assert.o multivolver.o convolver.o gtprogind.o afaudio.o
OBJ = $(patsubst %,$(OBJ_DIR)/%,$(_OBJ))

all: createbindir modsrccheck basecheck $(MOD_DEBUG)

createbindir:
	@test -d $(OBJ_DIR) || mkdir $(OBJ_DIR)

modsrccheck:	
	@if test -z "$(SRC_DIR)/module.h"							   ; \
	then                                                             \
	  echo "You need to set SRC_DIR equal to the base of  "        ; \
	  echo "your module source directory.  You can do this"        ; \
	  echo "via an environemnt variable, include it on the "       ; \
	  echo "make command line or set it at the top of the"         ; \
	  echo "Makefile!"	                                           ; \
     exit 1                                                        ; \
	fi

basecheck:	
	@if test -z "$(AUDACITY_DIR)/src/Audacity.h"                   ; \
	then                                                             \
	  echo "You need to set AUDACITY_DIR equal to the base"        ; \
	  echo "of your Audacity source directory.  You can do"        ; \
	  echo "this via an environemnt variable, include it on"       ; \
	  echo "the make command line or set it at the top of"         ; \
	  echo "the Makefile."                                         ; \
     exit 1                                                       ; \
	fi

$(MOD_DEBUG): $(OBJ)
	$(CC) -o $(BIN_DIR)/$@ $^ $(LDFLAGS)
	@echo ""
	@echo "**********************************************************"
	@echo "Congrats! The plug-in was succesfully compiled!"
	@echo "Now, copy the .so file in your Audacity modules directory!"
	@echo "Just type \"sudo make install\" to copy it automatically to"
	@echo $(INST_DIR)
	@echo "**********************************************************"
	@echo ""	

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CXXFLAGS)

#
# Cleanup
#
clean: 
	-rm -f $(OBJ_DIR)/*.so $(OBJ_DIR)/*.o

#
# Install
#
install: 
	cp $(BIN_DIR)/*.so $(INST_DIR)

#
# Uninstall
#
uninstall: 
	rm $(INST_DIR)/$(MOD_DEBUG)
