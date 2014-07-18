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
#include <time.h>
#include <pwd.h>
#include <grp.h>

#define 	MAX_FILE_COUNT 		4000
#define  	ELEMSIZE 		512	

struct 	mode 	{
	unsigned int listall:1 ;
	unsigned int show_detail:1 ;
	unsigned int show_recursion:1 ;
} ;

//char 	(*file_box)[512] ;
//int 	current_pos = 0 ;
//char 	(*dir_box)[512] ;
/// dir_front save the queue front 
//int 	dir_front = 0 ;
/// dir_current_pos save the queue current pos 
/*
*when user use -R mode , the dir_box will save the directory 
*into the dir_box , That is to say , when a new file was traveled
*and meet a dir , it will be saved in the queue rare , when trave
*l a file , first record the current pos , then out queue till 
*this pos . 
*/
//int 	dir_current_pos = 0 ;

void print_usage () ;

int compare_two_string (const void * str1 , const void * str2 ) ; 

void gather_file (const char * file_path ) ;

void format_show () ;

void show_file_detail () ;

int get_console_col () ;

_Bool is_dir (const char * p  ) ; 

#endif 
