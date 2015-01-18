#ifndef _MY_CP_H
#define _MY_CP_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <strings.h>
#include <fcntl.h>
#include <assert.h>

#define 	ISDIR 			1
#define 	FALSE 			0
#define 	PATH_MAX_LEN 	1024
#define 	EXIST 			2	
#define	 	TRUE 			3	

struct mode {
	int access ;
	int directory ;	
	int help ;
} ;

/// 显示帮助信息
void help_info ();
/// copy_file 准备copy前的工作 , 包括造路径 
int copy_file (struct mode *oper_mode , int argc , char * argv[] ) ;
/// 判断是否为一个目录
int is_directory (const char *path) ;
/// 获得绝对路径
void get_full_path (const char *argv , char *full_path) ;
/// copy 文件 真正的写文件
void copy (const char *dest , char *source ) ;
/// 打开文件 , 对open 的封装
int open_file (const char *path , int mode , int access ) ;
/// copy 目录
void copy_dir (const char *source , const char *dest ) ;
/// 将源文件的名字 cat 到目标文件上
void cat_source_to_dest (const char *source , char *full_path ) ;
/// copy 文件
void copy_dir (const char * source , const char * dest );
/// 创建 目录 
void create_dir (const char *source , const char *dest ) ;

#endif
