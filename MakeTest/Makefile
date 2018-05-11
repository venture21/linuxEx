# Makefile
.SUFFIXES : .c .o

OBJECTS = main.o \
		  print.o \
		  input.o
SRCS = $(OBJECTS:.o=.c)

CFLAGS = -g
TARGET = testMain
CC = gcc

#$@ 현재 목표 파일의 이름
$(TARGET) : $(OBJECTS)
	$(CC) -o $@ $(OBJECTS)

#$< 현재 목표 파일(TARGET)보다 더 최근에 갱신된 파일명으로, 
#첫번째 종속물의 이름				 
#.c.o :
#	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM) $(OBJECTS) $(TARGET) core

main.o : main.c
print.o : print.c
input.o : input.c
