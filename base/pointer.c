#include <stdio.h>
#include <windows.h>
#include "../common/out.c"

#define SIZE 4

int message(char *content, char *title) {
    MessageBox(0, content, title, 0);
    return 0;
}

int test1() {
    return 0;
}

void test2(int *num) {
    // `*`和`++`属于同级运算 表达式从右向左运算 *p++等同于*(p++) 如下为num对应地址的值自增
    // (*num)++;
    ++*num;
}

int *copy(int source[], int target[], int size) {
    for (int i = 0; i < size; i++)
        target[i] = source[i];
    return target;
}

int main() {
    /*
     * c中变量 常量 函数等数据 载入内存后 都拥有唯一编号 即指针
     * 函数调用 参数传递为值传递 在函数中修改参数时 需通过参数的指针操作
     * 指针通过十六进制数映射内存地址
     *
     * 指针变量在未赋值时 指针变量随机指向一个数据 可能为系统数据 修改后会造成内存区错误修改 可能会导致系统问题
     * 如int *p; *p=10;
     * 指针变量定义后必须初始化 且值为一个地址 不可赋值为其他类型数据
     * 指针变量暂不使用时 先赋值为NULL 后续使用时 重新赋值其它数据地址
     *
     * int a = 0;
     * a表示数据 &a表示数据指针
     * int *b = &a;
     * *b代表b中数据(a数据地址)对应的数据 访问*b等于访问a
     * 数组本质为指针 函数传参时`int *a`等同`int a[]`
     */
    int a = 0; // 定义并赋值
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
    // fun("内容", "标题");

    printf("%#x %s \n", test1, "test1"); // test1函数地址
    printf("%#x %s \n", test1(), "test1()"); // 执行test1函数

    int num = 0;
    test2(&num);
    printf("%d %s \n", num, "test2()");

    int a1[SIZE] = {1, 2, 3, 4};
    int a2[SIZE];
    int *a3;
    a3 = copy(a1, a2, SIZE);
    outInt(a2, SIZE); // 1,2,3,4
    outInt(a3, SIZE); // 1,2,3,4

    // 暂停 等待用户信号 否则控制台一闪即过 来不及看到执行结果
    // system("pause");
}