
#include <stdio.h>
#include <stdlib.h>
#define MAXCHAR 256
 
/*����˵��
*********************
T:Ҫ���ҵ��ַ���
P:ģʽ�ַ���
*********************
*/
void pre_process(char *patt, int m, int bm_bc[]){
	int k = 0;
	for ( k = 0; k < MAXCHAR; k++ ){
		bm_bc[k] = m;
	}
	//���һ���ַ���ֵ����Ҫ���㣬����Ĭ��ֵm������ʹ��0 ~ ��m-1���ڼ��㵽��ֵ
}
 
int BMH(char *src, int n, char *des, int m){
	int bm_bc[MAXCHAR] = {0};
	int j = 0, k = 0, i = 0;
 
	if ( m > n)
		return -1;
 
	pre_process(des, m, bm_bc);
	//k ָsrc���ҵ����Ĺ��̣�iָ��src�ĵ�ǰ�Ƚ�λ�ã�jָ��ƥ���Ӵ���λ��
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
	//��Ҫ��BMS���ݵ��������Ӵ����Ӵ��ĳ��ȣ���Ϊ������ʼ��ʱ��ʹ���ַ����ĳ�ʼ��������sizeof��������һ��\0�������ڴ�����ʱҪ-1
	printf("P find in T:%d \n", BMH(T, sizeof(T)-1, P, sizeof(P)-1 ));
 
}
