#include "DatabaseException.h"

DatabaseException::DatabaseException(const std::string& msg) : message(msg) {}

const char* DatabaseException::what() const noexcept {
    return message.c_str();
}