#include "JsonArray.h"

#include "JsonObject.h"

JsonValue& JsonArray::operator[](int index)
{
    return valuesVec.at(index);
}

const JsonValue& JsonArray::operator[](int index) const
{
    return valuesVec.at(index);
}

std::vector<JsonValue>& JsonArray::values()
{
    return valuesVec;
}

const std::vector<JsonValue>& JsonArray::values() const
{
    return valuesVec;
}

void JsonArray::setPrintIndentLevel(int level)
{
    indentLevel = level;
}

std::istream& operator>>(std::istream& in, JsonArray& self)
{
    in >> std::ws;
    if (in.get() != '[') {
        throw std::runtime_error("Input is not a json array");
    }
    in >> std::ws;
    if (in.peek() == ']') {
        in.get();
        return in;
    }

    char endChar = 0;
    while (in && endChar != ']') {
        JsonValue value;
        in >> value >> endChar >> std::ws;

        self.valuesVec.push_back(value);
    }

    return in;
};

std::ostream& operator<<(std::ostream& out, const JsonArray& self)
{
    if (self.valuesVec.empty()) {
        out << "[]";
        return out;
    }

    bool firstElement = true;

    out << "[\n";
    for (const JsonValue& value : self.valuesVec) {
        if (!firstElement) {
            out << ",\n";
        }

        for (int i = 0; i < self.indentLevel; ++i) {
            out << "    ";
        }

        JsonValue valueCopy = value;
        if (valueCopy.isObject()) {
            valueCopy.asObject().setPrintIndentLevel(self.indentLevel + 1);
        } else if (valueCopy.isArray()) {
            valueCopy.asArray().setPrintIndentLevel(self.indentLevel + 1);
        }
        out << valueCopy;

        firstElement = false;
    }

    out << '\n';
    for (int i = 0; i < self.indentLevel - 1; ++i) {
        out << "    ";
    }
    out << ']';

    return out;
}

