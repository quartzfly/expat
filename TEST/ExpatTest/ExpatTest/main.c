
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
	characterHandler��������tag��ʼ���ս�֮�������
	���з����Ʊ��֮ǰ���ᵥ������
	len��ֵ��buf�ĳ��ȣ����ϸ���̳̲���
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
	����Ĵ���չʾ��Ϊʲô��starrElement�����п���ͨ��atts[i]��Ϊ
	�˳�forѭ�����жϣ�atts��һ�����飬��ĳ��tag��n�����ԣ���atts
	�Ĵ�СΪ2n+1
	0 2 4 ......nΪtag��������
	1 3 5 ......n+1Ϊtag������ֵ
	���һ��ΪNULL��NULL���趨Ϊ0�����Կ�����Ϊ�ж�����
	����Ĵ���ֻ�����1
	*/
	char* strings[5] = { "1", NULL, "3", "4", "5" };
	for (int i = 0; strings[i]; i++)
	{
		printf("%s\n", strings[i]);
	}

	char buf[BUFFERSIZE+1];
	memset(buf, 0, BUFFERSIZE+1); // ��ʼ���ڴ棬��string.hͷ�ļ���

	printf("hello world\n");
	XML_Char* name1 = "string";
	XML_Char* name2 = "�ַ���";
	printf("%s\n", name1);
	printf("%s\n", name2);

	// XMLPARSEAPI(XML_Parser) XML_ParserCreate(const XML_Char *encoding);
	// param: encoding XML�ļ��ı����ʽ������NULL��ָ������
	// ����һ��parser����
	XML_Parser parser = XML_ParserCreate(NULL);

	int count = 0;
	XML_SetUserData(parser, &count);

	XML_SetElementHandler(parser, startElement, endElement);
	XML_SetCharacterDataHandler(parser, characterHandler);
	// ʹ��fread+while��ȡ�ļ�
	int flag = 0;
	FILE* file;
	fopen_s(&file, "G:\\8.project\\2.expat\\test.xml", "r+");
	while (!flag)
	{
		memset(buf, 0, BUFFERSIZE+1);
		// fread(Ҫ��ȡ���ڴ��׵�ַ�� Ҫ��ȡ���ļ��л����ĵ�λ������һ���ֽ���һ��Ӣ�ģ������ֽ���һ�����֣��� �������٣� ��������
		// ���ض�ȡ�˶��ٸ�������λ�����磬10���ֽڣ�
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
