CALCULATOR = vehicle_classificaiton
VENDOR = aupera
VERSION = 1.0.0


#if no aupera sdk, we use linux default compiler and env
ifeq (x$(AUP_PLATFORM_NAME),x)
LDFLAGS=-L/usr/local/lib -L/usr/lib/x86_64-linux-gnu
CXX=g++
CC=gcc
STAGING_DIR=
endif

OBJS = $(CALCULATOR).o  ../extern/protos/vehicle_classificaiton.pb.o

CXXFLAGS = -g -Wall -Wfatal-errors -fPIC -std=gnu++17 -Ofast -Wpointer-arith -DBOOST_ALL_DYN_LINK
# CXXFLAGS +=  -I. -I$(STAGING_DIR)/usr/include
CXXFLAGS +=  -I. -I../extern -I$(STAGING_DIR)/usr/include

#LDFLAGS = -L../.. -L. -L$(STAGING_DIR)/usr/lib
LDFLAGS = -L../extern -L.

LDLIBS = -lavaf

LDLIBS += -lopencv_core -lopencv_imgproc -lprotobuf -ldl -lrt -laupera -lpthread -lboost_filesystem -lboost_log_setup \
          -lboost_log -lboost_thread -lboost_system -laupcodec -lvpm -lavformat -lswscale -lavutil -lglog -lavap

LDLIBS += -lvitis_ai_library-vehicleclassification -lvitis_ai_library-dpu_task \
          -lvitis_ai_library-xnnpp -lvitis_ai_library-model_config \
          -lvitis_ai_library-math -lvart-util -lxir

ip1="10.10.10.2"
ip2="10.10.10.6"
password="VideoAlive@2020"

all:
	$(MAKE) avap
	$(MAKE) $(CALCULATOR)

$(CALCULATOR): 
	$(MAKE) $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -shared -o lib$(VENDOR).$(CALCULATOR).calculator.$(VERSION) $(LDFLAGS) $(LDLIBS)

avap:
	cp ./*proto ../extern/protos
	$(MAKE) -C ../extern/protos
	$(MAKE) install -C ../extern/protos

%.o: %.cc
	$(CXX) -c $^ -o $@ $(CXXFLAGS)

install: 
	sshpass -p $(password) scp -o "StrictHostKeyChecking=no" lib$(VENDOR).$(CALCULATOR).calculator.$(VERSION) root@$(ip1):/tmp/
	sshpass -p $(password) scp -o "StrictHostKeyChecking=no" lib$(VENDOR).$(CALCULATOR).calculator.$(VERSION) root@$(ip2):/tmp/
	sshpass -p $(password) scp -o "StrictHostKeyChecking=no" ../extern/protos/libavap.so.1.0.0 root@$(ip1):/usr/lib/
	sshpass -p $(password) scp -o "StrictHostKeyChecking=no" ../extern/protos/libavap.so.1.0.0 root@$(ip2):/usr/lib/
	sshpass -p $(password) ssh -o "StrictHostKeyChecking=no" root@$(ip1) "ln -sf /tmp/libaupera.vehicle_classificaiton.calculator.1.0.0 /tmp/libaupera.vehicle_classificaiton.calculator"
	sshpass -p $(password) ssh -o "StrictHostKeyChecking=no" root@$(ip1) "ln -sf /usr/lib/libavap.so.1.0.0 /usr/lib/libavap.so"
	sshpass -p $(password) ssh -o "StrictHostKeyChecking=no" root@$(ip2) "ln -sf /tmp/libaupera.vehicle_classificaiton.calculator.1.0.0 /tmp/libaupera.vehicle_classificaiton.calculator"
	sshpass -p $(password) ssh -o "StrictHostKeyChecking=no" root@$(ip2) "ln -sf /usr/lib/libavap.so.1.0.0 /usr/lib/libavap.so"	

clean:
	rm -f lib$(VENDOR).$(CALCULATOR).calculator $(OBJS)

uninstall:
ifeq (x$(AUP_PLATFORM_NAME),x)
	rm -rf /tmp/lib$(VENDOR).$(CALCULATOR).calculator
	rm -rf /tmp/lib$(VENDOR).$(CALCULATOR).calculator.$(VERSION)
else
	rm -rf $(STAGING_DIR)/usr/lib/lib$(VENDOR).$(CALCULATOR).calculator
	rm -rf $(STAGING_DIR)/usr/lib/lib$(VENDOR).$(CALCULATOR).calculator.$(VERSION)
endif
