#pragma once

#include <string>

struct SourceCodeTag {};
struct FileNameTag {};

template <typename Tag>
class StrongString {
public:
    explicit StrongString(const std::string& str) : value(str) {}
    explicit StrongString(std::string&& str) : value(std::move(str)) {}
    explicit StrongString(const char* str) : value(str) {}

    // Opérateurs de comparaison
    bool operator==(const StrongString& other) const { return value == other.value; }
    bool operator!=(const StrongString& other) const { return value != other.value; }
    bool operator<(const StrongString& other) const { return value < other.value; }
    bool operator<=(const StrongString& other) const { return value <= other.value; }
    bool operator>(const StrongString& other) const { return value > other.value; }
    bool operator>=(const StrongString& other) const { return value >= other.value; }

    operator std::string() const { return value; }

    const std::string& get() const { return value; }
    const char* data() const { return value.data(); }

private:
    std::string value;
};

using SourceCodeString = StrongString<SourceCodeTag>;
using FileNameString = StrongString<FileNameTag>;
