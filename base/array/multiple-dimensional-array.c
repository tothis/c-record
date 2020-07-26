#include <stdio.h>

void test1(int array[1][2]) {
    printf("%d", array[0][1]);
}

// 可省略第一个维度数据长度声明
void test2(int array[][1]) {
    printf("%d", array[0][0]);
}

void test3(int **array) {
    printf("%d", array[0][1]);
}

int main() {
    int array1[1][2] = {{1, 2}};
    // 可省略第一个维度数据长度声明
    int array2[][1] = {{3},
                       {4}};
    // 声明指针数组
    int *array3[3];
    array3[0] = array1[0];

    test1(array1);
    test2(array2);
    test3(array3);
    test3((int **) array1);
    return 0;
}