/*
 *
 * https://leetcode.com/problems/parsing-a-boolean-expression/
 * Return the result of evaluating a given boolean expression, represented as a string.
 * An expression can either be:
 * "t", evaluating to True;
 * "f", evaluating to False;
 * "!(expr)", evaluating to the logical NOT of the inner expression expr;
 * "&(expr1,expr2,...)", evaluating to the logical AND of 2 or more inner expressions expr1, expr2, ...;
 * "|(expr1,expr2,...)", evaluating to the logical OR of 2 or more inner expressions expr1, expr2, ...
 * Example 1: Input: expression = "!(f)" Output: true
 * Example 2: Input: expression = "|(f,t)" Output: true
 * Example 3: Input: expression = "&(t,f)" Output: false
 * Example 4: Input: expression = "|(&(t,f,t),!(t))" Output: false
 * Constraints:
 * 1 <= expression.length <= 20000
 * expression[i] consists of characters in {'(', ')', '&', '|', '!', 't', 'f', ','}.
 * expression is a valid expression representing a boolean, as given in the description.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

/* forward declarations */
bool parse_not(char **exp);
bool parse_and(char **exp);
bool parse_or(char **exp);
bool parse_expr(char **exp);

bool parse_not(char ** exp)
{
	/* should assert that **exp == '!' */
	*exp = *exp + 1;
	bool res = parse_expr(exp);
	return !res;
}

bool parse_expr(char **exp)
{
	char ch = **exp;
	switch(ch)
	{
		case '!':
			return parse_not(exp);
		case '&':
			return parse_and(exp);
		case '|':
			return parse_or(exp);
		case 't':
			*exp = *exp + 1;
			return true;
		case 'f':
			*exp = *exp + 1;
			return false;
		case '(':
			*exp = *exp + 1;
			bool res = parse_expr(exp);
			*exp = *exp + 1;
			return res;
		default:
			printf("error\n");
			return false;
	}
}

bool parse_and(char **exp)
{
	/*should assert that *exp == '&' */
	*exp =*exp +1; /*advance past '&' */
	*exp =*exp +1; /*advance past '('*/
	bool res = true;
	while (1)
	{
		bool res1 = parse_expr(exp);
		res = res & res1;
		if ((**exp) == ')')
		{
			*exp = *exp + 1;
			break;
		}
		if ((**exp) == ',')
		{
			*exp = *exp + 1;
		}
		else
		{
			printf("error\n");
			break;
		}
	}
	return res;
}

bool parse_or(char **exp)
{
	/*should assert that *exp == '|' */
	*exp =*exp +1; /*advance past '|' */
	*exp =*exp +1; /*advance past '('*/
	bool res = false;
	while (1)
	{
		bool res1 = parse_expr(exp);
		res = res | res1;
		if ((**exp) == ')')
		{
			*exp = *exp + 1;
			break;
		}
		if ((**exp) == ',')
		{
			*exp = *exp + 1;
		}
		else
		{
			printf("error\n");
			break;
		}
	}
	return res;
}

bool parseBoolExpr(char * expression)
{
	return parse_expr(&expression);
}


int main()
{
	printf("res is %s, expected true.\n", parseBoolExpr("!(f)") ? "TRUE" : "FALSE");
	printf("res is %s, expected true.\n", parseBoolExpr("|(f,t)") ? "TRUE" : "FALSE");
	printf("res is %s, expected false.\n", parseBoolExpr("&(t,f)") ? "TRUE" : "FALSE");
	printf("res is %s, expected false.\n", parseBoolExpr("|(&(t,f,t),!(t))") ? "TRUE" : "FALSE");
	return 0;
}
