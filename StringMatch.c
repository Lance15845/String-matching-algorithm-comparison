# include<stdio.h> 
# include <stdlib.h>
# include<string.h>
# include<time.h>


/*
  朴素匹配算法 
  @T 模式串
  @S 文本串 
*/ 
void BF(char *S, char *T) 
{
	int i = 0;
	int j = 0;
	int slen=strlen(S);//长字符串S的长度 
	int tlen=strlen(T);//子字符串T的长度 
	
	while(i < slen && j < tlen)//大于子字符串长度跳出循环 
	{
		if(S[i] == T[j])//匹配成功 
		{
			i++;
			j++;
		}
		else
		{
			i = i - j + 1; //长字符串回到下一个位置 
			j = 0;//返回子字符串首位 
		} 
	}
	if(j = tlen)//子字符串判满 
		printf("朴素匹配算法:\t匹配成功! 从文本串的第%d个位置开始匹配！\n", i-j); 
	else
		printf("匹配失败!"); 
} 

/*参数说明
*********************
T:要查找的字符串
P:模式字符串
*********************
*/
const int seed = 31; 
int hash(char s[], int len) //求出P和T各个子串的哈希值
{
	int hash = 0;
	int i ;
	for (i = 0; i < len; i++)
	{
		hash = seed * hash + s[i];
	}
	return hash;
}

int num(int m) //计算seed的n次方
{
	int number = 1;
	int i;
	for ( i = 0; i < m; i++)
	{
		number *= seed;
	}
	return number;
}

long long* hash2(char s1[], char s2[], int m, int n) //哈希滚动
{
	long long* hash_s2 = (long long*)malloc(sizeof(long long)*(n - m + 1)); //动态内存分配
	hash_s2[0] = hash(s2, m);
	int i;
	for (i = m; i < n; i++)
	{
		char news = s2[i];
		char old = s2[i - m];
		//前n个字符的哈希*seed-前n字符的第一个字符*seed的n次方再+新字符
		int v = (hash_s2[i - m] * seed) - (num(m)*old) + news;
		hash_s2[i - m + 1] = v;
	}
	return hash_s2;
}

/*
  RK算法匹配 
  @s1 文本串 
  @s2 模式串
  @m  文本串长度 
  @n 模式串长度 
*/ 
void match(char s1[], char s2[], int m, int n)
{
	long long hash_s1 = hash(s1, m);
	long long* hash_s2 = hash2(s1, s2, m, n);
	int q = 1; //控制
	int i, j;
	for (i = 0; i < n - m + 1; i++)
	{
		if (hash_s2[i] == hash_s1)
		{
			for (j = i; j < i + m; j++) //哈希有极小概率发生冲突100000个大概冲突在0~3之间
			{
				if (s1[j - i] != s2[j])
				{
					q = 0;
				}
			}
			if (q)
			{
				printf("RK算法: \t匹配成功! 从文本串的第%d个位置开始匹配！\n", i++); //输出开头下标
			}
		}
	}
	free(hash_s2);
}


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
	
	// j的值等于模式串长度即代表匹配成功 
	if ( j == strlen(pat))
	{
		printf("KMP算法: \t匹配成功! 从文本串的第%d个位置开始匹配！\n", i - j); 
	}
	// 匹配失败 
	else
	{
		printf("匹配失败!\n"); 
	}
}

