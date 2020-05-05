#include <stdio.h>

int main() {
    goto flag;
    printf("不会执行");
    flag:
    printf("会被执行");
    return 0;
}