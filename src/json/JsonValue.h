#pragma once

#include <variant>
#include <string>

class JsonObject;
class JsonArray;

class JsonValue
{
public:
    JsonValue();
    ~JsonValue();

    JsonValue(const JsonValue& other);

    template<typename T>
    JsonValue(const T& val) :
        value(val)
    {}
    JsonValue(const JsonObject& obj);
    JsonValue(const JsonArray& array);

    JsonValue& operator=(JsonValue other);

    const std::string& asString() const;
    int asInt() const;
    float asFloat() const;
    bool asBool() const;
    bool isNull() const;

    JsonObject& asObject();
    const JsonObject& asObject() const;
    bool isObject() const;

    JsonArray& asArray();
    const JsonArray& asArray() const;
    bool isArray() const;

    friend std::istream& operator>>(std::istream& in, JsonValue& self);
    friend std::ostream& operator<<(std::ostream& out, const JsonValue& self);

private:
    std::variant<std::string, std::monostate,
                 int, float, bool,
                 JsonObject*, JsonArray*> value;

    static JsonValue parsePrimitive(const std::string& str);

    static bool isInteger(const std::string& str);
    static bool isFloat(const std::string& str);

    friend void swap(JsonValue& first, JsonValue& second);
};

