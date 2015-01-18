#!Makefile

CC := gcc 
CFLAG :=  -Wall -std=c99 -g

.PHONY : clean

copy.out: help_info.o my_cp.o copy_file.o copy_dir.o my_cp.h
	$(CC) -o $@  $(CFLAG) $^
help_info.o:help_info.c my_cp.h
	$(CC) -c $^  $(CFLAG) 
my_cp.o : my_cp.c my_cp.h
	$(CC) -c $^  $(CFLAG) 
copy_file.o :copy_file.c my_cp.h
	$(CC) -c $^  $(CFLAG) 
copy_dir.o :copy_dir.c my_cp.h
	$(CC) -c $^ $(CFLAG)

clean:
	$(RM) *.o copy.out

