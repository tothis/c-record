#include <stdio.h>

int main() {

    const int AMOUNT = 100;
    int price;
    printf("��������");
    scanf("%d", &price);

    int change = AMOUNT - price;
    printf("����%d", change);

    return 0;
}