#include "JsonObject.h"

#include "JsonValue.h"
#include "JsonArray.h"

JsonValue& JsonObject::operator[](const std::string& key)
{
    return valueMap[key];
}

const JsonValue& JsonObject::operator[](const std::string& key) const
{
    return valueMap.at(key);
}

void JsonObject::setPrintIndentLevel(int level)
{
    indentLevel = level;
}

std::istream& operator>>(std::istream& in, JsonObject& obj)
{
    in >> std::ws;
    if (in.get() != '{') {
        throw std::runtime_error("Input is not a json object");
    }
    in >> std::ws;
    if (in.peek() == '}') {
        in.get();
        return in;
    }

    std::string key;    
    JsonValue value;

    char endChar = 0;
    while (in && endChar != '}') {
        in >> std::ws;
        in.ignore();
        std::getline(in, key, '"');

        in >> std::ws;
        in.ignore();

        in >> value >> endChar;

        obj.valueMap[key] = value;
    }

    return in;
}

std::ostream& operator<<(std::ostream& out, const JsonObject& self)
{
    if (self.valueMap.empty()) {
        out << "{}";
        return out;
    }

    bool firstPair = true;

    out << "{\n";
    for (const auto& pair : self.valueMap) {
        if (!firstPair) {
            out << ",\n";
        }

        for (int i = 0; i < self.indentLevel; ++i) {
            out << "    ";
        }
        out << '"' << pair.first << "\" : ";

        JsonValue value = pair.second;
        if (value.isObject()) {
            value.asObject().setPrintIndentLevel(self.indentLevel + 1);
        } else if (value.isArray()) {
            value.asArray().setPrintIndentLevel(self.indentLevel + 1);
        }
        out << value;

        firstPair = false;
    }

    out << '\n';
    for (int i = 0; i < self.indentLevel - 1; ++i) {
        out << "    ";
    }
    out << '}';

    return out;
}
