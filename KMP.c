# include<stdio.h> 
# include<string.h>
# include<time.h>
 
/*
  @pat 模式串
  @text 文本串 
  @next 状态转移数组 
*/ 
int KMP(char * text, char *pat, int next[])
/* 初始条件：状态转移数组next，文本串，模式串已存在
   操作结果：利用next数组对文本串进行模式串匹配
    若匹配成功，则返回从文本串的第几个位置进行匹配
	若匹配失败，则返回-1 
*/ 
{
	// 指向文本串下标 
	int i = 0;
	// 指向模式串下标 
	int j = 0;
	// 文本串的长度 
	int textLength = strlen(text);
	// 模式串的长度 
	int patLength =  strlen(pat);
//	int c = 0;
//	for(;c < strlen(text); c++ )
//		printf("%c\n",text[c]);
//	for(c = 0; c < strlen(pat); c++ )
//		printf("%c\n",pat[c]);
		
	// 开始匹配 
	while (i < textLength && j < patLength)
	{
		// 匹配成功或者j为-1 
		if ( j == -1 || text[i] == pat[j])
		{
			i++;
			j++;
		}
		// 失配 
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
/* 初始条件：状态转移数组next，模式串已存在
   操作结果：根据模式串构造next数组 
*/  
{
	// 初始化 
	next[0] = -1;
	// 指向文本串下标 
	int i = 0;
	// 指向模式串下标 
	int j = -1;
	
	// 构造next数组 
	while(i < strlen(pat))
	{
		// 匹配成功 
		if (j == -1 || pat[i] == pat[j] )
		{
			j++;
			i++;
			next[i] = j; 
		}
		// 失配 
		else
		{
			j = next[j];
		}
	}

	//next数组优化 
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


	// 遍历next数组 
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
		printf("匹配失败!"); 
	}
	else
	{
		
		printf("匹配成功! 从文本串的第%d个位置开始匹配！\n", result); 
	}
	printf( "%f seconds/n", Total_time); 
	
	return 0;
}
