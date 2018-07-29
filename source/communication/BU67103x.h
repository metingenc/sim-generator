#ifndef BU67103X_H
#define BU67103X_H

#include "c1553Device.h"
#include <string>
#include <stdemace.h>

struct LibVersion
{
	LibVersion(int majorValue, int minorValue, int developmentValue):
	 major(0), 
	 minor(0),
	 development(0)
	{
		major = majorValue;
		minor = minorValue;
		development = developmentValue;
	}

	int major;
	int minor;
	int development;	
};

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
   void show(const std::string text);
   
 private:
  	void getVersion(void);	
  	void getError(S16BIT nResult);
	struct LibVersion mLibVersion;
  	


};

#endif
