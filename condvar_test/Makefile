
#
#	Makefile for hello project
#

DEBUG = -g
CC = qcc
LD = qcc


TARGET = -Vgcc_ntox86_64
#TARGET = -Vgcc_ntoaarch64le


CFLAGS += $(DEBUG) $(TARGET) -Wall
LDFLAGS+= $(DEBUG) $(TARGET)

all:	condvar_test

clean:
	rm -f *.o condvar_test
	cd solutions; make clean_soln

