#include "StudentSearchException.h"

StudentSearchException::StudentSearchException(const std::string& message)
    : std::runtime_error(message) {}