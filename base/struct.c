#include <stdio.h>
#include <stdbool.h>

struct user { // �ṹ��������
    unsigned char *userName;
    unsigned char *address;
    short age;
    float score;
    bool sex;
} user1 = {
        "����", "�Ϻ�", 18, 99.9, true
}, user2; // �ṹ�������

void print(struct user user) {
    printf("userName:%s, address:%s, age:%d, score:%g, sex:%d\n", user.userName, user.address, user.age, user.score,
           user.sex);
}

int main() {
    user2.userName = "frank";
    user2.address = "����";
    user2.age = 20;
    user2.score = 59.9;
    user2.sex = false;
    print(user1);
    print(user2);
    return 0;
}