/*
 * 简单web服务器 可同时响应多个浏览器请求
 * 文件存在时 返回文件 文件不存在 返回404页面
 */
#include <winsock2.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <direct.h>

#define DEFAULT_PORT 80 // 端口80
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
    SOCKET sListen, sAccept; // 服务器监听套接字 连接套接字
    struct sockaddr_in s1, s2; // 服务器地址 客户端地址

    printf("**********\n");
    printf("server start\n");
    printf("**********\n");

    // 加载协议栈
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("加载失败\n");
        return USER_ERROR;
    }

    // 创建监听套接字 监听客户请求
    sListen = socket(AF_INET, SOCK_STREAM, 0);
    if (sListen == INVALID_SOCKET) {
        printf("创建出错 :  %d\n", WSAGetLastError());
        return USER_ERROR;
    }

    // 创建服务器地址 ip+端口号
    s1.sin_family = AF_INET;
    s1.sin_port = htons(DEFAULT_PORT); // 服务器端口号
    s1.sin_addr.s_addr = htonl(INADDR_ANY); // 服务器IP地址 默认使用本机IP

    // 绑定监听套接字和服务器地址
    if (bind(sListen, (LPSOCKADDR) &s1, sizeof(s1)) == SOCKET_ERROR) {
        printf("blind() failed : %d\n", WSAGetLastError());
        return USER_ERROR;
    }

    // 通过监听套接字进行监听
    if (listen(sListen, 5) == SOCKET_ERROR) {
        printf("listen() failed : %d\n", WSAGetLastError());
        return USER_ERROR;
    }
    // 循环等待客户的请求
    while (1) {
        // 接受客户端的连接请求 返回与该客户建立的连接套接字
        int size = sizeof(s2);
        sAccept = accept(sListen, (struct sockaddr *) &s2, &size);
        if (sAccept == INVALID_SOCKET) {
            printf("accept() failed : %d\n", WSAGetLastError());
            break;
        }
        // 创建线程接受浏览器请求
        DWORD ThreadID;
        CreateThread(NULL, 0, server, (LPVOID) sAccept, 0, &ThreadID);
    }
    closesocket(sListen);
    WSACleanup();
    return 0;
}

// 发送404 file_not_found报头
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

// 发送200 ok报头
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

// 发送自定义404页面
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

// 发送请求的资源
int send_file(SOCKET sAccept, FILE *resource) {
    char send_buf[BUF_LENGTH];
    while (1) {
        memset(send_buf, 0, sizeof(send_buf)); // 缓存清0
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

    // 清空缓存
    memset(recv_buf, 0, sizeof(recv_buf));
    // 接收错误
    if (recv(sAccept, recv_buf, sizeof(recv_buf), 0) == SOCKET_ERROR) {
        // 接收失败
        printf("recv failed : %d\n", WSAGetLastError());
        return USER_ERROR;
    } else
        printf("recv data from client : %s\n", recv_buf); // 接收成功 打印请求报文

    // 处理接收数据
    i = 0;
    j = 0;
    // 取出第一个单词 一般为HEAD GET POST
    while (!(' ' == recv_buf[j]) && (i < sizeof(method) - 1)) {
        method[i] = recv_buf[j];
        i++;
        j++;
    }
    method[i] = '\0'; // 结束符

    // 请求方法不为GET或HEAD 则断开本次连接
    if (stricmp(method, "GET") && stricmp(method, "HEAD")) {
        closesocket(sAccept); // 释放连接套接字 结束与该客户通信
        printf("不支持此请求方法\n");
        return USER_ERROR;
    }
    printf("请求方法 : %s\n", method);

    // 获取url中第二个'/'后内容 并把'/'改为windows路径分隔符'\'
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
    printf("请求地址 : %s\n", url);

    // 将请求的url路径转换为本地路径
    _getcwd(path, _MAX_PATH);
    strcat(path, url);
    printf("本地地址 : %s\n", path);

    // 打开本地路径下文件 网络传输中用r文本方式打开会出错
    FILE *resource = fopen(path, "rb");

    // 无此文件则发送404页面 并断开本次连接
    if (resource == NULL) {
        file_not_found(sAccept);
        if (0 == stricmp(method, "GET"))
            send_not_found(sAccept);

        closesocket(sAccept); // 释放连接套接字 结束与该客户通信
        printf("找不到文件\n");
        return USER_ERROR;
    }

    // 求出文件长度 记得重置文件指针到文件头
    fseek(resource, 0, SEEK_SET);
    fseek(resource, 0, SEEK_END);
    long length = ftell(resource);
    printf("文件长度 : %ld\n", length);
    fseek(resource, 0, SEEK_SET);

    // 发送200 OK HEAD
    file_ok(sAccept, length);

    if (0 == stricmp(method, "GET")) {
        if (0 == send_file(sAccept, resource))
            printf("返回文件成功\n");
        else
            printf("返回文件失败\n");
    }
    fclose(resource);

    closesocket(sAccept); // 释放连接套接字 结束与该客户通信
    printf("请求关闭\n");
    return 0;
}