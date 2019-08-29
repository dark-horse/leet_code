/*
 *
 * https://leetcode.com/problems/paint-fence/
 * There is a fence with n posts, each post can be painted with one of the k colors.
 * You have to paint all the posts such that no more than two adjacent fence posts have the same color.
 * Return the total number of ways you can paint the fence.
 * Note: n and k are non-negative integers.
 * Example:
 * Input: n = 3, k = 2 Output: 6
 * Explanation: Take c1 as color 1, c2 as color 2. All possible ways are:

 *             post1  post2  post3      
 *  -----      -----  -----  -----       
 *    1         c1     c1     c2 
 *    2         c1     c2     c1 
 *    3         c1     c2     c2 
 *    4         c2     c1     c1  
 *    5         c2     c1     c2
 *    6         c2     c2     c1
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>


/* recursive function */
int f(int n, int k)
{
    if (n==1) return 1;
    if (n==2) return k;
    if (n==3) return (k-1)*(k+1);
    int C_n_2 = k, C_n_1 = (k-1)*(k+1), C_n;
    int a_n_2 = 1;
    for (int i = 4; i <=n;i++)
    {
        int a_n_1 = C_n_2 - a_n_2;
        C_n = C_n_1 * k - a_n_1;
        C_n_2 = C_n_1;
        C_n_1 = C_n;
        a_n_2 = a_n_1;
    }
    return C_n;
}

int numWays(int n, int k){
    if (n==0) return 0;
    int res = f(n,k);
    res = res * k;
    return res;

}



int main()
{
	
	printf("result for n = 5, k = 2 is %d.\n", numWays(5,2));

	return 0;
}
