/*
 * ��web������ ��ͬʱ��Ӧ������������
 * �ļ�����ʱ �����ļ� �ļ������� ����404ҳ��
 */
#include <winsock2.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <direct.h>

#define DEFAULT_PORT 80 // �˿�80
#define BUF_LENGTH 1024
#define MIN_BUF 128
#define MAX_BUF 256
#define USER_ERROR -1
#define SERVER "http server\n"

int file_not_found(SOCKET sAccept);

int file_ok(SOCKET sAccept, long flen);

int send_file(SOCKET sAccept, FILE *resource);

int send_not_found(SOCKET sAccept);

DWORD WINAPI server(LPVOID lparam);

int main() {
    WSADATA wsaData;
    SOCKET sListen, sAccept; // �����������׽��� �����׽���
    struct sockaddr_in s1, s2; // ��������ַ �ͻ��˵�ַ

    printf("**********\n");
    printf("server start\n");
    printf("**********\n");

    // ����Э��ջ
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("����ʧ��\n");
        return USER_ERROR;
    }

    // ���������׽��� �����ͻ�����
    sListen = socket(AF_INET, SOCK_STREAM, 0);
    if (sListen == INVALID_SOCKET) {
        printf("�������� :  %d\n", WSAGetLastError());
        return USER_ERROR;
    }

    // ������������ַ ip+�˿ں�
    s1.sin_family = AF_INET;
    s1.sin_port = htons(DEFAULT_PORT); // �������˿ں�
    s1.sin_addr.s_addr = htonl(INADDR_ANY); // ������IP��ַ Ĭ��ʹ�ñ���IP

    // �󶨼����׽��ֺͷ�������ַ
    if (bind(sListen, (LPSOCKADDR) &s1, sizeof(s1)) == SOCKET_ERROR) {
        printf("blind() failed : %d\n", WSAGetLastError());
        return USER_ERROR;
    }

    // ͨ�������׽��ֽ��м���
    if (listen(sListen, 5) == SOCKET_ERROR) {
        printf("listen() failed : %d\n", WSAGetLastError());
        return USER_ERROR;
    }
    // ѭ���ȴ��ͻ�������
    while (1) {
        // ���ܿͻ��˵��������� ������ÿͻ������������׽���
        int size = sizeof(s2);
        sAccept = accept(sListen, (struct sockaddr *) &s2, &size);
        if (sAccept == INVALID_SOCKET) {
            printf("accept() failed : %d\n", WSAGetLastError());
            break;
        }
        // �����߳̽������������
        DWORD ThreadID;
        CreateThread(NULL, 0, server, (LPVOID) sAccept, 0, &ThreadID);
    }
    closesocket(sListen);
    WSACleanup();
    return 0;
}

// ����404 file_not_found��ͷ
int file_not_found(SOCKET sAccept) {
    char send_buf[MIN_BUF];
    sprintf(send_buf, "HTTP/1.1 404 NOT FOUND\n");
    send(sAccept, send_buf, strlen(send_buf), 0);
    sprintf(send_buf, "Connection: keep-alive\n");
    send(sAccept, send_buf, strlen(send_buf), 0);
    sprintf(send_buf, SERVER);
    send(sAccept, send_buf, strlen(send_buf), 0);
    sprintf(send_buf, "Content-Type: text/html\n");
    send(sAccept, send_buf, strlen(send_buf), 0);
    sprintf(send_buf, "\n");
    send(sAccept, send_buf, strlen(send_buf), 0);
    return 0;
}

// ����200 ok��ͷ
int file_ok(SOCKET sAccept, long flen) {
    char send_buf[MIN_BUF];
    sprintf(send_buf, "HTTP/1.1 200 OK\n");
    send(sAccept, send_buf, strlen(send_buf), 0);
    sprintf(send_buf, "Connection: keep-alive\n");
    send(sAccept, send_buf, strlen(send_buf), 0);
    sprintf(send_buf, SERVER);
    send(sAccept, send_buf, strlen(send_buf), 0);
    sprintf(send_buf, "Content-Length: %ld\n", flen);
    send(sAccept, send_buf, strlen(send_buf), 0);
    sprintf(send_buf, "Content-Type: text/html\n");
    send(sAccept, send_buf, strlen(send_buf), 0);
    sprintf(send_buf, "\n");
    send(sAccept, send_buf, strlen(send_buf), 0);
    return 0;
}

