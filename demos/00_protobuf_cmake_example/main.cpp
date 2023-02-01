#include <iostream>

#include "message.pb.h"

class FormatTest {
public:
    FormatTest(const std::string name) : name_(name) {}
    ~FormatTest(){};

private:
    std::string name_;
};

int a = 1;
int b = 2;

int main(int argc, char const *argv[]) {
    message::Message m;
    std::cout << "Hello Proto!" << std::endl;

    return 0;
}
