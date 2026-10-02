# find_word · 命令行词典查询工具

用 C 语言写的轻量命令行查词工具：输入一个单词，从本地词库文件中查出它的释义。

本质上它是一个**「逐行 key-value 文本查找」工具**——只要文件满足「关键词 + 空格 + 内容」的行格式，就能用它来查。所以不只是英汉词典，中文词库、术语表、配置对照表等各类对照关系都能查。

## 特性

- 交互式查询：输入单词回车即出结果，输入 `q` 退出
- 结果彩色高亮：单词青色加粗、释义绿色
- 未命中、词库文件打不开，都有清晰提示
- 纯标准 C，无任何第三方依赖，编译即用

## 效果

```
请输入要查找的单词(q退出):
abacus
    abacus:    n.frame with beads that slide along parallel rods, used for teaching numbers to children, and (in some countries) for counting
```

> 实际终端中，单词显示为青色加粗，释义显示为绿色。

## 目录结构

| 文件 | 说明 |
|------|------|
| `main.c` | 程序入口，负责与用户交互 |
| `search.c` | 查词核心逻辑 `Findwords()` |
| `search.h` | 对外接口声明 |
| `Makefile` | 构建脚本 |
| `dict.txt` | 词库数据（纯文本，约 2 万条） |

## 编译与运行

```bash
make        # 编译，生成可执行文件 dict
./dict      # 运行
```

清理编译产物：

```bash
make clean
```

## 词库格式

`dict.txt` 每行一条，格式为「关键词 + 空格 + 释义」，词与释义之间可有一个或多个空格（用于对齐）：

```
a                indef art one
abacus           n.frame with beads that slide along parallel rods...
abandon          v.  go away from (a person or thing or place) not intending to return; forsake; desert
```

只要满足这个格式即可替换成自己的词库，中英文均可。

## 实现说明

核心函数：`int Findwords(char *pwords, char *pout, char *pfile)`

1. 打开词库文件，失败返回 `-1`
2. 逐行 `fgets` 读取，直到文件结束仍未命中则返回 `-2`
3. 用 `strtok` 切出当前行的关键词，与输入做 `strcmp` 精确比较
4. 命中后跳过词与释义之间的空格，把释义 `strcpy` 到调用者提供的缓冲区，返回 `0`

**返回值约定**：`0` 找到 / `-1` 打开文件失败 / `-2` 未找到。

设计上把「查词逻辑」与「用户交互」分成两个文件：`search.c` 只负责根据一个关键词返回内容，不做任何屏幕输出；`main.c` 负责输入输出与流程控制。这样查词引擎可以被复用到其它场景（比如将来做成服务端）。

## 平台

已在 Ubuntu 上编译运行通过。代码为标准 C，Windows（MinGW）下同样可以编译。

## 后续计划

- 目前为顺序扫描，单次查询复杂度 O(n)。可将词表一次性预加载进哈希表，把查询降到均摊 O(1)
- 每次查询都会重新打开词库文件，可优化为常驻句柄
- 支持从命令行参数直接传入待查词、支持批量查询

## License

本项目基于 [MIT License](LICENSE) 开源。
