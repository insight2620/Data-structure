#include <stdio.h>
#include <string.h> 
#include <stdlib.h>

typedef int Position;
#define NotFound -1

void BuildMatch(char *pattern, int *match)//关键词预分析函数
{	
	//分析pattern,对pattern的每一个字符得出它对应的match值
	Position i, j;
	int m = strlen(pattern); 
	match[0] = -1; //pattern的第一个字符match值为-1

	for (j = 1; j < m; j++) 
	{
		i = match[j - 1];  //用i替代 match[j - 1],方便后面表示
		while ((i >= 0) && (pattern[i + 1] != pattern[j]))
			i = match[i];  //回退再比较
		if (pattern[i + 1] == pattern[j])
			match[j] = i + 1;
		else match[j] = -1; 
	}
}

Position KMP(char *string, char *pattern) //字符串模式匹配函数
{
	int n = strlen(string);   //求字符串string长度
	int m = strlen(pattern);  //求字符串pattern长度
	Position s, p, *match;

	if (n < m) return NotFound;  //n < m 时一定不匹配
	match = (Position *)malloc(sizeof(Position) * m);  //申请m个整型数据的空间,首地址强制转换为int型指针
	BuildMatch(pattern, match); //调用BuildMatch函数分析pattern,对pattern的每一个字符得出它对应的match值
	s = p = 0; //两个标志设为0使两个字符串从头开始匹配(两个字符串数组的下标)
	while (s < n && p < m) 
	{
		if (string[s] == pattern[p]) 
		{
			s++; p++; //如果前面的字符匹配上了则继续向后比较
		}
		else if (p > 0) p = match[p - 1] + 1; //指针P回退,再开始比较(相当于pattern向后挪动)
		else s++; //既p=0的情况既第一个字母就匹配不上，此时指针s向后挪一位再比
	}
	return (p == m) ? (s - m) : NotFound; //pattern中字符全部匹配完表示匹配上,返回string中对应的下标,否则返回NotFound
}

int main()
{
	char pattern1[100]; //存储关键词的字符串数组
	char pattern2[100]; 
	char pattern3[100]; 
	int a = 0;
	printf("请设置3个垃圾邮件过滤关键词：\n");
	printf("(空格分开回车结束)\n");
	scanf_s("%s", pattern1, 100); 
	scanf_s("%s", pattern2, 100);
	scanf_s("%s", pattern3, 100);
	printf("\n");
	while (a < 60) //设置测试次数
	{
		char string[9000]; //存储邮件的字符串数组
		printf("请输入邮件内容,按回车结束(支持中英文)：\n");
		scanf_s("%s", string, 9000);
		Position p1 = KMP(string, pattern1); //调用模式匹配函数,得到pattern在string中的位置
		Position p2 = KMP(string, pattern2); //同上,返回数组下标赋值给p2
		Position p3 = KMP(string, pattern3);
		if (p1 == NotFound && p2 == NotFound&& p3 == NotFound) //当全部关键词都未匹配上为正常邮件否则只要有一个匹配则为垃圾邮件
			 printf("\033[0;32;40m正常邮件,已接收！ \033[0m\n\n"); //格式符表示打印绿色字体
		else printf("\033[0;31;40m垃圾邮件,已过滤！ \033[0m\n\n"); //格式符表示打印红色字体
		a++;
	}
	return 0;
}
