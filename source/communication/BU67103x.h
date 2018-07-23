#ifndef BU67103X_H
#define BU67103X_H

#include "c1553Device.h"


class BU67103x : public c1553Device
{
public:
   BU67103x();
   ~BU67103x();
   void initialize();
   void deInitialize();
   void configure();
   void start();
   void stop();
   void read();
   void write();

};

#endif
