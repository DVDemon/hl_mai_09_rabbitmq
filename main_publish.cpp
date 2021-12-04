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
        //if(handler.connected())
        for(size_t i=0;i<1000;++i)
        {
            std::string msg = "Hello world:";
            msg+=std::to_string(i);
            channel.publish("", "hello", msg.c_str());
            std::cout << " [x] Sent " << msg << std::endl;
           
        }
        handler.quit();
    });


    while(true) handler.loop();
    return 0;
}