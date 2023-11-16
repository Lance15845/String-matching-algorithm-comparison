# include<stdio.h> 
# include<string.h>
# include<time.h>
 
/*
  @pat ģʽ��
  @text �ı��� 
  @next ״̬ת������ 
*/ 
int KMP(char * text, char *pat, int next[])
/* ��ʼ������״̬ת������next���ı�����ģʽ���Ѵ���
   �������������next������ı�������ģʽ��ƥ��
    ��ƥ��ɹ����򷵻ش��ı����ĵڼ���λ�ý���ƥ��
	��ƥ��ʧ�ܣ��򷵻�-1 
*/ 
{
	// ָ���ı����±� 
	int i = 0;
	// ָ��ģʽ���±� 
	int j = 0;
	// �ı����ĳ��� 
	int textLength = strlen(text);
	// ģʽ���ĳ��� 
	int patLength =  strlen(pat);
//	int c = 0;
//	for(;c < strlen(text); c++ )
//		printf("%c\n",text[c]);
//	for(c = 0; c < strlen(pat); c++ )
//		printf("%c\n",pat[c]);
		
	// ��ʼƥ�� 
	while (i < textLength && j < patLength)
	{
		// ƥ��ɹ�����jΪ-1 
		if ( j == -1 || text[i] == pat[j])
		{
			i++;
			j++;
		}
		// ʧ�� 
		else
		{
			j = next[j];
		}
	}
//	printf("%d %d\n",i,j);
//	printf("%d %d\n",strlen(text),strlen(pat));
	
	if ( j == strlen(pat))
	{
		return i -j;
	}
	else
	{
		return -1;
	}
}

void getNext(char * pat, int *next)
/* ��ʼ������״̬ת������next��ģʽ���Ѵ���
   �������������ģʽ������next���� 
*/  
{
	// ��ʼ�� 
	next[0] = -1;
	// ָ���ı����±� 
	int i = 0;
	// ָ��ģʽ���±� 
	int j = -1;
	
	// ����next���� 
	while(i < strlen(pat))
	{
		// ƥ��ɹ� 
		if (j == -1 || pat[i] == pat[j] )
		{
			j++;
			i++;
			next[i] = j; 
		}
		// ʧ�� 
		else
		{
			j = next[j];
		}
	}

	//next�����Ż� 
	for(i = 1; pat[i]; i++) {
        j = next[i];
        while(j && (pat[j] == pat[i])) {
            j = next[j];
        }
        next[i] = j;
    }

}


int main(){
//	char text[] = "ababababca";
//	char pat[] = "abababca";
	clock_t start, finish;
	double Total_time; 
	
	char text[] = "aaaaaaabbaaa";
	char pat[] = "aaa";
//	char text[] = "here is a simple example";
//	char pat[] = "example";
	int next[strlen(pat)];

	start = clock();
	
	getNext(pat, next);


	// ����next���� 
	int i ;
	for(i = 0; i < strlen(pat); i++)
	{
		printf("%d\n",next[i]);
	}
	
	int result = KMP(text, pat, next);
	
	finish = clock(); 
    Total_time = (double)(finish-start) / CLOCKS_PER_SEC; 
  

	if (result == -1)
	{
		printf("ƥ��ʧ��!"); 
	}
	else
	{
		
		printf("ƥ��ɹ�! ���ı����ĵ�%d��λ�ÿ�ʼƥ�䣡\n", result); 
	}
	printf( "%f seconds/n", Total_time); 
	
	return 0;
}
