#include "opendir.h"

extern struct mode m ;
extern char (*file_box)[512] ;
extern int current_pos ;
extern char (*dir_box)[512] ;
extern int dir_front ;
extern int dir_current_pos ;
///save all file in the array 

void gather_file (const char * file_path ) {
	DIR * dirp ;
	struct dirent * dirent_p ;
	struct stat stat_buf , stat_temp ;
	char 	path[512] , temp[512];
	int 	i ;

	//init the file path will use next 
	bzero (path , sizeof (path)) ;
	bzero (temp  , sizeof (temp)) ;
	if (stat (file_path , &stat_buf) == -1 ) {
		perror ("stat error 1") ;
		exit (1) ;
	}
	///current file is a directory
	if ( S_ISDIR (stat_buf.st_mode) ) {
		if ( (dirp = opendir (file_path)) == NULL ) {
			perror ("opendir error 1") ;
			exit (1) ;
		}
		strcpy (temp , file_path) ;
		strcat (temp , "/") ;
		i = strlen (temp) ;
	///read directory 
		while (( dirent_p = readdir (dirp)) != NULL) {
			strcpy (temp+i,dirent_p->d_name) ;
//			printf ("path temp value (full path) %s \n" , temp ) ;
			if ( stat (temp , &stat_temp) == -1 ) {
				perror ("stat error 3 ") ;	
				exit (1) ;
			}
			if ((dirent_p ->d_name[0]) == '.' ||((dirent_p->d_name[0]=='.') && (dirent_p ->d_name[1] == '.'))) {
			/// ignore "." or not 
				if (m.listall) {
					strcpy (file_box[(current_pos)] , dirent_p ->d_name ) ;
					(current_pos) ++ ;
				} else {
					continue ;
				}
			} /// judging if dir , if dir save in queue
			else  if (S_ISDIR(stat_temp.st_mode)){
				strcpy (file_box[(current_pos)] , dirent_p->d_name ) ;
				getcwd (dir_box[dir_current_pos] ,512) ;
				strcat (dir_box[dir_current_pos] , "/" ) ;
				strcat (dir_box[dir_current_pos] , dirent_p ->d_name ) ;
				strcat (dir_box[dir_current_pos] , "/") ;
				(current_pos) ++ ; 
				dir_current_pos ++ ;
			}
	
		 /// other case , just copy
			else {
				strcpy (file_box[(current_pos)] , dirent_p ->d_name) ;
				(current_pos) ++ ;
			}
		}
	}
		qsort ((void*)file_box , current_pos , ELEMSIZE , compare_two_string) ;
		
}