/*
  @pat 模式串
  @next 状态转移数组 
*/ 
void getNext(char * pat, int *next)
/* 初始条件：状态转移数组next，模式串已存在
   操作结果：根据模式串构造next数组 
*/  
{
	// next数组初始化 
	next[0] = -1;
	// 指向文本串下标 
	int i = 0;
	// 指向模式串下标 
	int j = -1;
	
	// 构造next数组 
	while(i < strlen(pat))
	{
		// 匹配成功 或 j = -1 
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
	//防止模式串有连续多个不匹配的字符 
	for(i = 1; pat[i]; i++) {
        j = next[i];
        while(j && (pat[j] == pat[i])) {
            j = next[j];
        }
        next[i] = j;
    }
   
}

 

int main()
{
	// 定义CPU时钟计时单元（clock tick）变量 
	// clolk_t 在time库中为长整型 
	clock_t start, stop;
	// 定义算法的执行时间 
	double KMP_execute_time, BF_execute_time, RK_execute_time; 
	// 文本串 共10164个字符 
	char text[] = "I watched her get on at the station in Florence. She slid open the glass door and, once inside the cay, informal manner that skidded from sullen to sprightly and assumed mine did as well. Her tone jibed with her casual clothes: scuffed hiking boots, a pair of jeans, no makeup, and a half-unbuttoned, faded, reddish lumberjack shirtworn over a black T-shirt. And yet, despite the rumpled look, she had green eyes and dark eyebrows. She knows, I thought, she knows. Probably knows why I made that silly comment about her glumness. I was surestrangers were always finding one pretext or another to start a conversation with her. Which explains that irritated don’t you even try look she projects wherever she goes.After her ironic comment about my son, I was not surprised to find our conversation lagging. Time to pick up our respective books. But then shturned to me and asked point-blank: “Are you excited about seeingyour son?” Again, I thought she was ribbing me somehow, but her tone was not flippant. There was something at once alluring and disarming in the way she got personal and cut straight through the hurdles betweenstrangers on a train. I liked it. Perhaps she wanted to know what a man almost twice her age felt before meeting his son. Or perhaps she simplydidn’t feel like reading. She was waiting for me to answer.  “So, are you happy—maybe? Nervous—maybe?”What kind of person are you when someone gets to know you? I wanted to ask. Are you funny, jovial, playful, or is there a glum, ill?tempered serum coursing in your veins that clouds your features and blots out all the laughter promised by that smile and those green eyes? I wanted to know—because I couldn’t tell. I was about to compliment her on her ability to read people so well when her phone rang. Boyfriend, of course! What else. I’d grown so used to constant cell phone interruptions, that it was no longer possible for me to meet students over coffee or talk to my colleagues or to my son even without a mobile phone call barging in. Saved by the phone, silenced by the phone, shunted by the phone. “Hi, Pa,” she said as soon as it rang. I believed she was picking up the phone right away to prevent the loud chime from disturbing other passengers. But what surprised me was how she yelled into her phone. “It’s the damned train. It stopped, I’ve no idea for how long, but should be no more than two hours. See you soon.” The father was asking her something. “Of course I did, you old goon, how could I forget.” He asked something else. “That too.” Silence. “Me too. Lots and lots. She clicked off the phone and tossed it into her backpack, as if to say: We’re not going to be interrupted again. She gave me an uneasy smile. “Parents,” she finally said, meaning The same everywhere, aren’t they?But then she explained“seehim every weekend—I’m his weekend wallah—my siblings and his caregiver take care of him weekdays.” Before giving me a chance to say another word, she asked, “So, did you prettify yourself for tonight’s event?” What a way to describe what I wore! “Do I look prettified?” I replied, bandying the word back at her in jest so she’d not think I was fishing for compliments.“Well, the pocket square, the well-pressed shirt, no tie, but then the cuff links? I’d say you gave it some thought. Old-school a bit, but dapper.”We both smiled. “Actually, I have this” I said, half removing a colorful necktie from my jacket pocket and slipping it back in. I wanted her to see that I had enough of a sense of humor to poke fun at myself“Just as I thought,” she said. “Prettified! Not like a retired professor in Sunday clothes, but almost. So, what do the two of you do in Rome?”Was she ever going to let up? Had I started something with my initial question that made her think we could be so informal? “We meet every five or six weeks. He’s been living in Rome but will soon be moving to Paris. I miss him already. I like spending the day with him; we do nothing, really, mostly walk, though it usually turns out to be the same walk: his Rome, by the conservatory, my Rome, where I used to live as a young teacher. Eventually we’ll always have lunch at Armando’s. He puts up with me or maybe he enjoys my company, I still can’t tell, maybe both, but we’ve ritualized these visits: Via Vittoria, Via Belsiana, Via del Babuino. Sometimes we wander off all the way to the Protestant Cemetery. They’re like the markers of our lives. We’ve nicknamed them our vigils after the way pious people stop at various madonnelle—street shrines—to payhomage to the Madonna of the street. Neither of us forgets: lunch, walk, vigils. I’m lucky. Walking around Rome with him is itself a vigil. Everywhere you turn you stumble on memories—your own, someone else’s, the city’s. I like Rome at twilight, he likes it afternoons, and there’ve been times when we’ll have an afternoon tea anywhere just to drag things out a bit till evening sets in and we have drinks.”“I never stay close with anyone I’ve had a relationship with. Most people don’t like to burn bridges. I seem to blow them up—probably because there wasn’t much of a bridge to start with. Sometimes I leave everything behind in their apartment and simply disappear. I hate the drawn-out process of packing up and moving out and those unavoidable postmortems that turn into teary-eyed pleas to stay together; above all I hate the lingering pretense of an attachment after we don’t even want to be touched by someone we no longer recall wanting to sleep with. You’re right: I don’t know why I start with anyone. The sheer annoyance of a new relationship. Plus the small home habits I need to put up with. The smell of his birdcage. The way he likes his CDs stacked. The sound of an ancient radiator in the middle of the night that wakes me but never him. He wants to shut the windows. I like them open. I’ll drop my clothes wherever; hewants our towels folded and put away. He likes the tube of toothpaste squeezed neatly from the bottom up; I squeeze it whatever way I can and always lose the cap, which he always finds somewhere on the floor behind the toilet bowl. The remote control has its place, the milk needs to stand close but not too close to the freezer, underwear and socks belong in thisdrawer but not that drawer.“And yet, I’m not difficult. I’m actually a good person, just a bit opinionated. But it’s only a front. I put up with everyone and everything. At least for a while. Then one day it just hits me: I don’t want to be with this guy, don’t want him near me, need to get away. I fight this feeling. But as soon as a man senses this, he’ll hound me with despairing puppy eyes. Once I spot that look, pfffff, I’m gone and immediately find someone else.“Men!” she finally said, as though that one word summed up all the shortcomings most women are willing to overlook and learn to put up withand ultimately forgive in the men they hope to love for the rest of theirlives even when they know they won’t. “I hate to see anyone hurt.”A shadow hovered over r features. I wished I could touch her face, gently. She caught the glance, I lowered my eyes. Once again, I noticed her boots. Wild, untamed boots, as though they’dbeen dragged on craggy treks and acquired an aged, weatherworn look, which meant she trusted them. She liked her things worn and broken in.She liked comfort. Her thick navy woolen socks were men’s socks, probably lifted from the drawer of the man she claimed she had no love for. But the mid-season leather biker’s jacket looked very expensive. Prada, most likely. Had she dashed out of her boyfriend’s home, and in her hurry, thrown on the first items at hand with a hasty I’ m heading out to my dad’s, call you this evening? She was wearing a man’s watch. His too? Or did she just prefer men’s watches? Everything about her suggested something gritty, rugged, unfinished. And then I caught a sliver of skin between her socks and the cuff of her jeans—she had the smoothest ankles.";
	// 模式串 
	char pat[] = "I caught a sliver of skin between her socks and the cuff of her jeans";
	// 文本串长度 
	int text_length = strlen(text);
	// 模式串长度 
	int pat_length = strlen(pat); 
	
	// 朴素算法 
	start = clock();
	BF(text,pat);
	stop = clock(); 
	// 计算朴素算法运行时间 
	// 常量CLOCKS_PER_SEC用来表示一秒钟会有多少个时钟计时单元 系统自带 
    BF_execute_time = (double)(stop - start) / CLOCKS_PER_SEC; 
  
    // Rabin-Karp算法 
    start = clock();
    match(pat, text, pat_length,text_length);
    stop = clock(); 
   // 计算朴素算法运行时间 
   RK_execute_time = (double)(stop - start) / CLOCKS_PER_SEC; 

    // KMP算法 
    // 定义next状态转移数组 
    int next[strlen(pat)];
    start = clock();
    // 构造状态转移数组 
   	getNext(pat, next);
   	KMP(text, pat, next);
    stop = clock(); 
    // 计算朴素算法运行时间 
   KMP_execute_time = (double)(stop - start) / CLOCKS_PER_SEC; 

	printf("\n") ;
   // 算法运行时间对比 
   	printf( "朴素匹配算法用时：%lf seconds\n", BF_execute_time); 
	printf( "Rabin-Karp算法用时：%lf seconds\n", RK_execute_time); 
	printf( "KMP算法用时：%lf seconds\n", KMP_execute_time); 
	
	return 0;
 } 
