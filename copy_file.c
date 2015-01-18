#include "my_cp.h"

inline int is_directory (const char * path) {
	
	struct stat buf ;
	int 	stat_ret = 0 ;
	stat_ret = stat (path , &buf) ;

	if ( -1 == stat_ret ) {
		printf ("second argv doesn't exist\n") ;
		return FALSE ;
	} else if ( S_ISREG(buf.st_mode) ) {
		printf ("second argv of file is exist\n") ;
		return EXIST ;
	}
	if (S_ISDIR(buf.st_mode) ){
		printf ("pass in a directory !\n" ) ;
		return ISDIR ;
	} 
}

void 	get_full_path (const char * argv , char * full_path ) {
	if ( '/' == argv[0] ) {
		printf ("seconnd argv is absolute address\n") ;
		strncpy (full_path , argv , strlen(argv) +1) ;
		printf ("path is %s\n" , full_path) ;
	} else {
		getcwd (full_path , PATH_MAX_LEN ) ;	
		int 	length_temp = strlen(full_path) ;
		full_path[length_temp] = '/' ;
		full_path[length_temp+1] = 0 ;
		strcat (full_path,argv) ;
		printf ("path is %s\n" , full_path) ;
	}
}

void 	copy (const char * source ,  char * dest ) {
	char 	buffer[4096] ;
	int 	read_size = 1 ;
	int 	write_size = 0 ;
	int 	fd_dest = 0 ;
	int 	fd_source = 0 ;
	struct 	stat stat_source ;

	printf ("dest file name is %s\n",dest) ;
	fd_dest = open_file (dest , O_RDWR|O_CREAT,S_IRWXU) ;
	fd_source = open_file(source , O_RDWR , 0);
	while ( read_size != 0 ) {
		
		if ( -1 == (read_size = read (fd_source , buffer , 4096) )) {
			perror ("read error ") ;
			exit (1) ;
		}
		if ( -1 == (write_size = write (fd_dest , buffer , read_size )) ) {
			if (read_size != write_size ) {
				printf ("write error!\n") ;
				exit (1) ;
			}
		}
	}
	// 修改权限 和 用户id 组id	
	if ( -1 == fstat (fd_source ,&stat_source )) {
		perror ("fstat error ") ;
		exit (1);
	}
	if ( -1 == fchmod (fd_dest , stat_source.st_mode ) ) {
		perror ("fchmod error " ) ;
		exit (1) ;
	}
	if ( -1 == fchown (fd_dest , stat_source.st_uid , stat_source.st_gid) ) {
		perror ("fchown error ") ;
		exit (1) ;
	}
	close (fd_source) ;
	close (fd_dest) ;
}
// 封装一下 open
int 	open_file (const char * path , int mode ,  int access) {
	int 	ret_fd = 0;
	if ( 0 == access ) {
		if ( (ret_fd = open (path, mode) ) < 0 ) {
			perror ("open dest error ") ;
			exit (1) ;
		} 
	} else {
		if ( (ret_fd = open (path, mode , access) ) < 0 ) {
			perror ("open dest error ") ;
			exit (1) ;
		} 
	}

	return ret_fd ;
}
// 函数完成将source 的最后一个字段链接到的dest上
void 	cat_source_to_dest (const char * source , char * path ) {
	int 	source_length = strlen(source);
	// 这里保证 source 最后一位为 '/'
	source_length -=2 ;
	while ( ('/'  != source[source_length]) && ( 0 != source_length) ) {
		source_length -- ;
	}
	if ( '/' == source[source_length] ) {
		strcat (path, source+source_length) ;
	} else {
		strcat (path , source) ;
	}
	int path_length = strlen(path) ;
	if ('/' != path[path_length-1]){
		strcat (path,"/") ;
	}
	printf ("final path is %s\n",path) ;
}

/// 这里应该做 错误检查 , 检查相对应模式下的错误情况 比如在copy 文件时  , source 不能是目录 , copy 目录时 , source 不能是文件等 必须做特殊处理
int copy_file (struct mode *oper_mode , int argc , char* argv[]) {

	// 保存 argv 中的 dest
	char 	path_buf[PATH_MAX_LEN] ;
	char 	source_path[PATH_MAX_LEN] ;
// 这里 对于递归 ， 接口写好！ ， directory ， directory 参数 ， 这样的话， 就可以调， target的话，
	bzero (path_buf , PATH_MAX_LEN) ;
	strcpy(source_path , argv[argc-2]) ;
	if( 1 == oper_mode->directory ) {
		printf ("copy directory!\n ") ;  	// source是目录
		get_full_path (argv[argc-1] , path_buf) ;	
		// 判断用户输入的是否符合自己规定
		if ( '/' != path_buf[strlen(path_buf)-1] ){
			strcat (path_buf , "/") ;
		}
		if ( '/' != source_path[strlen(source_path)-1] ) {
			strcat (source_path , "/" ) ;
		}
		cat_source_to_dest (source_path , path_buf) ;
		copy_dir (source_path,path_buf) ;
		return TRUE ;	
	} else {
		// 全都处理成绝对路径 
		get_full_path (argv[argc-1] ,path_buf ) ;		
		if (ISDIR == is_directory(path_buf )) {
			printf ("target is a direcroty !\n") ;
			// 首先处理名字
			// 我需要st_mode 值 和 st_uid , st_gid值 然后去调函数设置	
			// 生成最终的文件名
			if ( '/' != path_buf[strlen(path_buf)-1] ){
				strcat (path_buf , "/") ;
			}
			cat_source_to_dest (argv[argc-2] , path_buf) ;
			path_buf[strlen(path_buf)-1] = 0 ;
			copy (argv[argc-2] , path_buf ) ;
		}else {
			// 判断文件是否存在
			if (!access (path_buf , F_OK)) {
			// 存在
				printf ("file now is exist ! overwrite it now !\n") ;
			}
			copy (argv[argc-2] , path_buf ) ;
			return TRUE ;
		}	
	}	
	return TRUE ;
}

