
#
#	Makefile for resmgr project (rmintro)
#



DEBUG = -g
CC = qcc
LD = qcc

TARGET = -Vgcc_ntox86_64
#TARGET = -Vgcc_ntoarmv7le
#TARGET = -Vgcc_ntoaarch64le

CFLAGS += $(DEBUG) $(TARGET) -Wall
LDFLAGS+= $(DEBUG) $(TARGET) -lsecpol

BINS = example example_initialization example_read example_write

all:	$(BINS)

clean_solutions:
	rm -f *.o $(BINS)
