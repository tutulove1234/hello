#include "my_cp.h"
//
const 	char * argv_p = "prh" ;

// 这里要实现 p r 考虑同时出现的情况
extern int opterr ;

int main (int argc , char *argv[]) {
	
	int 	option ;
	struct 	mode	oper_mode  = {0,0,0} ;
	opterr = 0 ;
	// 设置不向终端输出错误信息

	while ((option = getopt (argc , argv , argv_p)) != -1 ) {
		switch (option) {
			case 'p' :oper_mode.access = 1 ; printf ("p appear!\n") ;break ;
			case 'r' :oper_mode.directory = 1 ; printf ("r appear!\n") ;break ;
			case 'h' :oper_mode.help = 1 ;help_info() ;break ;
			case '?' : printf ("invalid argument !\n") ;  break;
			case ':' : printf ("lack of target!\n") ; break;
		}
	}
	if ( argc < 3 ) {
		printf ("invalid argument !\n") ;
		help_info() ;
		exit (1) ;
	}

	copy_file (&oper_mode , argc , argv ) ;
	
	return 0;
}

 
