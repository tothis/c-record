/*
 * 如果未定义NUMBER 则定义NUMBER 并编译下面代码 直到遇到#endif 避免重复定义
 */
#ifndef NUMBER
#define NUMBER

/* 依赖库 */
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// 随机数
int random(void);

#endif