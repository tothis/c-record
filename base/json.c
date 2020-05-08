#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../lib/cJSON/cJSON.h"

void parse() {
    char *json1 = "{\"user\":{\"userName\":\"����\",\"address\":\"�Ϻ�\",\"age\":18,\"score\":99.9,\"sex\":true}}";
    char *json2 = "{\"userName\":\"����\",\"address\":\"�Ϻ�\",\"age\":18,\"score\":99.9,\"sex\":true}";

    cJSON *root;
    root = cJSON_Parse(json1);
    cJSON *format = cJSON_GetObjectItem(root, "user");
    printf("�û��� -> %s\n", cJSON_GetObjectItem(format, "userName")->valuestring);
    printf("���� -> %d\n", cJSON_GetObjectItem(format, "age")->valueint);
    printf("�ɼ� -> %g\n", cJSON_GetObjectItem(format, "score")->valuedouble);
    cJSON_Delete(root);

    root = cJSON_Parse(json2);
    printf("�û��� -> %s\n", cJSON_GetObjectItem(root, "userName")->valuestring);
    cJSON_Delete(root);
}

void create() {
    // Ƕ������
    cJSON *pRoot = cJSON_CreateObject();
    cJSON *pArray = cJSON_CreateArray();
    cJSON_AddItemToObject(pRoot, "user", pArray);
    cJSON *pItem = cJSON_CreateObject();
    cJSON_AddStringToObject(pItem, "userName", "frank");
    cJSON_AddBoolToObject(pItem, "sex", true);
    cJSON_AddNumberToObject(pItem, "age", 20);
    cJSON_AddNumberToObject(pItem, "score", 99.9);
    cJSON_AddItemToArray(pArray, pItem);
    char *szJSON = cJSON_Print(pRoot);
    printf(szJSON);
    printf("\n");

    // Ƕ�׶���
    pRoot = cJSON_CreateObject();
    pItem = cJSON_CreateObject();
    cJSON_AddStringToObject(pItem, "userName", "frank");
    cJSON_AddItemToObject(pRoot, "user", pItem);
    szJSON = cJSON_Print(pRoot);
    printf(szJSON);
    printf("\n");

    // ����
    pRoot = cJSON_CreateObject();
    cJSON_AddStringToObject(pRoot, "userName", "james");
    szJSON = cJSON_Print(pRoot);
    printf(szJSON);
    printf("\n");

    cJSON_Delete(pRoot);
    free(szJSON);
}

int main() {
    parse();
    create();
    return 0;
}