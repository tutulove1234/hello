#include "stack.h"  

void  	stack_new (Stack_p   stk , int elemsize) {
	stk ->elem_size = elemsize ;
	stk ->total_elem = 1 ;
	stk ->curr_total_elem = 0 ;
	stk ->total_size = elemsize * stk->total_elem ;
	stk ->stack_pos = malloc (stk->total_size) ; 
	
	assert (stk ->stack_pos != NULL) ;
} 

void 	stack_extend (Stack_p 	stk) {
	stk ->stack_pos = realloc (stk->stack_pos , stk->total_size * 2) ;
	stk ->total_size = stk ->total_size *2 ;
	stk ->total_elem = stk ->total_elem *2 ;

	assert (stk != NULL) ;
}

int 	stack_push (Stack_p 	stk , void * elem) {
	if ( (stk ->curr_total_elem +1)  > stk ->total_elem ) {
		stack_extend (stk) ;
	} 

	memcpy ((char *)stk->stack_pos + stk->curr_total_elem*stk ->elem_size , elem , stk->elem_size) ;
	
	(stk ->curr_total_elem )++ ;
	
	return 	OK ;
}

int 	stack_pop (Stack_p 	stk , void * elem) {
	
	if (stk ->curr_total_elem == 0) {

		return NOT_OK;
	} 
	
	(stk ->curr_total_elem)-- ;

	memcpy (elem , (char *)stk ->stack_pos + stk->elem_size * stk ->curr_total_elem , stk ->elem_size) ;
	printf ("%d \n" ,  *(char *)elem) ;

	return 	OK ;
}

void 	stack_dispose (Stack_p 	stk) {
	free (stk ->stack_pos);
}

int main () {
	Stack 	stk ;
	char 	i , temp;
	
	stack_new (&stk , 1) ;
	
	for (i = 0 ; i < 10 ; i ++) {
		stack_push (&stk , &i) ;	
	}

	for (i = 0 ; i < 11 ; ++i) {
		stack_pop (&stk , &temp) ;
	}

	stack_dispose (&stk);

	return 	0 ;
}
