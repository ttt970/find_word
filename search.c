#include <stdio.h>
#include <string.h>
#include "search.h"

int Findwords(char *pwords, char *pout,char *pfile)
{
    char buffer_line[512] = {0};
    char *ptmp = NULL;
    FILE *fp = NULL;

    fp = fopen(pfile, "r");
    if (fp == NULL)
    {
        perror("fail to fopen");
        return -1;
    }

    while (1)
    {
        if (NULL == fgets(buffer_line, sizeof(buffer_line), fp))
        {
            fclose(fp);
            return -2;                   // 读到文件末尾都没找到
        }

        if (0 == strcmp(pwords, strtok(buffer_line," ")))//strtok将单词与释义分割，匹配成功执行如下代码
        {
            ptmp = buffer_line + strlen(pwords)+1;//取出释义_ok.因为strtok改了\0所以要+1
            //*pout = buffer_line + strlen(pwords)+1;//取出释义_ok.因为strtok改了\0所以要+1
            //for(;*pout == ' ';pout++);//去除释义前的空格——若直接退出，不会改变外部字符数组的值，因为真正存大东西的buffer_line已经销毁
            for(; *ptmp == ' '; ptmp++);//去除释义前的空格
            strcpy(pout,ptmp);      
            break;
        }
    }

    fclose(fp);
    return 0;
}
