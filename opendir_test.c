/*
 * =====================================================================================
 *
 *       Filename:  opendir_test.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/17/2014 10:48:39 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  windleaves (Litong), tonglovejin1@163.com
 *        Company:  Class 1204 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include "opendir.h"


/// use it to record the fild 
struct mode m = {0} ;
char (*file_box)[512] ;
int  current_pos = 0 ;
char (*dir_box)[512] ;
int  dir_front = 0 ;
int  dir_current_pos = 0 ;
char *blank_count ;
///print usage
void print_usage () {
	printf (".\n.\n.\nUsage <ls [arguments] [filename]> \n.\n.\n") ;
}

///designed for qsort , to compare to string 
int compare_two_string (const void * str1 , const void * str2) {

	char str1_temp[512] ;
	char str2_temp[512] ;

	if (str1 == NULL || str2 == NULL ) {
		
		printf ("Can't deference NULL pointer !\n") ;
		exit (1) ;
	}

	bzero (str1_temp , 512) ;
	bzero (str2_temp , 512) ;

	memcpy (str1_temp , str1 , strlen(str1) + 1) ;
	memcpy (str2_temp , str2 , strlen(str2) + 1 ) ;
	
	if ((str1_temp[0] == '.') ) {
		strcpy (str1_temp , str1_temp + 1) ;
	}
	if ((str2_temp[0] == '.')) {
		strcpy (str2_temp , str2_temp + 1) ;
	}

	/// deal with the dirtory file 
	
	return 	(strcmp ((char *)str1_temp , (char *)str2_temp)) ;
}


int get_pretty_wide ( int curr_col ) {

	int i , j ,k ,l , flag = 0 ;
	int temp_max_len , temp_len;
	///total save the current max length 
	int total = curr_col ;
	
	blank_count = (char *)malloc (current_pos+1) ;

	///find suit wide ~ 
	for (i = 1 ; (i < current_pos) && (total  >= curr_col) ; ++i) { 
		for (k = 0 ,total = 0 ; k < current_pos ; k += i) {
			temp_max_len = strlen (file_box[k]) ;
			for (j = k ; (j < k + i) && (k+i < current_pos); j++ ) {
				temp_len = strlen (file_box[j]) ;
				if (temp_len > temp_max_len)
				      temp_max_len = temp_len  ;
			}
			for ( l = k ; l < k + i ; l++ ) {
				blank_count[l] = temp_max_len +2 ;
			}
			total += temp_max_len + 1 ;
		} 		
	}

//	printf ("total = %d\n" , total ) ;

	return 	i - 1 ;
} 

///format show the file 
void format_show () {
	int curr_col ;
	int per_col_file_count ;
	int col_count ;
	int i , j , k , remainder ;
	int temp_len , remainder_increase ;

	remainder_increase = 0 ;
	curr_col = get_console_col() ;
	//use bruse force to test which wide is best suit this window
	per_col_file_count = get_pretty_wide (curr_col) ; 

	remainder = current_pos % per_col_file_count ;
	col_count = current_pos / per_col_file_count ;
	
	/// use i to record the total print file 
	for ( i = 0 ; i < current_pos ; i++ ) {
		///This for loop control line
		for (j = 0 ; j < per_col_file_count ; j ++ ) {
			///This for loop control row
			for ( k = j ; k < current_pos ; k += per_col_file_count ) {
				temp_len = strlen (file_box[k]) ;
				printf ("%s" , file_box[k]) ;
				///add blank to suit screen 
				while (temp_len < blank_count[k]) {
					putchar(' ') ;
					temp_len++ ;
				}
				i ++ ;
			}/// deal woth remainder  
			if (remainder > 0 ) {
				remainder_increase ++ ;

				printf ("%s\n" , file_box[per_col_file_count * col_count + remainder_increase]) ;
				remainder -- ;
			} else {
				printf ("\n") ;
			}
			
		} 		
	}
}	 

void show_info () {
	if (m.show_detail) {
		show_file_detail () ;
	} else if (m.show_recursion) {
		while (dir_front != dir_current_pos) {
		
			gather_file (dir_box[dir_front]) ;

			format_show () ;

			dir_front ++ ;
		}
	} else {
		format_show () ;
	}
}

int main(int argc, char *argv[])
		
{
	int choose ;
	const char * short_opt = "alRh" ;
	struct winsize ws ;

///console size 
	
	ioctl (0,TIOCGWINSZ,&ws) ;

	file_box = (char (*)[512]) malloc (MAX_FILE_COUNT * 512) ;
	dir_box = (char (*)[512]) malloc (MAX_FILE_COUNT * 512) ;

	bzero (file_box , MAX_FILE_COUNT * 512 ) ;
	bzero (dir_box , MAX_FILE_COUNT * 512) ;

	while ( (choose = getopt (argc , argv , short_opt)) != -1)  {
		switch (choose) {
			case 'a' :
				 m.listall = 1 ; break ;
		 	case 'l' :
				 m.show_detail = 1 ; break ;
			case 'R' :
				 m.show_recursion = 1 ; break ;
			case 'h' :
				 print_usage () ; exit (0) ;
		}
	}
/// deal with the argument without filename
	if ( argc <= 2 ) {
		gather_file ("." ) ;
		show_info () ;
	}
/// deal with the argument with filename 
	else {
		while ( argc > 2 )  {
			if ( argv[argc-1][0] != '-' ) {
				gather_file (argv[argc-1]) ;
				show_info () ;
			}		
			else {
				break ;
			}
			argc -- ;
		}
	
	}
	
	free (file_box) ;
	free (dir_box) ;

		return EXIT_SUCCESS ;
}	
