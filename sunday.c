#include<stdlib.h> 
#include<stdio.h>
#include<string.h>
#define MAX 1048
#define TRUE 1
#define ERROR 0

typedef int status;
//初始化字符串 
status InitData(char **S,char **T){
    char ch;
    int i = 0;
    (*S) = (char *)malloc(sizeof(char) * MAX);//分配储存位置 
    (*T) = (char *)malloc(sizeof(char) * MAX);

    if((*S)==NULL || (*T) ==NULL){
        printf("初始化错误...");
        return ERROR;
    }
    //输入字符串
    printf("请输入字符串，以#结束\n");
    while((ch = getchar())!='#'){
        (*S)[i++] = ch;
        (*S)[i] = '\0';
    }
    getchar();  //清除缓冲区回车键
    i = 0;  //重置
    printf("请输入搜索词，以#结束\n");
    while((ch = getchar()) !='#'){
        (*T)[i++] = ch;
        (*T)[i]='\0';
    }
}

//应Sunday算法需要，需要在子字符串中查找特定字符 
int Findindex(char *T,char temp)
{
	int i = 0;
	if(T == NULL){
        printf("搜索词为空...");
        exit (-1); //异常退出
    }
	for(i=strlen(T)-1;i>=0;i--)	
	{
		if(T[i] == temp)
		return i;
	}
	return 0;
}

//Sunday主算法 
status Sunday(char *S, char *T)
{
	int slen=strlen(S),tlen=strlen(T);
	int i=0,j=0; 
	int temp=0,index=-1;
	

	while(i<slen&&j<tlen)
	{
		if(S[i] == T[j])
		{
			if(j=tlen-1)//确定子字符串匹配完整 
			{
				printf("Match succeed！");
                return TRUE;//匹配成功 
			}
		i++;j++;
		}
		else
		{
			temp=tlen-j+i;//主字符串中匹配字符的距位置 
			index=Findindex(T,S[temp]);//在子字符串中查找该匹配字符的位置 
			if(index==-1)//主字符串中未找到 
			{
				i=index+1;//i指向下一项 
				j=0;//j指向子字符串的首项 
			}
			else
			{
				i=temp-index;//主子符串中找到 ，得出距离 
				j=0;// j指向子字符串的首项 
			}
		}
	}
	printf("Match failed！"); 
	return ERROR;//匹配失败 
 }
 
void main()
 {
   char *S,*T;


   InitData(&S,&T);
   Sunday(S,T)pat 
