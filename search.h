#ifndef SEARCH_H
#define SEARCH_H

/*
 * 在词典文件 dict.txt 中查找单词 pwords，把查到的含义写入 pout。
 * 返回值： 0  找到
 *        -1  打开词典文件失败
 *        -2  词典中没有这个单词
 */
extern int Findwords(char *pwords, char *pout,char *pfile);

#endif
