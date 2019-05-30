#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

#include "Controller.h"
#include "Brushless.h"

#include "Publisher.h"
#include "Subscriber.h"

#include "PolitoceanConstants.h"

using namespace Politocean;
using namespace Politocean::RPi;

/***********************************************************************************
 * Listener class for subscriber
***********************************************************************************/

class Listener
{
    std::string action_;
    int velocity_;

    bool updated_;
public:
    Listener() : updated_(false) {}

    void listen(const std::string& payload, const std::string& topic);

    std::string action();
    int velocity();

    bool isUpdated();
};

void Listener::listen(const std::string& payload, const std::string& topic)
{
    if (topic == Constants::Topics::MICROROV_COMMANDS)
    {
        updated_ = true;
        if (payload == Constants::Commands::Actions::START)
            action_ = Constants::Commands::Actions::START;
        else if (payload == Constants::Commands::Actions::STOP)
            action_ = Constants::Commands::Actions::STOP;
        else
            action_ = Constants::Commands::Actions::NONE;

        updated_ = true;
    }
    else if (topic == Constants::Topics::MICROROV_VELOCITY)
        try
        {
            velocity_ = std::stoi(payload);
            updated_ = true;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    else return ;
}

std::string Listener::action()
{
    return action_;
}

int Listener::velocity()
{
    return velocity_;
}

bool Listener::isUpdated()
{
    return updated_;
}

/***********************************************************************************
 * Talker class for publisher
***********************************************************************************/

class Talker
{

};

int main(int argc, const char *argv[])
{
    Subscriber subscriber(Constants::MicroRov::IP_ADDRESS, Constants::MicroRov::MICRO_ROV_ID);
    Listener listener;

    subscriber.subscribeTo(Constants::Topics::MICROROV+"#", &Listener::listen, &listener);

    // Try to connect to the subscriber
    try
    {
        subscriber.connect();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    Publisher publisher(Constants::MicroRov::IP_ADDRESS, Constants::MicroRov::MICRO_ROV_ID);
    Talker talker;

    Controller controller;

    // Try to setup the controller
    try
    {
        controller.setup();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    while (subscriber.is_connected())
    {
        if (listener.isUpdated())
        {

        }
    }
}