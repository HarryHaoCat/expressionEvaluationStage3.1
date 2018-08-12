/*************************************************************************
> File Name: expressionEvaluation.c
> Author: HaoJie
> Mail: 954487858@qq.com
> Created Time: 2018年07月16日  星期一 16h22m3s
************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include "sequentialStack.h"

/*  Initialize the sequential stack
 */
State InitStack(SequentialStackChar *s) 
{
	if(s == NULL)  //If the pointer s points to NULL.
	{
		printf("<Error! This pointer is NULL>\n");
		return FAILED;
	}
	s->top = 0;
	return SUCCEEDED;
}

/*  Release the memory of the sequential stack
 */
void DestroyStack(SequentialStackChar *s)    
{
	if(s == NULL)
	{
		printf("<Error! This pointer is NULL>\n");
		return;
	}
	free(s);   //Free the pointer that points to the stack.
}

/*  Check if the stack is empty.
    Return SUCCEEDED to indicate the stack is empty.
    Return FAILED to indicate the stack is NOT empty.
 */
State StackEmpty(SequentialStackChar *s)
{	
	if(s == NULL)
	{
		printf("<Error! This pointer is NULL>\n");
		return FAILED;
	}
	if(s->top == 0)
		return SUCCEEDED;
	return FAILED;
}

/*  If the stack is NOT full, push e into it and return SUCCEEDED to indicate a successful push.
    If the stack is full, merely return FAILED to indicate an unsuccessful push.
 */
State Push(SequentialStackChar *s, ElemType e)
{
	if(s == NULL)
	{
		printf("<Error! This pointer is NULL>\n");
		return FAILED;
	}
	if(s->top == MaxSize)
	{
		//printf("The stack is full!\n");
		return FAILED;
	}
	s->data[s->top++] = e;
	return SUCCEEDED;

}

/*  If the stack is NOT empty, pop the top of the stack into e and return SUCCEEDED to indicate a successful pop.
    If the stack is empty, merely return FAILED to indicate an unsuccessful pop.
 */
State Pop(SequentialStackChar *s, ElemType *e)
{
	if(s == NULL)
	{
		printf("<Error! This pointer is NULL>\n");
		return FAILED;
	}
	if(s->top == 0)
	{
		//printf("The stack is empty!\n");
		return SUCCEEDED;
	}
	*e = s->data[s->top-1];
	s->top--;
	return SUCCEEDED;
}

/*  If the stack is NOT empty, assign the top of the stack to e and return SUCCEEDED to indicate a successful gettop.
    If the stack is empty, merely return FAILED to indicate an unsuccessful gettop.
 */
State GetTop(SequentialStackChar *s, ElemType *e)
{
	if(s == NULL)
	{
		printf("<Error! This pointer is NULL>\n");
		return FAILED;
	}
	if(s->top == 0)
	{
		//printf("The stack is empty!\n");
		return FAILED;
	}
	*e = s->data[s->top-1];
	return SUCCEEDED;

}
/* Interfaces for the 2nd stack for double elements*/

//  Initialize the sequential stack

State InitStackDouble(SequentialStackDouble *s)
{
	if(s == NULL)
	{
		printf("<Error! This pointer is NULL>\n");
		return FAILED;
	}
	s->top = 0;
	return SUCCEEDED;
}

/*  Release the memory of the sequential stack
 */
void DestroyStackDouble(SequentialStackDouble *s)
{
	if(s == NULL)
	{
		printf("<Error! This pointer is NULL>\n");
		return;
	}
	free(s);
}

/*  Check if the stack is empty.
 Return SUCCEEDED to indicate the stack is empty.
 Return FAILED to indicate the stack is NOT empty.
 */
State StackEmptyDouble(SequentialStackDouble *s)
{
	if(s == NULL)
	{
		printf("<Error! This pointer is NULL>\n");
		return FAILED;
	}
	if(s->top == 0)
		return SUCCEEDED;
	return FAILED;
}
/*  If the stack is NOT full, push e into it and return SUCCEEDED to indicate a successful push.
    If the stack is full, merely return FAILED to indicate an unsuccessful push.
 */

State PushDouble(SequentialStackDouble *s, ElemTypeDouble e)
{
	if(s == NULL)
	{
		printf("<Error! This pointer is NULL>\n");
		return FAILED;
	}
	if(s->top == MaxSize)
	{
		//printf("The stack is full!\n");
		return FAILED;
	}
	s->data[s->top++] = e;
	return SUCCEEDED;
	
}
/*  If the stack is NOT empty, pop the top of the stack into e and return SUCCEEDED to indicate a successful pop.
    If the stack is empty, merely return FAILED to indicate an unsuccessful pop.
 */
State PopDouble(SequentialStackDouble *s, ElemTypeDouble *e)
{
	if(s == NULL)
	{
		printf("<Error! This pointer is NULL>\n");
		return FAILED;
	}
	if(s->top == 0)
	{
		//printf("The stack is empty!\n");
		return FAILED;
	}
	*e = s->data[s->top-1];
	s->top--;
	return SUCCEEDED;
	
}
/*  If the stack is NOT empty, assign the top of the stack to e and return SUCCEEDED to indicate a successful gettop.
    If the stack is empty, merely return FAILED to indicate an unsuccessful gettop.
 */
State GetTopDouble(SequentialStackDouble *s, ElemTypeDouble *e)
{
	if(s == NULL)
	{
		printf("<Error! This pointer is NULL>\n");
		return FAILED;
	}
	if(s->top == 0)
	{
		//printf("The stack is empty!\n");
		return FAILED;
	}

	*e = s->data[s->top-1];
	return SUCCEEDED;
	
}