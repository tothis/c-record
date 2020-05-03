#include <stdio.h>

int main() {

    const int AMOUNT = 100;
    int price;
    printf("ÇëÊäÈë½ğ¶î");
    scanf("%d", &price);

    int change = AMOUNT - price;
    printf("ÕÒÄã%d", change);

    return 0;
}