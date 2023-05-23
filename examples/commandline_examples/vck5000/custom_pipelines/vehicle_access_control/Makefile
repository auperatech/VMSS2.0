CALCULATOR = plate_recognizer
VERSION = 1.0.0

#if no aupera sdk, we use linux default compiler and env
ifeq (x$(AUP_PLATFORM_NAME),x)
LDFLAGS=-L/usr/local/lib -L/usr/lib/x86_64-linux-gnu
CXX=g++
CC=gcc
STAGING_DIR=
endif

OBJS = plate_recognizer.o  ../extern/protos/plate_recognizer.pb.o

CXXFLAGS = -g -Wall -fPIC -std=gnu++17 -Ofast -Wpointer-arith -DBOOST_ALL_DYN_LINK -Wfatal-errors
CXXFLAGS +=  -I. -I$(STAGING_DIR)/usr/include -I../extern 

LDFLAGS +=  -L../.. -L. -L../extern

LDFLAGS +=  -L$(STAGING_DIR)/usr/lib -lavaf -lboost_log

LDFLAGS +=  -llicenseplate -lpthread -lvitis_ai_library-platedetect -lvitis_ai_library-platenum -ldetector -lopencv_core -lopencv_imgcodecs -lopencv_imgproc -lglog -lprotobuf -lvitis_ai_library-dpu_task -lvitis_ai_library-model_config -lvitis_ai_library-ssd -lvitis_ai_library-refinedet -lvitis_ai_library-yolov2 -lvitis_ai_library-yolov3 -lvitis_ai_library-facedetect -lprotobuf

LDFLAGS += -lvitis_ai_library-math


all:
	$(MAKE) avap
	$(MAKE) $(CALCULATOR)


$(CALCULATOR):
	$(MAKE) $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -shared -o lib$(CALCULATOR).calculator.$(VERSION) $(LDFLAGS)

avap:
	cp ./*proto ../extern/protos
	$(MAKE) -C ../extern/protos
	$(MAKE) install -C ../extern/protos

%.o: %.cc
	$(CXX) -c $^ -o $@ $(CXXFLAGS)

install: 
ifeq (x$(AUP_PLATFORM_NAME),x)
	cp lib$(CALCULATOR).calculator.$(VERSION) /tmp
	ln -sf /tmp/lib$(CALCULATOR).calculator.$(VERSION) /tmp/lib$(CALCULATOR).calculator
else
	cp lib$(CALCULATOR).calculator.$(VERSION) $(STAGING_DIR)/usr/lib
	ln -sf $(STAGING_DIR)/usr/lib/lib$(CALCULATOR).calculator.$(VERSION) $(STAGING_DIR)/usr/lib/lib$(CALCULATOR).calculator
endif

clean:
	rm -f lib$(CALCULATOR).calculator $(OBJS)

uninstall:
ifeq (x$(AUP_PLATFORM_NAME),x)
	rm -rf /tmp/lib$(CALCULATOR).calculator.$(VERSION)
else
	rm -rf $(STAGING_DIR)/usr/lib/lib$(CALCULATOR).calculator.$(VERSION)
endif
