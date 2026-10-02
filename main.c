#include <stdio.h>
#include <string.h>
#include "search.h"

int main(void)
{
    char words[32] = {0};
    char out[512]  = {0};
    int  ret = 0;

    while(1)
    {
        printf("请输入要查找的单词(q退出): \n");
        if (NULL == fgets(words, sizeof(words), stdin))//会读入\n
        {
            return -1;
        }
        words[strlen(words)-1] = '\0';     // 去掉行尾的换行符
        //words[strcspn(words, "\n")] = '\0';     // 去掉行尾的换行符

        if (0 == strcmp(words,"q"))
        {
            return 0;
        }

        ret = Findwords(words, out,"./dict.txt");
        if (-2 == ret)
            printf("未找到\n");
        else if (-1 == ret)
            printf("打开词典文件失败\n");
        else
            printf("\033[1;36m%10s\033[0m:    \033[32m%s\033[0m", words, out);//在printf("%10s:     %s", words, out)基础上增加效果——单词青色加粗，释义绿色
    }

    return 0;
}
