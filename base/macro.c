#include <stdio.h>
/*
 * 宏与全局变量区别
 * 作用时间不同
 * 宏在编译时会被替换 全局变量运行时才可使用 即需要占用内存
 * 宏不可被赋值 全局变量可赋值
 * 宏在定义所在文件 或引用所在文件生效 全局变量可在工程所有文件中生效
 */
#define N 10

int main() {
    for (int i = 0; i < N; i++) {
        printf("%d", i);
        printf(i == N - 1 ? "" : "-");
    }
    return 0;
}