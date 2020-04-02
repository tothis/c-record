#include <stdio.h>

#define CHAR_MAX 128 /* ��������ַ������� */

int charToNum(char ch); /* �ַ���Ӧ���� */
char numToChar(int num); /* ���ֶ�Ӧ�ַ� */
long numToDecimal(char *beforeNum, int before); /* ת��Ϊ10���� */
int decimalToNLength(char *beforeNum, long decimalNum, int after); /* ת��Ϊָ�����ƺ� ��ȡ�ַ����鳤�� */
void output(char beforeNum[], int length); /* ���ַ����������ӡ */

int main() {
    int before; /* �洢ԭ���� */
    int after; /* �洢Ŀ������ */
    int length; /* �洢ת����Ŀ�����ƺ��ַ�����ĳ��� */
    long decimalNum; /* �洢ת���ɵ�10������ */
    char beforeNum[CHAR_MAX]; /* �洢��ת������ֵ��ת�������ֵ */
    int flag = 1; /* �洢�Ƿ��˳�����ı�־ */
    /* ���������flagֵ����ѭ���Ƿ���� */
    while (flag) {
        printf("ת��ǰ����>>");
        scanf("%s", beforeNum);
        printf("ת��ǰ��������>>");
        scanf("%d", &before);
        printf("ת�����������>>");
        scanf("%d", &after);
        printf("ת���������>>");
        decimalNum = numToDecimal(beforeNum, before);
        length = decimalToNLength(beforeNum, decimalNum, after);
        output(beforeNum, length);
        printf("��������1 �˳�����0\n");
        scanf("%d", &flag);
    }
    return 0;
}

/* ���ַ�ת�������� */
int charToNum(char ch) {
    if (ch >= '0' && ch <= '9')
        return ch - '0'; /* �������ַ�ת�������� */
    else
        return ch - 'A' + 10; /* ����ĸ�ַ�ת�������� */
}

/* ������ת�����ַ� */
char numToChar(int num) {
    if (num >= 0 && num <= 9)
        return (char) ('0' + num - 0); /* ��0~9֮�������ת�����ַ� */
    else
        return (char) ('A' + num - 10); /* ������10������ת�����ַ� */
}

long numToDecimal(char beforeNum[], int source) {
    long decimalNum = 0;
    int length;
    int i;
    for (i = 0; beforeNum[i] != '\0'; i++);
    length = i;
    for (i = 0; i <= length - 1; i++) /* �ۼ� */
        decimalNum = (decimalNum * source) + charToNum(beforeNum[i]);
    return decimalNum;
}

int decimalToNLength(char beforeNum[], long decimalNum, int after) {
    int i = 0;
    while (decimalNum) {
        beforeNum[i] = numToChar(decimalNum % after); /* ���������ת��Ϊ�ַ� */
        decimalNum = decimalNum / after; /* ��ʮ���������Ի��� */
        i++;
    }
    beforeNum[i] = '\0';
    return i;
}

void output(char beforeNum[], int length) {
    for (int i = length - 1; i >= 0; i--) /* ���beforeNum�����е�ֵ */
        printf("%c", beforeNum[i]);
    printf("\n");
}