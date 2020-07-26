#include <stdio.h>

void test1(int array[2]) {
    printf("%d", array[0]);
}

// 可省略声明长度声明
void test2(int array[]) {
    printf("%d", array[0]);
}

void test3(int *array) {
    printf("%d", array[1]);
}

int main() {
    int array1[] = {1, 2};
    int array2[2] = {3, 4};
    // 数组本身为指针无需使用'&'符号
    int *array3 = (int *) array2;

    test1(array1);
    test2(array2);
    test3(array3);
    return 0;
}