#include<stdlib.h> 
#include<stdio.h>
#include<string.h>
#define MAX 1048
#define TRUE 1
#define ERROR 0

typedef int status;
//��ʼ���ַ��� 
status InitData(char **S,char **T){
    char ch;
    int i = 0;
    (*S) = (char *)malloc(sizeof(char) * MAX);//���䴢��λ�� 
    (*T) = (char *)malloc(sizeof(char) * MAX);

    if((*S)==NULL || (*T) ==NULL){
        printf("��ʼ������...");
        return ERROR;
    }
    //�����ַ���
    printf("�������ַ�������#����\n");
    while((ch = getchar())!='#'){
        (*S)[i++] = ch;
        (*S)[i] = '\0';
    }
    getchar();  //����������س���
    i = 0;  //����
    printf("�����������ʣ���#����\n");
    while((ch = getchar()) !='#'){
        (*T)[i++] = ch;
        (*T)[i]='\0';
    }
}

//ӦSunday�㷨��Ҫ����Ҫ�����ַ����в����ض��ַ� 
int Findindex(char *T,char temp)
{
	int i = 0;
	if(T == NULL){
        printf("������Ϊ��...");
        exit (-1); //�쳣�˳�
    }
	for(i=strlen(T)-1;i>=0;i--)	
	{
		if(T[i] == temp)
		return i;
	}
	return 0;
}

//Sunday���㷨 
status Sunday(char *S, char *T)
{
	int slen=strlen(S),tlen=strlen(T);
	int i=0,j=0; 
	int temp=0,index=-1;
	

	while(i<slen&&j<tlen)
	{
		if(S[i] == T[j])
		{
			if(j=tlen-1)//ȷ�����ַ���ƥ������ 
			{
				printf("Match succeed��");
                return TRUE;//ƥ��ɹ� 
			}
		i++;j++;
		}
		else
		{
			temp=tlen-j+i;//���ַ�����ƥ���ַ��ľ�λ�� 
			index=Findindex(T,S[temp]);//�����ַ����в��Ҹ�ƥ���ַ���λ�� 
			if(index==-1)//���ַ�����δ�ҵ� 
			{
				i=index+1;//iָ����һ�� 
				j=0;//jָ�����ַ��������� 
			}
			else
			{
				i=temp-index;//���ӷ������ҵ� ���ó����� 
				j=0;// jָ�����ַ��������� 
			}
		}
	}
	printf("Match failed��"); 
	return ERROR;//ƥ��ʧ�� 
 }
 
void main()
 {
   char *S,*T;


   InitData(&S,&T);
   Sunday(S,T)pat 
