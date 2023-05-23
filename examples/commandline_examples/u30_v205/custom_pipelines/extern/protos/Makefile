PROGS = avap
VERSION = 1.0.0

#if no aupera sdk, we use linux default compiler and env
ifeq (x$(AUP_PLATFORM_NAME),x)
LDFLAGS=-L/usr/local/lib -L/usr/lib/x86_64-linux-gnu
CXX=g++
CC=gcc
STAGING_DIR=
endif

SRCS = $(wildcard ./*.cc)
OBJS = $(patsubst %.cc,%.o,$(SRCS))

CXXFLAGS = -g -Wall -fPIC -std=gnu++17 -Ofast -Wpointer-arith -DBOOST_ALL_DYN_LINK
CXXFLAGS +=  -I.

LDFLAGS += -L. -L$(STAGING_DIR)/usr/lib -lboost_log -lglog -lpthread \



all:
	$(MAKE) proto_rule
	$(MAKE) $(PROGS)

%.o: %.cc
	$(CXX) -c $^ -o $@ $(CXXFLAGS)

proto_rule:
	protoc -I=. --cpp_out=. ./*.proto

$(PROGS):
	$(MAKE) $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -shared -o lib$(PROGS).so.$(VERSION) $(LDFLAGS)

install:
	cp lib$(PROGS).so.$(VERSION) $(STAGING_DIR)/usr/lib
	ln -sf $(STAGING_DIR)/usr/lib/lib$(PROGS).so.$(VERSION) $(STAGING_DIR)/usr/lib/lib$(PROGS).so
	mkdir -p $(STAGING_DIR)/usr/include/aup/avap/
	cp ./*.pb.h $(STAGING_DIR)/usr/include/aup/avap/

uninstall:
	rm -rf $(STAGING_DIR)/usr/lib/lib$(PROGS).so.$(VERSION)
	rm -rf $(STAGING_DIR)/usr/lib/lib$(PROGS).so
	rm -rf $(STAGING_DIR)/usr/include/aup/avap/

clean:
	rm -f lib$(PROGS).so.$(VERSION)
	rm -f ./*.pb.h
	rm -f ./*.pb.c
	rm -f ./*.pb.o