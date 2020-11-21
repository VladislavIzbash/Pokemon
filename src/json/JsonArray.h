#pragma once

#include "JsonValue.h"

#include <vector>
#include <iostream>

class JsonArray
{
public:
    JsonValue& operator[](int index);
    const JsonValue& operator[](int index) const;

    std::vector<JsonValue>& values();
    const std::vector<JsonValue>& values() const;

    void setPrintIndentLevel(int level);

    friend std::istream& operator>>(std::istream& in, JsonArray& self);
    friend std::ostream& operator<<(std::ostream& out, const JsonArray& self);

private:
    std::vector<JsonValue> valuesVec;
    int indentLevel = 1;
};

