#include <iostream>
#include "SimplePocoHandler.h"

// https://habr.com/ru/post/253317/

int main(void)
{
    SimplePocoHandler handler("localhost", 5672);

    AMQP::Connection connection(&handler, AMQP::Login("guest", "guest"), "/");

    AMQP::Channel channel(&connection);
    channel.declareQueue("hello");
    channel.consume("hello", AMQP::noack).onReceived(
            [](const AMQP::Message &message,
                       [[maybe_unused]] uint64_t deliveryTag,
                       [[maybe_unused]] bool redelivered)
            {

                std::cout <<" [x] Received "<<message.body() << std::endl;
            });

    std::cout << " [*] Waiting for messages. To exit press CTRL-C\n";
    handler.loop();
    return 0;
}