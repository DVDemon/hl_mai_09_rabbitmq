#include <iostream>
#include "SimplePocoHandler.h"


int main(void)
{
    SimplePocoHandler handler("localhost", 5672);

    AMQP::Connection connection(&handler, AMQP::Login("guest", "guest"), "/");

    AMQP::Channel channel(&connection);
    channel.declareQueue("hello");
    channel.consume("hello", AMQP::noack).onReceived([](const AMQP::Message &message, [[maybe_unused]] uint64_t deliveryTag, [[maybe_unused]] bool redelivered)
                                                     {
                std::string msg;
                for(size_t i=0;i<message.bodySize();++i) msg+=message.body()[i];
                std::cout <<" [x] Received ["<<msg << "]," << message.bodySize() << std::endl; 
                });

    std::cout << " [*] Waiting for messages. To exit press CTRL-C\n";
    while (true)
        handler.loop();
    return 0;
}