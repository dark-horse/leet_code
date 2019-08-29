/*
 *
 * https://leetcode.com/problems/multiply-strings/
 * Example 1:
 * Input: num1 = "2", num2 = "3" Output: "6"
 * Example 2:
 * Input: num1 = "123", num2 = "456" Output: "56088"
 * Note:
 * The length of both num1 and num2 is < 110.
 * Both num1 and num2 contain only digits 0-9.
 * Both num1 and num2 do not contain any leading zero, except the number 0 itself.
 * You must not use any built-in BigInteger library or convert the inputs to integer directly.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


/* num1 and num2 are reverse copies of original string */
/* for example, number 123 will show as "321" */
void multiply_by_2(char * num1, int num_len, char * res)
{
	int carry_over = 0, res_index = 0;
	for (int i = 0; i < num_len; i ++)
	{
		int digit = (int) (num1[i]-'0');
		digit = digit + carry_over;
		carry_over = digit / 10;
		digit = digit % 10;
		res[res_index] = (char) (digit + (int)'0');
		res_index ++;
	}
	res_index ++;
	res[res_index] = (char) (carry_over + (int)'0');
}

/* num1 and num2 are reverse copies of original string */
/* for example, number 123 will show as "321" */
void add(char * num1, int num1_len, char * num2, int num2_len, char * res)
{
	int max_num_len, min_num_len;
	char * max_num;
	if (num1_len > num2_len)
	{
		max_num_len = num1_len;
		min_num_len = num2_len;
		max_num = num1;
	}
	else
	{
		max_num_len = num2_len;
		min_num_len = num1_len;
		max_num = num2;
	}
	int carry_over = 0, res_index = 0;
	for (int i = 0; i < min_num_len; i++)
	{
		int digit1 = (int) (num1[i] - '0');
		int digit2 = (int) (num2[i] - '0');
		int digit = digit1 + digit2 + carry_over;
		carry_over = digit / 10;
		digit = digit % 10;
		res[res_index] = (char) (digit + (int)'0');
		res_index ++;
	}
	for (int i = min_num_len; i < max_num_len; i ++)
	{
		int digit = (int) (max_num[i]-'0');
		digit += carry_over;
		carry_over = digit / 10;
		digit = digit % 10;
		res[res_index] = (char) (digit + (int)'0');
		res_index ++;
	}
	if (carry_over)
	{
		res[res_index] = (char) (carry_over + (int)'0');
	}
}

/* assume multiplier is greater or equal than 1, and smaller or equal than 9 */
void multiply_by_1_digit(char * num1, int num1_len, char * res, int multiplier)
{
	if (multiplier == 0)
	{
		memcpy(res /*dest*/, num1 /*src*/, (num1_len+1)*sizeof(char));
		return;
	}
	int carry_over = 0, res_index = 0;
	for (int i = 0; i < num1_len; i ++)
	{
		int digit = (int) (num1[i] - '0');
		digit = digit * multiplier + carry_over;
		carry_over = digit / 10;
		digit = digit % 10;
		res[res_index] = (char) (digit + (int)('0'));
		res_index ++;
	}
	if (carry_over) res[res_index] = (char) (carry_over + (int)'0');
}

void reverse_string(char * s, int s_len)
{
	int i = 0, j = s_len-1;
	while (i < j)
	{
		char tmp = s[i];
		s[i] = s[j];
		s[j] = tmp;
		i++;
		j--;
	}
}


char * multiply(char * num1, char * num2)
{
	if (!num1 || !num2) return "";
	if ((*num1=='0')|| (*num2=='0')) return "0";
	int num1_len = strlen(num1), num2_len = strlen(num2);
	reverse_string(num1, num1_len);
	reverse_string(num2, num2_len);
	char * res = (char *) malloc((num1_len+num2_len+1)*sizeof(char));
	char * helper1= (char *) malloc((num1_len+num2_len+1)*sizeof(char));
	char * helper2= (char *) malloc((num1_len+num2_len+1)*sizeof(char));
	memset(res, 0, (num1_len + num2_len+1)*sizeof(char));
	memset(helper1, 0, (num1_len + num2_len+1)*sizeof(char));
	memset(helper2, 0, (num1_len + num2_len+1)*sizeof(char));

	for (int i = 0; i < num1_len; i ++)
	{
		int digit = (int) (num1[i] - '0');
		if (!digit)
		{
			if(i>0) helper2[i-1] = '0';
			continue;	/* nothing to do when we multiply with 0 */
		}
		memcpy(helper2 + i, num2, num2_len*sizeof(char));
		if(i>0) helper2[i-1] = '0';
		multiply_by_1_digit(helper2, num2_len + i, helper1, digit);
		add(res, strlen(res), helper1, strlen(helper1), res);
	}

	
	reverse_string(res, strlen(res));
	free(helper1);
	free(helper2);
	return res;
}



int main()
{
	char res[]="\0\0\0\0\0\0\0\0";
	char a[] = "408";
	char b[] ="5";
	reverse_string(a,3);
	reverse_string(b,2);
	add(a,3,b,2,res);
	reverse_string(res, strlen(res));
	printf("%s\n",res);
	reverse_string(a,3);
	reverse_string(b,2);
	char * mult = multiply(a,b);
	printf("multiplication: %s.\n", mult);
	free(mult);
	return 0;
}
