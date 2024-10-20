#pragma once
#include <stdexcept>
#include <string>

class StudentSearchException : public std::runtime_error {
public:
    explicit StudentSearchException(const std::string& message);
};