#include <iostream>
#include "Communication/BU67103x.h"


int main()
{
   std::cout<<"Hello, sim-generator"<<std::endl;

   c1553Device *device = new BU67103x();
   device->initialize();


   return 0;
}
