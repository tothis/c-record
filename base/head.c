/*
 * 双引号 先搜索工程文件所在目录 再搜索编译器头文件所在目录
 * 尖括号 搜索顺序与之相反
 */
#include <stdio.h>
#include "number.h"

#define N 10

int main() {
    for (int i = 0; i < N; i++) {
        printf("%d-", i);
        printf("%d", random());
        printf(i == N - 1 ? "" : "\n");
    }
    return 0;
}