// �����Զ���404ҳ��
int send_not_found(SOCKET sAccept) {
    char send_buf[MAX_BUF];
    sprintf(send_buf,
            "<html>"
            "<title>404</title>"
            "<style>"
            "body{display:flex;align-items:center;justify-content:center;}"
            "</style>"
            "<body>"
            "<h1>404 not found</h1>"
            "</body>"
            "<html>");
    send(sAccept, send_buf, strlen(send_buf), 0);
    return 0;
}

// �����������Դ
int send_file(SOCKET sAccept, FILE *resource) {
    char send_buf[BUF_LENGTH];
    while (1) {
        memset(send_buf, 0, sizeof(send_buf)); // ������0
        fgets(send_buf, sizeof(send_buf), resource);
        if (SOCKET_ERROR == send(sAccept, send_buf, strlen(send_buf), 0)) {
            printf("send() failed : %d\n", WSAGetLastError());
            return USER_ERROR;
        }
        if (feof(resource))
            return 0;
    }
}

DWORD WINAPI server(LPVOID lparam) {
    SOCKET sAccept = (SOCKET) (LPVOID) lparam;
    char recv_buf[BUF_LENGTH];
    char method[MIN_BUF];
    char url[MIN_BUF];
    char path[_MAX_PATH];
    int i, j;

    // ��ջ���
    memset(recv_buf, 0, sizeof(recv_buf));
    // ���մ���
    if (recv(sAccept, recv_buf, sizeof(recv_buf), 0) == SOCKET_ERROR) {
        // ����ʧ��
        printf("recv failed : %d\n", WSAGetLastError());
        return USER_ERROR;
    } else
        printf("recv data from client : %s\n", recv_buf); // ���ճɹ� ��ӡ������

    // �����������
    i = 0;
    j = 0;
    // ȡ����һ������ һ��ΪHEAD GET POST
    while (!(' ' == recv_buf[j]) && (i < sizeof(method) - 1)) {
        method[i] = recv_buf[j];
        i++;
        j++;
    }
    method[i] = '\0'; // ������

    // ���󷽷���ΪGET��HEAD ��Ͽ���������
    if (stricmp(method, "GET") && stricmp(method, "HEAD")) {
        closesocket(sAccept); // �ͷ������׽��� ������ÿͻ�ͨ��
        printf("��֧�ִ����󷽷�\n");
        return USER_ERROR;
    }
    printf("���󷽷� : %s\n", method);

    // ��ȡurl�еڶ���'/'������ ����'/'��Ϊwindows·���ָ���'\'
    i = 0;
    while ((' ' == recv_buf[j]) && (j < sizeof(recv_buf)))
        j++;
    while (!(' ' == recv_buf[j]) && (i < sizeof(recv_buf) - 1) && (j < sizeof(recv_buf))) {
        if (recv_buf[j] == '/')
            url[i] = '\\';
        else if (recv_buf[j] == ' ')
            break;
        else
            url[i] = recv_buf[j];
        i++;
        j++;
    }
    url[i] = '\0';
    printf("�����ַ : %s\n", url);

    // �������url·��ת��Ϊ����·��
    _getcwd(path, _MAX_PATH);
    strcat(path, url);
    printf("���ص�ַ : %s\n", path);

    // �򿪱���·�����ļ� ���紫������r�ı���ʽ�򿪻����
    FILE *resource = fopen(path, "rb");

    // �޴��ļ�����404ҳ�� ���Ͽ���������
    if (resource == NULL) {
        file_not_found(sAccept);
        if (0 == stricmp(method, "GET"))
            send_not_found(sAccept);

        closesocket(sAccept); // �ͷ������׽��� ������ÿͻ�ͨ��
        printf("�Ҳ����ļ�\n");
        return USER_ERROR;
    }

    // ����ļ����� �ǵ������ļ�ָ�뵽�ļ�ͷ
    fseek(resource, 0, SEEK_SET);
    fseek(resource, 0, SEEK_END);
    long length = ftell(resource);
    printf("�ļ����� : %ld\n", length);
    fseek(resource, 0, SEEK_SET);

    // ����200 OK HEAD
    file_ok(sAccept, length);

    if (0 == stricmp(method, "GET")) {
        if (0 == send_file(sAccept, resource))
            printf("�����ļ��ɹ�\n");
        else
            printf("�����ļ�ʧ��\n");
    }
    fclose(resource);

    closesocket(sAccept); // �ͷ������׽��� ������ÿͻ�ͨ��
    printf("����ر�\n");
    return 0;
}