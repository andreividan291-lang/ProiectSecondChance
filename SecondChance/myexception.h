#include <exception>
#include <string>

class MyException : public std::exception
{
private:
    std::string message;

public:
    // Constructor cu mesaj
    explicit MyException(const std::string& msg) : message(msg) {}

    // Funcția what() override
    virtual const char* what() const noexcept override {
        return message.c_str();
    }
};
