
#
#	Makefile for interrupt project
#

DEBUG = -g
CC = qcc
LD = qcc

TARGET = -Vgcc_ntox86_64
#TARGET = -Vgcc_ntoaarch64le


CFLAGS += $(DEBUG) $(TARGET) -Wall
LDFLAGS+= $(DEBUG) $(TARGET)

BINS = intsimple_kbd_ev intsimple_kbd_ist

all:	$(BINS)

clean:
	rm -f *.o $(BINS)

