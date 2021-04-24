#include <iostream>

#include "SimplePocoHandler.h"

// https://habr.com/ru/post/253317/

int main(void)
{
    SimplePocoHandler handler("localhost", 5672);

    AMQP::Connection connection(&handler, AMQP::Login("guest", "guest"), "/");
    AMQP::Channel channel(&connection);

    channel.onReady([&]()
    {
        std::cout << "ready" << std::endl;
        if(handler.connected())
        {
            channel.publish("", "hello", "Hello World!");
            std::cout << " [x] Sent 'Hello World!'" << std::endl;
            handler.quit();
        }
    });


    handler.loop();
    return 0;
}