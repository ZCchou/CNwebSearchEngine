#include "../Include/EchoServer.h"
#include <iostream>

using std::cout;
using std::endl;


void test()
{
    EchoServer server(4, 10, "127.0.0.1", 8888);

    server.start();
}

int main(int argc, char **argv)
{
    test();
    return 0;
}

