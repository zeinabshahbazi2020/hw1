CXX:= g++ --std=c++14 -O2 -L/usr/local/lib
   2 CC:= gcc -O2 -L/usr/local/lib
   3 
   4 SRC:=./
   5 HWSRC:=./
   6 UTILSRC=./xapp-utils
   7 MSGSRC:=./xapp-mgmt
   8 
   9 ASNSRC:=../defs_hwe2sm
  10 E2APSRC:=./xapp-asn/e2ap
  11 E2SMSRC:=./xapp-asn/e2sm
  12 
  13 ####### Logging library and flags
  14 CLOGFLAGS:= `pkg-config mdclog --cflags`
  15 LOG_LIBS:= `pkg-config mdclog --libs`
  16 CURL_LIBS:= `pkg-config libcurl --libs`
  17 RNIB_LIBS:= -pthread /usr/local/include/rnib/rnibreader.a
  18 ######## Keep include dirs separate so we have transparency
  19 
  20 
  21 BASEFLAGS=  -Wall -std=c++14 $(CLOGFLAGS) 
  22 C_BASEFLAGS= -Wall $(CLOGFLAGS) -DASN_DISABLE_OER_SUPPORT
  23 
  24 XAPPFLAGS= -I./
  25 HWFLAGS= -I./
  26 UTILFLAGS= -I$(UTILSRC)
  27 MSGFLAGS= -I$(MSGSRC)
  28 
  29 ASNFLAGS=-I$(ASNSRC) -I/usr/local/include/riclibe2ap -DASN_DISABLE_OER_SUPPORT
  30 E2APFLAGS = -I$(E2APSRC)
  31 E2SMFLAGS = -I$(E2SMSRC)
  32 
  33 ########libs
  34 
  35 LIBS= -lsdl -lrmr_si -lriclibe2ap -lpthread -lm $(LOG_LIBS) $(CURL_LIBS) $(RNIB_LIBS)
  36 COV_FLAGS= -fprofile-arcs -ftest-coverage
  37 
  38 #######
  39 HWXAPP_SRC= hw_xapp_main.cc
  40 XAPP_SRC= xapp.cc
  41 UTIL_SRC= $(wildcard $(UTILSRC)/*.cc)
  42 MSG_SRC= $(wildcard $(MSGSRC)/*.cc)
  43 
  44 E2AP_SRC= $(wildcard $(E2APSRC)/*.cc)
  45 E2SM_SRC= $(wildcard $(E2SMSRC)/*.cc)
  46 ASN1C_SRC= $(wildcard $(ASNSRC)/*.c)
  47 
  48 ##############Objects
  49 UTIL_OBJ=${UTIL_SRC:.cc=.o}
  50 XAPP_OBJ=${XAPP_SRC:.cc=.o}
  51 HWXAPP_OBJ= ${HWXAPP_SRC:.cc=.o} 
  52 MSG_OBJ= ${MSG_SRC:.cc=.o}
  53 
  54 E2AP_OBJ = $(E2AP_SRC:.cc=.o)
  55 E2SM_OBJ = $(E2SM_SRC:.cc=.o)
  56 ASN1C_MODULES = $(ASN1C_SRC:.c=.o)
  57 
  58 $(ASN1C_MODULES): export CFLAGS = $(C_BASEFLAGS) $(ASNFLAGS)
  59 $(UTIL_OBJ):export CPPFLAGS=$(BASEFLAGS) $(UTILFLAGS) $(E2APFLAGS) $(E2SMFLAGS) $(ASNFLAGS) $(MSGFLAGS)
  60 
  61 $(MSG_OBJ):export CPPFLAGS=$(BASEFLAGS) $(MSGFLAGS) $(ASNFLAGS) $(E2APFLAGS) $(E2SMFLAGS)
  62 $(E2AP_OBJ): export CPPFLAGS = $(BASEFLAGS) $(ASNFLAGS) $(E2APFLAGS)
  63 $(E2SM_OBJ): export CPPFLAGS = $(BASEFLAGS) $(ASNFLAGS) $(E2SMFLAGS)
  64 $(XAPP_OBJ): export CPPFLAGS = $(BASEFLAGS) $(XAPPFLAGS) $(UTILFLAGS) $(MSGFLAGS) $(E2APFLAGS) $(E2SMFLAGS) $(ASNFLAGS)
  65 
  66 $(HWXAPP_OBJ):export CPPFLAGS=$(BASEFLAGS) $(HWFLAGS) $(XAPPFLAGS) $(UTILFLAGS) $(MSGFLAGS) $(E2APFLAGS) $(E2SMFLAGS) $(ASNFLAGS)
  67 
  68 OBJ= $(HWXAPP_OBJ) $(UTIL_OBJ) $(MSG_OBJ)  $(ASN1C_MODULES) $(E2AP_OBJ) $(E2SM_OBJ) $(XAPP_OBJ)
  69 
  70 print-%  : ; @echo $* = $($*)
  71 
  72 hw_xapp_main: $(OBJ)
  73         $(CXX) -o $@  $(OBJ) $(LIBS) $(RNIBFLAGS) $(CPPFLAGS) $(CLOGFLAGS)  
  74 
  75 install: hw_xapp_main
  76         install  -D hw_xapp_main  /usr/local/bin/hw_xapp_main
  77 
  78 clean:
  79         -rm *.o $(ASNSRC)/*.o $(E2APSRC)/*.o $(UTILSRC)/*.o $(E2SMSRC)/*.o  $(MSGSRC)/*.o $(SRC)/*.o hw_xapp_main 
