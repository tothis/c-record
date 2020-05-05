#include <stdio.h>
#include <math.h>

int main() {
    // 科学计数法 默认保留小数点后6位
    printf("%e\n", .1);
    // 默认保留小数点后6位
    printf("%f\n", .1);
    // 类似`%f` 但会去掉多余零 最多保留六位有效数字
    printf("%g\n", .1);

    printf("----- -----\n");

    /*
     * 3的4次幂 底数为3 指数为4
     */
    printf("%g\n", pow(3, 4));

    /*
     * a^n=b(a>0且a≠1) 则n为以a为底b的对数 n=log(a)b a为对数的底数 b为真数
     * 例 2^3=8 3为以2为底8的对数 3=log₂8 2为对数的底数 8为真数
     */
    printf("%g\n", log(10)); // 以e为底的对数函数
    printf("%g\n", log10(100)); // 求以10为底的对数 数学中 lg等同log₁₀
    printf("%g\n", log(8) / log(2)); // 求以2为底8的对数 运用换底公式 计算log₂8
    printf("%g", exp(1)); // e的n次幂函数
    return 0;
}