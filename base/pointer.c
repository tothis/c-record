#include <stdio.h>
#include <windows.h>

int message(char *content, char *title) {
    MessageBox(0, content, title, 0);
    return 0;
}

int *zero() {
    return 0;
}

int main() {
    /*
     * c中变量 常量 函数等数据 载入内存后 都拥有唯一编号 即指针
     * 函数调用 参数传递为值传递 在函数中修改参数时 需通过参数的指针操作
     * 指针通过十六进制数映射内存地址
     *
     * 指针在未赋值时 指针随机指向一个数据 可能为系统数据 修改后可能会导致系统问题
     * 如int *p; *p=10;
     *
     * int a = 0;
     * a表示数据 &a表示数据指针
     * int *b = &a;
     * *b代表b中数据(a数据地址)对应的数据 访问*b等于访问a
     * 使用 `*test` 定义指针变量 要求 `test` 对应数据为其它数据地址
     * 数组本质为指针 即 `*a` 等同于 `a[]`
    */
    int a = 0; // 赋值
    int *b = &a; // 定义指针 b为保存变量a的地址

    int **c = &b; // 定义二级指针 c为保存变量b的地址
    printf("%d %s \n", a, "a"); // a变量值
    printf("%#x %s \n", &a, "&a"); // a变量地址
    printf("%#x %s \n", b, "b"); // a变量地址
    printf("%d %s \n", *b, "*b"); // a变量值
    printf("%d %s \n", **c, "**c"); // a变量值

    printf("%#x %s \n", &b, "&b"); // b变量地址
    printf("%#x %s \n", c, "c"); // b变量地址

    printf("%#x %s \n", message, "message"); // message函数地址
    printf("%#x %s \n", &message, "&message"); // message函数地址

    // 函数指针
    // 函数返回值类型 函数指针名称 函数参数列表
    int (*fun)(char *a, char *b) = message;
    fun("内容", "标题");

    printf("%#x %s \n", zero, "zero"); // zero变量地址
    printf("%#x %s \n", zero(), "zero()"); // 执行zero函数
}