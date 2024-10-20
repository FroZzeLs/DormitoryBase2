#pragma once
#include <exception>
#include <string>

class DatabaseException : public std::exception {
private:
    std::string message;

public:
    explicit DatabaseException(const std::string& msg);

    const char* what() const noexcept override;
};