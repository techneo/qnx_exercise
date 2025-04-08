
#
#	Makefile for proc_thread project
#

DEBUG = -g
CC = qcc
LD = qcc

#TARGET = -Vgcc_ntox86_64
TARGET = -Vgcc_ntoaarch64le

CFLAGS += $(DEBUG) $(TARGET) -Wall
LDFLAGS+= $(DEBUG) $(TARGET)

BINS = client server

all: $(BINS)

clean:
	rm -f *.o $(BINS)
