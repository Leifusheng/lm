#include "Json.h"
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

string Json::print()
{
    char *p = cJSON_Print(root);
    string ret = p;
    free(p);
    return ret;
}
