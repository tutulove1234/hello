///This head file is designed for a paradigm stack  
/*
 *The purpose is to achieve a stack which could save any data type
 *
 */
#ifndef  _STACK_H
#define  _STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define 	OK 		1 
#define 	NOT_OK 		0

///The abstract data structure 

typedef struct stack {
	int 	elem_size ; 			//元素大小
	int 	curr_total_elem ; 		//当前元素总个数
	int 	total_elem ; 			//总长度
	int 	total_size ; 			//当前申请栈的总大小
	void* 	stack_pos ; 			//栈位置
} Stack , * Stack_p ;

///创建一个新栈
void 	stack_new  (Stack_p  	stk , int elemsize) ;
int 	stack_push (Stack_p 	stk , void * elem) ;
int 	stack_pop  (Stack_p 	stk , void * elem) ;
///销毁栈
void 	stack_dispose (Stack_p 	stk) ;
///扩张栈大小
void 	stack_extend (Stack_p 	stk ) ; 

#endif
