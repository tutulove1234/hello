#include "opendir.h"

int get_console_col(){

	int col = 80 ;
	int row = 24 ;

#ifdef 	TIOCGSIZE
	struct ttysize ts ;
	ioctl ( STDIN_FILENO , TIOCGSIZE , &ts ) ;

	col = ts.ts_cols ;
	row = ts.ts_lines ;
#elif 	defined(TIOCGWINSZ)	
	struct winsize ts ;
	ioctl (STDIN_FILENO , TIOCGWINSZ , &ts) ;
	col = ts.ws_col ;
	row = ts.ws_row ;
#endif 
	return col ;
}
