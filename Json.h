#ifndef JSON_H
#define JSON_H
#include <string>
#include "cJSON.h"
using namespace std;
class Json
{
public:
    Json();
    ~Json();
    void add(string key, string value);
    string print();
    void parse(string buf);
    string value(string key);
private:
    cJSON *root;
    //forbind less copy
    Json(const Json &othre);
    Json& operator = (const Json& other);
};

#endif // JSON_H
