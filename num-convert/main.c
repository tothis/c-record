#include <stdio.h>

#define CHAR_MAX 128 /* 最大允许字符串长度 */

int charToNum(char ch); /* 字符对应数字 */
char numToChar(int num); /* 数字对应字符 */
long numToDecimal(char *beforeNum, int before); /* 转换为10进制 */
int decimalToNLength(char *beforeNum, long decimalNum, int after); /* 转换为指定进制后 获取字符数组长度 */
void output(char beforeNum[], int length); /* 将字符数组逆序打印 */

int main() {
    int before; /* 存储原数制 */
    int after; /* 存储目标数制 */
    int length; /* 存储转换成目标数制后字符数组的长度 */
    long decimalNum; /* 存储转换成的10进制数 */
    char beforeNum[CHAR_MAX]; /* 存储待转换的数值和转换后的数值 */
    int flag = 1; /* 存储是否退出程序的标志 */
    /* 利用输入的flag值控制循环是否结束 */
    while (flag) {
        printf("转换前的数>>");
        scanf("%s", beforeNum);
        printf("转换前的数制是>>");
        scanf("%d", &before);
        printf("转换后的数制是>>");
        scanf("%d", &after);
        printf("转换后的数是>>");
        decimalNum = numToDecimal(beforeNum, before);
        length = decimalToNLength(beforeNum, decimalNum, after);
        output(beforeNum, length);
        printf("继续请输1 退出请输0\n");
        scanf("%d", &flag);
    }
    return 0;
}

/* 将字符转换成数字 */
int charToNum(char ch) {
    if (ch >= '0' && ch <= '9')
        return ch - '0'; /* 将数字字符转换成数字 */
    else
        return ch - 'A' + 10; /* 将字母字符转换成数字 */
}

/* 将数字转换成字符 */
char numToChar(int num) {
    if (num >= 0 && num <= 9)
        return (char) ('0' + num - 0); /* 将0~9之间的数字转换成字符 */
    else
        return (char) ('A' + num - 10); /* 将大于10的数字转换成字符 */
}

long numToDecimal(char beforeNum[], int source) {
    long decimalNum = 0;
    int length;
    int i;
    for (i = 0; beforeNum[i] != '\0'; i++);
    length = i;
    for (i = 0; i <= length - 1; i++) /* 累加 */
        decimalNum = (decimalNum * source) + charToNum(beforeNum[i]);
    return decimalNum;
}

int decimalToNLength(char beforeNum[], long decimalNum, int after) {
    int i = 0;
    while (decimalNum) {
        beforeNum[i] = numToChar(decimalNum % after); /* 求出余数并转换为字符 */
        decimalNum = decimalNum / after; /* 用十进制数除以基数 */
        i++;
    }
    beforeNum[i] = '\0';
    return i;
}

void output(char beforeNum[], int length) {
    for (int i = length - 1; i >= 0; i--) /* 输出beforeNum数组中的值 */
        printf("%c", beforeNum[i]);
    printf("\n");
}