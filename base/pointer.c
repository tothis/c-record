#include <stdio.h>
#include <windows.h>

int message(char *content, char *title) {
    MessageBox(0, content, title, 0);
    return 0;
}

int *zero() {
    return 0;
}

int main() {
    /*
     * c�б��� ���� ���������� �����ڴ�� ��ӵ��Ψһ��� ��ָ��
     * �������� ��������Ϊֵ���� �ں������޸Ĳ���ʱ ��ͨ��������ָ�����
     * ָ��ͨ��ʮ��������ӳ���ڴ��ַ
     *
     * ָ����δ��ֵʱ ָ�����ָ��һ������ ����Ϊϵͳ���� �޸ĺ���ܻᵼ��ϵͳ����
     * ��int *p; *p=10;
     *
     * int a = 0;
     * a��ʾ���� &a��ʾ����ָ��
     * int *b = &a;
     * *b����b������(a���ݵ�ַ)��Ӧ������ ����*b���ڷ���a
     * ʹ�� `*test` ����ָ����� Ҫ�� `test` ��Ӧ����Ϊ�������ݵ�ַ
     * ���鱾��Ϊָ�� �� `*a` ��ͬ�� `a[]`
    */
    int a = 0; // ��ֵ
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
    fun("����", "����");

    printf("%#x %s \n", zero, "zero"); // zero������ַ
    printf("%#x %s \n", zero(), "zero()"); // ִ��zero����
}