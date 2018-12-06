#ifndef BU67103X_H
#define BU67103X_H

#include <string>
#include <stdemace.h>
#include <map>
#include <vector>

#include "c1553Device.h"
#include "AceBCMessage.h"
#include "AceDevice.h"

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
   void initialize(AceDevice aceConfig, std::map<short,AceBCMessage> messages);
   void initialize();
   void deInitialize();   
   void configure();   
   void start();   
   void stop();
   void read();
   void write();
   void show(const std::string text);
   
 private:
    bool mIsInitialized;
    bool mIsConfigurated;
    bool mIsStarted;
  	void getVersion(void);	
  	void getError(S16BIT nResult);
	  struct LibVersion mLibVersion;

    AceDevice mConfig;
    std::map<short,AceBCMessage> mMessages;

    void createBCObjects();
    short getGCD(short a, short b); 
    short getGCD(std::vector<short> list); 
    short getLCM(std::vector<short> list);

};

#endif
