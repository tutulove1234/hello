#include "my_cp.h"

void create_dir (const char *source , const char *dest ) {
	
	struct 	stat 	source_stat_buf ;
	int 	stat_ret = 0 ;
	int 	mkdir_ret  = 0 ;
	int 	chown_ret = 0 ;

	if ( -1 == (stat_ret = stat (source , &source_stat_buf ) )) {
		perror ("stat error");
		assert (stat_ret != -1) ;
		exit (1) ;
	}

	if ( -1 == (mkdir_ret = mkdir (dest , source_stat_buf.st_mode))) {
		perror ("mkdir error ") ;
		assert (mkdir_ret != -1 ) ;
		exit (1) ;
	}
	
	if ( -1 ==  (chown_ret = chown (dest , source_stat_buf.st_uid , source_stat_buf.st_gid ) )) {
		perror ("chown error") ;
		assert (chown_ret != -1 ) ;
		exit (1) ;
	}
}

void copy_dir (const char * source , const char * dest ) {
	
	DIR * dirp ;
	struct dirent * dir_struct ;
	char 	path_dest_temp[PATH_MAX_LEN] = {0} ;
	char 	* temp_path ;
	int 	dest_length = strlen(dest) ;
	int 	is_dir_ret = 0 ;

	create_dir (source , dest) ;
	strcpy (path_dest_temp , dest) ;
	if (NULL ==  (dirp = opendir (source) ) ){
		perror ("opendir error ") ;
		exit (1) ;
	}
	chdir (source) ; 

	temp_path = get_current_dir_name () ;
	printf ("current path is %s\n",temp_path ) ;
	while( NULL != (dir_struct = readdir (dirp ) ) ) {
		//  文件名还是自己造吧
		is_dir_ret = is_directory (dir_struct->d_name )  ;
		// 目录文件
		if ( ISDIR == is_dir_ret ) {
			if ( !strcmp (dir_struct->d_name,".") ){
				continue ;
			} else if (!strcmp (dir_struct->d_name , "..") ) {
				continue ;
			}
			printf ("copy a directory \n") ;
			strcpy ( path_dest_temp + dest_length , dir_struct->d_name) ;
			strcat (path_dest_temp , "/") ;
			copy_dir (dir_struct->d_name , path_dest_temp ) ;
			chdir ("..") ;
		} else if ( EXIST == is_dir_ret ) {
		// 普通文件
			printf ("target is a normal file , and it exist ! we will creat a dir have the same name !\n") ;
			strcpy ( path_dest_temp + dest_length , dir_struct->d_name) ;
			copy (dir_struct->d_name , path_dest_temp ) ; 
		} else {
		// 特殊文件
			printf ("target is special file  ! we will create it .\n") ;
			strcpy ( path_dest_temp + dest_length , dir_struct->d_name) ;
			copy (dir_struct->d_name , path_dest_temp ) ; 
		}
	}

	free (temp_path) ;
}

