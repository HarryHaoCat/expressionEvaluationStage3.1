/*************************************************************************
> File Name: expressionEvaluation1.c
> Author: HaoJie
> Mail: 954487858@qq.com
> Created Time: 2018年08月6日  星期一 17h22m3s
************************************************************************/
#include <stdio.h>
#include "sequentialStack.h"
#include <ctype.h>
int isUnary(char* infixExpression);                   //Check if some operator is a unary operator 
int Priority(char c);                                 //Calculate the priority value of the operators
char previous(char* infixExpression, int index);      //Get the first non_space character before the current character
char next(char* infixExpression, int index);          //Get the first non_space character after the current character
void printError(char* infixExpression, int index);    //Mark the location of error.

/*The function converts infix expression into postfix expression. 
  Firstly, check if the infix expression is legal, if it's illegal, print error information and return FAILED.
  If the infix expresssion is legal, convert it into postfix expression and retuen 0.  
*/
int infixToPostfix(char* infixExpression, char postfixExpression[]){   
	for (int i = 0; i < 100; i++)   	                               
		postfixExpression[i] = '\0';
	int braceNum = 0;
	SequentialStackChar* s = (SequentialStackChar*)malloc(sizeof(SequentialStackChar));
	ElemType e;
	if(InitStack(s) == FAILED){
		printf("<Error! Initial stack fail>\n");
		return FAILED;
	}
	int numIndex = 0, index = 0;
	int operand = 0, blank = 0, leftBrace = 0, rightBrace = 0;
	while(infixExpression[index] != '\0'){
		/*
		  Check whether the current character is illegal,
		  if the current character isn't '+', '-', '*', '/', ' ', '(', ')' or number '0'-'9', 
		  then print proper error information and return FAILED to indicate illegal characters in expression.  
		*/
		if(!(isdigit(infixExpression[index]) || infixExpression[index] == '+' || infixExpression[index] == ' '  
			|| infixExpression[index] == '-' || infixExpression[index] == '*' || infixExpression[index] == '/'
			|| infixExpression[index] == '(' || infixExpression[index] == ')')){
			printError(infixExpression, index);
			printf("<Error! Illegal character \'%c\' in the expression>\n", infixExpression[index]);
			return FAILED;
		}
		//Count the number of spaces
		else if(infixExpression[index] == ' '){    
			blank++;
		}
		/*
		  If the current character is a digit, check whether the character lacks operator, if so, then print error information and 
		  return FAILED;
		  If it's a legal digit, put it into the array postfixExpression.   
		*/
		else if(isdigit(infixExpression[index])){   	
			if(infixExpression[index + 1] == ' ' && isdigit(next(infixExpression, index))){	
				printError(infixExpression, index + 1);
				printf("<Error! A space between two operands>\n");
				return FAILED;
			}
			else{
				postfixExpression[numIndex++] = infixExpression[index];
				if(!isdigit(infixExpression[index + 1])){
					postfixExpression[numIndex++] = '#';
					operand++;
				}			
			}
		}
		//If the current character is operator, space or brace
		else if(infixExpression[index] == '+' || infixExpression[index] == '-' || infixExpression[index] == '*'  
			 || infixExpression[index] == '/' || infixExpression[index] == '(' || infixExpression[index] == ')'){
			/*Handle illegal unary operator '+' and '-'.
			  (1)A space follows a unary operator '+' or '-'.
			  (2)A unary operator '+' or '-' lacks operand.
			  (3)An operaor '+' or '-' follows a unary operator '+' or '-'.
			  (4)There is only one operator '+' or '-' in the expression without operands.
			*/
			if(infixExpression[index] == '+'  || infixExpression[index] == '-'){ 
				if((previous(infixExpression,index) == ' ' || index == 0 || previous(infixExpression,index) == '(') && infixExpression[index + 1] == ' '){
					printError(infixExpression, index + 1);
					printf("<Error! A space follows a unary \'%c\'>\n", infixExpression[index]);
					return FAILED;
				}
				else if(next(infixExpression, index) == '\0' || next(infixExpression, index) == ')'){
					printError(infixExpression, index);
					printf("<Error! No operand after operator \'%c\'>\n", infixExpression[index]);
					return FAILED;
				}
				else if(next(infixExpression, index) == '+' || next(infixExpression, index) == '-' || next(infixExpression, index) == '*' || next(infixExpression, index) == '/'){
					printError(infixExpression, index);
					printf("<Error! Operator \'%c\'  follows another operator \'%c\' in the expression>\n", next(infixExpression, index), infixExpression[index]);
					return FAILED;
				}
			}
			/*
			  Handle illegal brace ')'.
			  (1)Not matched braces before the current brace.
			  (2)A digit follows a close brace ')', lack of operator. 
			  (3)A open brace '(' follows a close brace ')' without operator between them.  
			*/
			else if(infixExpression[index] == ')'){
				braceNum--;
				if(index == 0 || previous(infixExpression, index) == ' ' || braceNum < 0){
					printError(infixExpression, index);
					printf("<Error! No matched \'(\' before \')\'>\n");
					return FAILED;
				}
				else if(next(infixExpression, index) == '('){
					printError(infixExpression, index);
					printf("<Error! No operator between \')\' and \'(\'>\n");
					return FAILED;
				}
				else if(index != 0 && isdigit(next(infixExpression, index))){
					printError(infixExpression, index);
					printf("<Error! No operator between \')\' and operand>\n");
					return FAILED;					
				}
			}
			/*
			  Handle illegal brace '('.
			  (1)There is a ')' before a '(' without operator between them.
			  (2)There is a digit before a '(' without operator between them.
			*/
			else if(infixExpression[index] == '('){  
				braceNum++;
				if(index != 0 && isdigit(previous(infixExpression, index))){
					printError(infixExpression, index);
					printf("<Error! No operator between operand and \'(\'>\n");
					return FAILED;					
				}
				else if(next(infixExpression, index) == ')'){
						printError(infixExpression, index);
						printf("<Error! No expression in the braces>\n");
						return FAILED;		
				}		
			}
			/*
			  Handle illegal '*' and '/'
			  (1)No opreands on both sizes of '*' or '/'.
			  (2)No opreands before operator '*' or '/'.
			  (3)No opreands after operator '*' or '/'.
			  (4)An operator '*','/','+' or '-' follows operator '*' or '/'.
			*/
			else if(infixExpression[index] == '*' || infixExpression[index] == '/'){
				if(previous(infixExpression, index) != ')' && !isdigit(previous(infixExpression, index)) && (next(infixExpression, index) == '\0' || next(infixExpression, index) == ')')){
					printError(infixExpression, index);
					printf("<Error! Operator \'%c\' without operands in the expression>\n", infixExpression[index]);
					return FAILED;
				}
				else if(next(infixExpression, index) == '+' || next(infixExpression, index) == '-' || next(infixExpression, index) == '*' || next(infixExpression, index) == '/'){
					printError(infixExpression, index);
					printf("<Error! Operator \'%c\'  follows another operator \'%c\' in the expression>\n", next(infixExpression, index), infixExpression[index]);
					return FAILED;
				}
				else if(index == 0 || (previous(infixExpression, index) != ')' && !isdigit(previous(infixExpression, index)) && (isdigit(next(infixExpression,index)) || next(infixExpression,index) == '('))){
					printError(infixExpression, index);
					printf("<Error! No operand before operator \'%c\'>\n", infixExpression[index]);
					return FAILED;				
				}
				else if(infixExpression[index + 1] == '\0' || next(infixExpression, index) == '\0' || next(infixExpression, index) == ')'){
					printError(infixExpression, index);
					printf("<Error! No operand after operator \'%c\'>\n", infixExpression[index]);
					return FAILED;
				}
			}
			//If the char stack is empty
			if(StackEmpty(s)){
				/*
				  If the current operator '+' or '-' is a unary operator, the put character '@' and '$' into stack respectively.
 				*/
				if((infixExpression[index] == '+' || infixExpression[index] == '-') && !isdigit(previous(infixExpression, index)) && previous(infixExpression, index) != ')'){    
					if(!Push(s, infixExpression[index] == '+'? '@':'$')){
						printf("<Error! The stack is full>\n");
						DestroyStack(s);
						return FAILED;
					}				
				}
				/*				  
				  Handle illegal braces '(' and ')'. 
				*/
				else{
					if (infixExpression[index] == '('){
						leftBrace++;
					}
					else if(infixExpression[index] == ')'){
						printError(infixExpression, index);
						printf("<Error! No matched \'(\' before \')\'>\n");
						return FAILED;
					}
					if(!Push(s, infixExpression[index])){
						printf("<Error! The stack is full>\n");
						DestroyStack(s);
						return FAILED;
					}					
				}
			}
			//If the char stack is not empty, and the current character is '(', then push it into the char stack.
			else if (infixExpression[index] == '('){  
				if(!Push(s, infixExpression[index])){
					printf("<Error! The stack is full>\n");
					DestroyStack(s);
					return FAILED;
				}
				leftBrace++;
			}	
			/*
			  If the char stack is not empty and the current character is ')', '+', '-', '*', '/',	
			  (1)If the current character is ')', then pop operators from the char stack to the postfix expression until meeting the open brace '('.
			  (2)If the current character is '+', '-', '*', '/',
			  		(a)If the current character is prior to the top value of the char stack, then push it into the char stack,
			  		(B)else pop the top value in the stack to the postfix expression, repeat (2). 
			*/
			else{ 
				if (infixExpression[index] == ')'){   
					rightBrace++;
					GetTop(s, &e);
       				while (e != '('){
						if(!Pop(s, &postfixExpression[numIndex++])){
							printf("<Error! The stack is empty>\n");
							return FAILED;
						}
						GetTop(s, &e);
					}
					if(!Pop(s, &e)){  
						printf("<Error! The stack is empty>\n");
						return FAILED;
					}
				}
				else{                          
					GetTop(s, &e);  			
					if (Priority(infixExpression[index]) > Priority(e)){
						if (infixExpression[index] == '+' || infixExpression[index] == '-'){
							if (previous(infixExpression, index) == '(' && (infixExpression[index] == '+' || infixExpression[index] == '-') 
								&&(isdigit(infixExpression[index + 1])||infixExpression[index + 1] == '(')){   
								if(!Push(s, infixExpression[index] == '+'? '@':'$')){
									printf("<Error! The stack is full>\n");
									DestroyStack(s);
									return FAILED;
								}
							}
							else{   
								if(!Push(s, infixExpression[index])){
									printf("<Error! The stack is full>\n");
									DestroyStack(s);
									return FAILED;
								}
							}
						}
						else{   
							if(!Push(s, infixExpression[index])){
								printf("<Error! The stack is full>\n");
								DestroyStack(s);
								return FAILED;
							}
						}
					}
					else if (Priority(infixExpression[index]) <= Priority(e)){  		
						while(Priority(infixExpression[index]) <= Priority(e)){
							if(!Pop(s, &postfixExpression[numIndex++])){
								printf("<Error! The stack is empty!!!>\n");
								return FAILED;
							}
							if(GetTop(s, &e) == 0)
							{
								break;
							}
						}
						if(!Push(s, infixExpression[index])){
							printf("<Error! The stack is full>\n");
							DestroyStack(s);
							return FAILED;
						}						
						index++;
						continue;   
					}
				}				
			}
		}
	 index++;
	}
	//Move the rest characters in the char stack to the postfix expression.
	while (!StackEmpty(s)){    
		if(!Pop(s, &postfixExpression[numIndex++])){
			printf("<Error! The stack is empty>\n");
			return FAILED;
		}
	}
	//DestroyStack the char stack.
	DestroyStack(s);
	if(leftBrace != rightBrace){
		if(leftBrace < rightBrace){
			printError(infixExpression, index - 1);
			printf("<Error! No matched \'(\' before \')\'>\n");
		}
		else{
			printError(infixExpression, index - 1);
			printf("<Error! No matched \')\' after \'(\'>\n");
		}
		return FAILED;
	}
	//Check if the input is empty.
	if(blank == index){
		printf("<Error! The input is EMPTY>\n");
		return FAILED; 
	}
	else return SUCCEEDED;
}

