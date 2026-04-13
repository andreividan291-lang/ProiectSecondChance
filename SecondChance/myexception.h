#include <exception>
#include <string>

class MyException : public std::exception
{
private:
    std::string message;

public:

    explicit MyException(const std::string& msg) : message(msg) {}

    virtual const char* what() const noexcept override { return message.c_str(); }
};
