#include <stdio.h>
#include <stdbool.h>

struct User { // 结构体类型名
    unsigned char *userName;
    unsigned char *address;
    short age;
    float score;
    bool sex;
} user1 = {
        "李磊", "上海", 18, 99.9, true
}, user2; // 结构体变量名

void print(struct User user) {
    printf("userName:%s, address:%s, age:%d, score:%g, sex:%d\n", user.userName, user.address, user.age, user.score,
           user.sex);
}

int main() {
    user2.userName = "frank";
    user2.address = "北京";
    user2.age = 20;
    user2.score = 59.9;
    user2.sex = false;
    print(user1);
    print(user2);
    struct User user3 = {
            "james", "深圳", 30, 60, true
    };
    print(user3);
    return 0;
}