/*Compute the value of postfix expression.
  Traverse the postfix expression, if it's an operand, push it into a double stack. 
  	If it's a binary operator, pop two operands from the double stack, and calculate them using the operator, then push it back to the double stack.
  	If it's a unary operator, pop one operand from the double stack, and calculate it using the operator, then push it back to the double stack.
  when traversing is over, pop the result from the stack to the value.
*/
int computeValueFromPostfix(char* postfixExpression, double *value){ 
	int index = 0;
	SequentialStackDouble* Is = (SequentialStackDouble*)malloc(sizeof(SequentialStackDouble));
	if(InitStackDouble(Is) == FAILED){
		printf("<Error! Initial stack fail>\n");
		return FAILED;
	}
	while(postfixExpression[index] != '\0'){
		//If the current character is digit, push it into a double stack.
		if(isdigit(postfixExpression[index])){ 
			int temp = index + 1;
			double tempValue = (double)(postfixExpression[index] - '0');;
			while(postfixExpression[temp] != '#'){
				tempValue = 10.0 *tempValue + (postfixExpression[temp] - '0');
				temp++;
				index++;
			}
			if(PushDouble(Is, tempValue) == FAILED){
				printf("<Error! The stack is full>\n");
				DestroyStackDouble(Is);
				return FAILED;
			}
			index++;
			continue;
		}
		//If the current character is a space, then skip it.
		else if(postfixExpression[index] == '#'){ 
			index++;
			continue;
		}
		/*
		  If the current character is operator '+', '-', '*', '/', fetch two operands from the stack to calculate them using the current operator, 
		  then put it back to the stack.
		*/
		else if(postfixExpression[index] == '+' || postfixExpression[index] == '-' || postfixExpression[index] == '*'|| postfixExpression[index] == '/'){   //否则为操作符
			double num1 = 0.0, num2 = 0.0;
			if(PopDouble(Is, &num1) == FAILED){
				printf("<Error! The stack is empty>\n");
				return FAILED;
			}
			if(PopDouble(Is, &num2) == FAILED){
				printError(postfixExpression, index);
				printf("<Error! No  operand after Operator \'%c\'>\n", postfixExpression[index]);
				return FAILED;
			}
			switch(postfixExpression[index]){
				case ('+'): if(PushDouble(Is, num2 + num1) == FAILED){printf("<Error! The stack is full>\n"); return FAILED;}break;
				case ('-'): if(PushDouble(Is, num2 - num1) == FAILED){printf("<Error! The stack is full>\n"); return FAILED;}break;
				case ('*'): if(PushDouble(Is, num2 * num1) == FAILED){printf("<Error! The stack is full>\n"); return FAILED;}break;
				case ('/'): if(num1 != 0) {
								if(PushDouble(Is, (double)num2 / num1) == FAILED){
									printf("<Error! The stack is full>\n"); 
									return FAILED;
								} 
								break;
						    }
						    else{
						    	printError(postfixExpression, index);
						    	printf("<Error! Some operand is divided by zero in the expression>\n");
						    	return FAILED;
						    }
				default:break; 
			}
		}
		//If the current character is '@' or '$', fetch one operand from the stack to calculate, then put the result back to stack. 
		else if(postfixExpression[index] == '@' || postfixExpression[index] == '$'){
			double num1 = 0.0;
			if(PopDouble(Is, &num1) == FAILED){
				printf("<Error! The stack is empty>\n");
				return FAILED;
			}
			switch(postfixExpression[index]){
				case ('@'): if(PushDouble(Is, num1) == FAILED){printf("<Error! The stack is full>\n"); return FAILED;}break;
				case ('$'): if(PushDouble(Is, 0-num1) == FAILED){printf("<Error! The stack is full>\n"); return FAILED;}break;
				default:break;
			}
		}
		index++;
	}
	//Clear postfix expression.
	for (int i = 0; i < 100; i++)
		postfixExpression[i] = '\0';
	*value = 0.0;
	//Get the result from the stack to give it to value. 
	if(PopDouble(Is, value) == FAILED){
		printf("<Error! The stack is empty>\n");
		return FAILED;
	}
	DestroyStackDouble(Is);
	return SUCCEEDED;
}

//Calculate the priority value of operators.
int Priority(char c){               
	switch (c){
	case '(': return 0;
	case '+': return 1;
	case '-': return 1;
	case '*': return 2;
	case '/': return 2;
	case '@': return 3;
	case '$': return 3;
	default:  return 0;
	}
}

//Get the first non_space character before the current character.
char previous(char* infixExpression, int index){       
	int i= index;               
	while(i > 0 && infixExpression[--i] == ' ' );
    return infixExpression[i];                
}

//Get the first non_space character after the current character.
char next(char* infixExpression, int index){                           
	int i= index;
	while(infixExpression[++i] == ' ' && infixExpression[i] != '\0');
	return infixExpression[i];                
}
    
//Mark the location of error.
void printError(char* infixExpression, int index){
	printf("\"");
	for(int i = 0; i < index; i++)
        printf("%c", infixExpression[i]);
    printf("\e[40;37m%c\e[0m", infixExpression[index]);
    while(infixExpression[++index] != '\0')
        printf("%c",infixExpression[index]);
    printf("\"\n");
}
