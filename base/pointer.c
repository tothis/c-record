#include <stdio.h>
#include <windows.h>
#include "../common/out.c"

#define SIZE 4

int message(char *content, char *title) {
    MessageBox(0, content, title, 0);
    return 0;
}

int test1() {
    return 0;
}

void test2(int *num) {
    // `*`��`++`����ͬ������ ���ʽ������������ *p++��ͬ��*(p++) ����Ϊnum��Ӧ��ַ��ֵ����
    // (*num)++;
    ++*num;
}

int *copy(int source[], int target[], int size) {
    for (int i = 0; i < size; i++)
        target[i] = source[i];
    return target;
}

int main() {
    /*
     * c�б��� ���� ���������� �����ڴ�� ��ӵ��Ψһ��� ��ָ��
     * �������� ��������Ϊֵ���� �ں������޸Ĳ���ʱ ��ͨ��������ָ�����
     * ָ��ͨ��ʮ��������ӳ���ڴ��ַ
     *
     * ָ�������δ��ֵʱ ָ��������ָ��һ������ ����Ϊϵͳ���� �޸ĺ������ڴ��������޸� ���ܻᵼ��ϵͳ����
     * ��int *p; *p=10;
     * ָ��������������ʼ�� ��ֵΪһ����ַ ���ɸ�ֵΪ������������
     * ָ������ݲ�ʹ��ʱ �ȸ�ֵΪNULL ����ʹ��ʱ ���¸�ֵ�������ݵ�ַ
     *
     * int a = 0;
     * a��ʾ���� &a��ʾ����ָ��
     * int *b = &a;
     * *b����b������(a���ݵ�ַ)��Ӧ������ ����*b���ڷ���a
     * ���鱾��Ϊָ�� ��������ʱ`int *a`��ͬ`int a[]`
     */
    int a = 0; // ���岢��ֵ
    int *b = &a; // ����ָ�� bΪ�������a�ĵ�ַ

    int **c = &b; // �������ָ�� cΪ�������b�ĵ�ַ
    printf("%d %s \n", a, "a"); // a����ֵ
    printf("%#x %s \n", &a, "&a"); // a������ַ
    printf("%#x %s \n", b, "b"); // a������ַ
    printf("%d %s \n", *b, "*b"); // a����ֵ
    printf("%d %s \n", **c, "**c"); // a����ֵ

    printf("%#x %s \n", &b, "&b"); // b������ַ
    printf("%#x %s \n", c, "c"); // b������ַ

    printf("%#x %s \n", message, "message"); // message������ַ
    printf("%#x %s \n", &message, "&message"); // message������ַ

    // ����ָ��
    // ��������ֵ���� ����ָ������ ���������б�
    int (*fun)(char *a, char *b) = message;
    // fun("����", "����");

    printf("%#x %s \n", test1, "test1"); // test1������ַ
    printf("%#x %s \n", test1(), "test1()"); // ִ��test1����

    int num = 0;
    test2(&num);
    printf("%d %s \n", num, "test2()");

    int a1[SIZE] = {1, 2, 3, 4};
    int a2[SIZE];
    int *a3;
    a3 = copy(a1, a2, SIZE);
    outInt(a2, SIZE); // 1,2,3,4
    outInt(a3, SIZE); // 1,2,3,4

    // ��ͣ �ȴ��û��ź� �������̨һ������ ����������ִ�н��
    // system("pause");
}