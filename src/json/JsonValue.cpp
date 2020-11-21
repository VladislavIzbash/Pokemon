#include "JsonValue.h"

#include "JsonObject.h"
#include "JsonArray.h"

#include <algorithm>

JsonValue::JsonValue() :
    value(std::monostate())
{}

JsonValue::JsonValue(const JsonObject& obj) :
    value(new JsonObject(obj))
{}

JsonValue::JsonValue(const JsonArray& array) :
    value(new JsonArray(array))
{}

JsonValue::JsonValue(const JsonValue& other) :
    value(other.value)
{
    if (other.isObject()) {
        std::get<JsonObject*>(value) = new JsonObject(other.asObject());
    } else if (other.isArray()) {
        std::get<JsonArray*>(value) = new JsonArray(other.asArray());
    }
}

JsonValue& JsonValue::operator=(JsonValue other)
{
    swap(*this, other);

    return *this;
}

const std::string& JsonValue::asString() const
{
    return std::get<std::string>(value);
}

int JsonValue::asInt() const
{
    return std::get<int>(value);
}

float JsonValue::asFloat() const
{
    return std::get<float>(value);
}

bool JsonValue::asBool() const
{
    return std::get<bool>(value);
}

bool JsonValue::isNull() const
{
    return std::holds_alternative<std::monostate>(value);
}

JsonObject& JsonValue::asObject()
{
    return *std::get<JsonObject*>(value);
}

const JsonObject& JsonValue::asObject() const
{
    return *std::get<JsonObject*>(value);
}

JsonArray& JsonValue::asArray()
{
    return *std::get<JsonArray*>(value);
}

const JsonArray& JsonValue::asArray() const
{
    return *std::get<JsonArray*>(value);
}

bool JsonValue::isObject() const
{
    return std::holds_alternative<JsonObject*>(value);
}

bool JsonValue::isArray() const
{
    return std::holds_alternative<JsonArray*>(value);
}

JsonValue::~JsonValue()
{
    if (isObject()) {
        delete std::get<JsonObject*>(value);
    } else if (isArray()) {
        delete std::get<JsonArray*>(value);
    }
}

void swap(JsonValue& first, JsonValue& second)
{
    std::swap(first.value, second.value);
}

std::istream& operator>>(std::istream& in, JsonValue& self)
{
    std::string valStr;

    in >> std::ws;
    char nextChar = in.peek();

    if (nextChar == '"') {
        in.ignore();
        std::getline(in, valStr, '"');

        self = JsonValue::parsePrimitive('"' + valStr + '"');

    } else if (nextChar == '{') {
        JsonObject* obj = new JsonObject();
        in >> *obj;
        self = obj;

    } else if (nextChar == '[') {
        JsonArray* array = new JsonArray();
        in >> *array;
        self = array;

    } else {
        char curChar;
        while (in && nextChar != '}' && nextChar != ']' && nextChar != ',') {
            in >> curChar;
            valStr += curChar;

            in >> std::ws;
            nextChar = in.peek();
        }

        self = JsonValue::parsePrimitive(valStr);
    }

    return in;
}

std::ostream& operator<<(std::ostream& out, const JsonValue& self)
{
    if (std::holds_alternative<std::string>(self.value)) {
        out << '"' << self.asString() << '"';
    } else if (std::holds_alternative<int>(self.value)) {
        out << self.asInt();
    } else if (std::holds_alternative<float>(self.value)) {
        out << self.asFloat();
    } else if (std::holds_alternative<bool>(self.value)) {
        out << (self.asBool() ? "true" : "false");
    } else if (std::holds_alternative<std::monostate>(self.value)) {
        out << "null";
    } else if (self.isObject()) {
        out << self.asObject();
    } else if (self.isArray()) {
        out << self.asArray();
    }

    return out;
}

JsonValue JsonValue::parsePrimitive(const std::string& str)
{
    JsonValue json;

    if (str[0] == '"') {
        json.value = str.substr(1, str.length() - 2);
    } else if (isInteger(str)) {
        json.value = std::stoi(str);
    } else if (isFloat(str)) {
        json.value = std::stof(str);
    } else if (str == "true") {
        json.value = true;
    } else if (str == "false") {
        json.value = false;
    } else if (str == "null") {
        json.value = std::monostate();
    } else {
        throw std::runtime_error("Cannot parse json value (" + str + ")");
    }

    return json;
}

bool JsonValue::isInteger(const std::string& str)
{
    return std::all_of(str.begin(), str.end(), isdigit);
}

bool JsonValue::isFloat(const std::string& str)
{
    return std::all_of(str.begin(), str.end(), [](char ch) {
        return isdigit(ch) || ch == '.';
    });
}
