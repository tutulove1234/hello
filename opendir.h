#ifndef  _OPEN_DIR_H
#define  _OPEN_DIR_H
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <stdbool.h>
#include <strings.h>

#define 	MAX_FILE_COUNT 		8000
#define  	ELEMSIZE 		512	

struct 	mode 	{
	unsigned int listall:1 ;
	unsigned int show_detail:1 ;
	unsigned int show_recursion:1 ;
} ;


void print_usage () ;

int compare_two_string (const void * str1 , const void * str2 ) ; 

void gather_file (const char * file_path , char (*file_box)[512] , int * current_pos) ;

void format_show (char (*file_box)[512] , const int current_pos ) ;

void show_file_detail (char (*file_box)[512] , const int current_pos) ;

int get_console_col () ;

_Bool is_dir (const char * p  ) ; 

#endif 
