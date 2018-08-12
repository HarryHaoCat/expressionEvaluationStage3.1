
#include <stdio.h>
#include <stdlib.h>
#include "expressionEvaluation.h"
#define ExpressionLen  15 
#define improperTestNumbers 100
#define infixLength 100

int main(){
	char testChar[35] = {'+', ' ', '-', ' ', '*', '/',' ', '(', ')', ' ','+', ' ', '-', ' ', '*', '/',' ', '(', ')', ' ','0', '1',' ', '2', ' ', '3', '4', ' ', '5', '6', ' ', '7', '8', ' ',  '9'};
	char testExpression[improperTestNumbers][ExpressionLen] = {};
	srand(10);
	for(int i = 0; i < improperTestNumbers; i++){
		for(int j = 0; j < ExpressionLen; j++){
			testExpression[i][j] = testChar[rand() % 35];
		}
		//printf("%s", testExpression[i]);
		char postfixExpression[infixLength];
        double value;
		printf("---------------------***   Test %d    ***------------------------\n\n", i + 1);
        printf("The infix expression:%s\n", testExpression[i]);
        if (infixToPostfix(testExpression[i], postfixExpression) == 1){
            printf("The postfix expression:%s\n", postfixExpression);
            if (computeValueFromPostfix(postfixExpression, &value) == 1)
                printf("The value of the expression:%g\n\n", value);
            else
                printf("Sorry, we can't evaluate such a postfix expression.\n");
        }
        else{
            printf("Sorry, we can't turn such an infix expression to a postfix expression.\n");
        }
        printf("----------------------------------------------------------------\n\n");
		printf("\n");
	}   
    printf("-----***   End of tests for IMPROPER prefix expressions.    ***-----\n\n\n");
	return 0;
}
