#pragma once

#include "JsonValue.h"

#include <map>
#include <iostream>

class JsonObject
{
public:
    JsonValue& operator[](const std::string& key);
    const JsonValue& operator[](const std::string& key) const;

    void setPrintIndentLevel(int level);

    friend std::istream& operator>>(std::istream& in, JsonObject& self);
    friend std::ostream& operator<<(std::ostream& out, const JsonObject& self);

private:
     std::map<std::string, JsonValue> valueMap;
     int indentLevel = 1;
};

