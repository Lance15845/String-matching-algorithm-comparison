
#include <stdio.h>
#include <stdlib.h>
#define MAXCHAR 256
 
/*参数说明
*********************
T:要查找的字符串
P:模式字符串
*********************
*/
void pre_process(char *patt, int m, int bm_bc[]){
	int k = 0;
	for ( k = 0; k < MAXCHAR; k++ ){
		bm_bc[k] = m;
	}
	//最后一次字符的值不需要计算，保留默认值m，或者使用0 ~ （m-1）内计算到的值
}
 
int BMH(char *src, int n, char *des, int m){
	int bm_bc[MAXCHAR] = {0};
	int j = 0, k = 0, i = 0;
 
	if ( m > n)
		return -1;
 
	pre_process(des, m, bm_bc);
	//k 指src查找递增的过程；i指向src的当前比较位置；j指向匹配子串的位置
	k = m -1;
	while ( k < n ){
		j = m -1;
		i = k;
		while ( j >=0 && src[i] == des[j] ){
			j--;
			i--;
		}
		if ( j == -1)
			return i+1;
		k += bm_bc[src[k]];
 
	}
	return -1;
}
 
int main(){
	char T[]="GCCTCATCCUACG TTAC";
	char P[]="G TTAC";
	//需要向BMS传递的是两个子串和子串的长度，因为上述初始化时是使用字符串的初始化，所以sizeof会计算最后一个\0，所以在传参数时要-1
	printf("P find in T:%d \n", BMH(T, sizeof(T)-1, P, sizeof(P)-1 ));
 
}
