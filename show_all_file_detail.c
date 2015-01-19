#include "opendir.h"

extern struct mode m ;
extern char (*file_box)[512] ;
extern int current_pos ;
extern char (*dir_box)[512] ;
extern int dir_front ;
extern int dir_current_pos ;

static inline char file_type (struct stat * stat_p) {
	if (S_ISLNK (stat_p->st_mode)) {
		return 'l' ;
	}
	else if (S_ISREG (stat_p->st_mode)) {
		return '-' ;
	}
	else if (S_ISDIR (stat_p->st_mode)) {
		return 'd' ;
	}
	else if (S_ISCHR (stat_p->st_mode)) {
		return 'c' ;
	}
	else if (S_ISBLK (stat_p->st_mode)) {
		return 'b' ;
	}
	else if (S_ISFIFO (stat_p->st_mode)) {
		return 'f' ;
	}
	else if (S_ISSOCK (stat_p->st_mode)) {
		return 's' ;
	}
	
	return '*' ;
}

void file_mode (struct stat * stat_buf , char *passin_buf) {
	char 	buf[20] ;
	int 	curr = 0 ;

	///owner mode 
	
	if (stat_buf ->st_mode & S_IRUSR) {
		buf[curr++] = 'r' ;
	}
	else {
		buf[curr++] = '-' ;
	}
	if (stat_buf ->st_mode & S_IWUSR) {
		buf[curr++] = 'w' ;
	}
	else {
		buf[curr++] = '-' ;
	}
	if (stat_buf ->st_mode & S_IXUSR) {
		buf[curr++] = 'x' ;
	}
	else {
		buf[curr++] = '-' ;
	}

	/// group mode 
	if (stat_buf ->st_mode & S_IRGRP) {
		buf[curr++] = 'r' ;
	}
	else {
		buf[curr++] = '-' ;
	}
	if (stat_buf ->st_mode & S_IWGRP) {
		buf[curr++] = 'w' ;
	}
	else {
		buf[curr++] = '-' ;
	}
	if (stat_buf ->st_mode & S_IXGRP) {
		buf[curr++] = 'x' ;
	}
	else {
		buf[curr++] = '-' ;
	}

	///other user mode
	if (stat_buf ->st_mode & S_IROTH) {
		buf[curr++] = 'r' ;
	}
	else {
		buf[curr++] = '-' ;
	}
	if (stat_buf ->st_mode & S_IROTH) {
		buf[curr++] = 'w' ;
	}
	else {
		buf[curr++] = '-' ;
	}
	if (stat_buf ->st_mode & S_IXOTH) {
		buf[curr++] = 'x' ;
	}
	else {
		buf[curr++] = '-' ;
	}
	buf[curr] = 0 ;
	
	strcpy (passin_buf , buf) ;

}
///show all file's detail 

void show_file_detail () {
	int index = 0 ;	
	struct stat stat_buf ;
	struct passwd *psd ;
	struct group * grp ;
	///输出缓冲
	char   out_put_buf[256] ;
	char   time_buf[40] ;

	printf ("current pos = %d \n" , current_pos) ;

	bzero (out_put_buf,sizeof (out_put_buf)) ;
	for ( ; index < current_pos ; ++ index ) {
	 	if ( stat (file_box[index] , &stat_buf) == -1) {
			perror ("stat error 4 ") ;
			exit (1) ;
		}
		out_put_buf[0] = file_type (&stat_buf) ;
		file_mode(&stat_buf , out_put_buf+1);
		psd = getpwuid(stat_buf.st_uid) ;
		grp = getgrgid (stat_buf.st_gid) ;
		strcpy (time_buf , ctime(&stat_buf.st_mtime)) ;
		time_buf[strlen(time_buf)-1] = 0 ;

		sprintf (out_put_buf + strlen (out_put_buf) , "%s %lu %s %s %8ld %s  %s \n" , ". " , stat_buf.st_nlink , psd -> pw_name , grp ->gr_name ,stat_buf.st_size , time_buf , file_box[index]);
		printf ("%s" ,  out_put_buf ) ;
		bzero (out_put_buf , sizeof (out_put_buf)) ;
	}
}


