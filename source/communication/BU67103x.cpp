#include "BU67103x.h"
#include <iostream>

BU67103x::BU67103x()
{

}

BU67103x::~BU67103x()
{

}

void BU67103x::initialize()
{
   std::cout << "BU67103x is initializing" << std::endl;
}

void BU67103x::deInitialize()
{
   std::cout << "BU67103x is deInitializing" << std::endl;
}

void BU67103x::configure()
{
   std::cout << "BU67103x is configuring" << std::endl;
}

void BU67103x::start()
{
   std::cout << "BU67103x is starting" << std::endl;
}

void BU67103x::stop()
{
   std::cout << "BU67103x is stoping" << std::endl;
}

void BU67103x::read()
{
   std::cout << "BU67103x is reading" << std::endl;
}

void BU67103x::write()
{
   std::cout << "BU67103x is writing" << std::endl;
}


