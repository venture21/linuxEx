
CC = gcc
OBJECTS = upper.o \
		  useupper.o
TARGET = upper useupper		  
#SRCS = $(OBJECTS:.o=.c)

all : $(TARGET)

upper : upper.c
	$(CC) -o $@ $<

useupper : useupper.c
	$(CC) -o $@ $<

clean :
	$(RM) $(OBJECTS) $(TARGET)
