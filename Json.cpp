#include "Json.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
Json::Json()
{
    root = cJSON_CreateObject();
}

Json::~Json()
{
    cJSON_Delete(root);
}

void Json::add(string key, string value)
{
    cJSON_AddStringToObject(root, key.c_str(), value.c_str());
}

void Json::add(string key, int value)
{
    char buf[256];
    sprintf(buf, "%d", value);
    add(key, buf);
}

string Json::print()
{
    char *p = cJSON_Print(root);
    string ret = p;
    free(p);
    return ret;
}

void Json::parse(string buf)
{
    if (root != NULL)
        cJSON_Delete(root);
    root = cJSON_Parse(buf.c_str());
}

string Json::value(string key)
{
    cJSON* obj = cJSON_GetObjectItem(root, key.c_str());
    return obj->valuestring;
}
