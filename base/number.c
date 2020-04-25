#include <unistd.h>
#include "number.h"

// 随机数
int random(void) {
    static int value;
    srand((unsigned) time(NULL)); // 使用当前时间作为伪随机数种子 最多精确到秒
    sleep(1); // 睡眠1s
    value = rand();
    return value;
}