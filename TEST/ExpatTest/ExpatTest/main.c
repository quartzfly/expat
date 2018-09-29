
#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include "C:/Program Files (x86)//Expat 2.2.6/Source/lib/expat.h"

#define BUFFERSIZE 100

static void XMLCALL startElement(void *userData, const XML_Char *name, const XML_Char **atts)
{
	printf("start handle:\n");
	printf("\tname = %s\n", (char*)name);
	printf("current count = %d\n", *(int *)userData);
	char* a = "123";
	for (int i = 0; atts[i]; i+=2)
	{
		printf("i = %d %s %s\n", i, atts[i], atts[i+1]);
	}
	(*(int *)userData)++;
}

static void XMLCALL endElement(void *userData, const XML_Char *name)
{
	printf("end handle:");
	printf("\tname = %s\n", (char*)name);
}

/*
	characterHandler函数处理tag起始与终结之间的内容
	换行符跟制表符之前都会单独处理
	len的值是buf的长度，网上个别教程不对
*/
static void XMLCALL characterHandler(void *userData, const XML_Char *buf, int len)
{
	//len = 15l;
	//char value[50];
	//for (int i = 0; i < 151; i++)
	//{
	//	printf("%c ", buf[i]);
	//}
	//printf("\n");
	//strcpy(value, buf);
	//value[len] = '\0';
	printf("character handler: len = %d||", len);
	for (int i = 0; i < len; i++)
	{
		if (buf[i] == '\t')
		{
			printf("\\t %d ", buf[i]);
		}
		else if (buf[i] == '\n')
		{
			printf("\\n %d ", buf[i]);
		}
		else
		{
			printf("%c %d ", buf[i], buf[i]);
		}
	}
	printf("\n");
}

int main(int argc, char** argv)
{
	/*
	下面的代码展示了为什么在starrElement函数中可以通过atts[i]作为
	退出for循环的判断，atts是一个数组，若某个tag有n个属性，则atts
	的大小为2n+1
	0 2 4 ......n为tag的属性名
	1 3 5 ......n+1为tag的属性值
	最后一个为NULL，NULL被设定为0，所以可以作为判断条件
	下面的代码只会输出1
	*/
	char* strings[5] = { "1", NULL, "3", "4", "5" };
	for (int i = 0; strings[i]; i++)
	{
		printf("%s\n", strings[i]);
	}

	char buf[BUFFERSIZE+1];
	memset(buf, 0, BUFFERSIZE+1); // 初始化内存，在string.h头文件中

	printf("hello world\n");
	XML_Char* name1 = "string";
	XML_Char* name2 = "字符串";
	printf("%s\n", name1);
	printf("%s\n", name2);

	// XMLPARSEAPI(XML_Parser) XML_ParserCreate(const XML_Char *encoding);
	// param: encoding XML文件的编码格式，传入NULL则不指定编码
	// 创建一个parser对象
	XML_Parser parser = XML_ParserCreate(NULL);

	int count = 0;
	XML_SetUserData(parser, &count);

	XML_SetElementHandler(parser, startElement, endElement);
	XML_SetCharacterDataHandler(parser, characterHandler);
	// 使用fread+while读取文件
	int flag = 0;
	FILE* file;
	fopen_s(&file, "G:\\8.project\\2.expat\\test.xml", "r+");
	while (!flag)
	{
		memset(buf, 0, BUFFERSIZE+1);
		// fread(要读取的内存首地址， 要读取的文件中基本的单位（例如一个字节是一个英文，两个字节是一个汉字）， 共读多少， 输入流）
		// 返回读取了多少个基本单位（例如，10个字节）
		size_t len = fread(buf, 1, BUFFERSIZE, file);
		buf[len] = '\0';
		// flag = len < sizeof(buf)-1;
		flag = feof(file);
		XML_Parse(parser, buf, (int)len, flag);
		printf("------------------------------------------\n");
	}
	XML_ParserFree(parser);
	system("pause");
	return 0;
}
