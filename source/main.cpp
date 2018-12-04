#include <iostream>
#include <map>

#include "communication/BU67103x.h"
#include "communication/AceBCMessage.h"
#include "communication/AceDevice.h"
#include "loader/ConfigLoader.h"
#include "loader/BcMessageLoader.h"
	

int main()
{
	std::cout<<" ============================================================"<<std::endl;
    std::cout<<"|                     SIM-GENERATOR v0.1                     |"<<std::endl;
    std::cout<<" ============================================================"<<std::endl;


    BU67103x *device = new BU67103x();

    ConfigLoader configLoader("config.xml");
    AceDevice aceConfig = configLoader.load();

	BcMessageLoader messageLoader("bc_message.xml");
	std::map<short,AceBCMessage> messages = messageLoader.load();

	
    device->initialize(aceConfig);
    device->configure(aceConfig, messages);
    device->deInitialize();

/*
	for(auto it = messages.begin(); it != messages.end(); ++it)
	{
   		std::cout << "=====================================================================" <<std::endl;
		std::cout << "pKey: "<<it->second.getKey() << "Key: "<< it->first<<std::endl;
	    std::cout << "Name: "<<it->second.getName() <<std::endl;
	    std::cout << "MessageType: "<<it->second.getMessageType() <<std::endl;
	    std::cout << "SyncType: "<<it->second.getSyncType() <<std::endl;
	    std::cout << "Frequency: "<<it->second.getFrequency() <<std::endl;
	    std::cout << "RemoteTerminal: "<<it->second.getRemoteTerminal() <<std::endl;
	    std::cout << "SubAddress: "<<it->second.getSubAddress() <<std::endl;			    
	    std::cout << "WordCount: "<<it->second.getWordCount() <<std::endl;
	    std::cout << "MessageGapTime: "<<it->second.getMessageGapTime() <<std::endl;
	    std::cout << "MessageOptions: "<<it->second.getMessageOptions() <<std::endl;
	    std::cout << "=====================================================================" <<std::endl;	    	      	
	}
*/
    
/*
   BU67103x *device = new BU67103x();
   device->initialize(aceConfig);
   device->configure();
   device->deInitialize();
*/	

   /*
   std::map<short, aceBCMessage> mMessageMap;
   
   aceBCMessage msg1(MessageType::BCtoRT, SyncType::SYNC,0,0,0,17,1,1,0,0);
   aceBCMessage msg2(MessageType::BCtoRT, SyncType::SYNC,0,0,0,17,2,2,0,0);
   aceBCMessage msg3(MessageType::BCtoRT, SyncType::SYNC,0,0,0,17,31,31,0,0);

   mMessageMap.insert(std::pair<short, aceBCMessage>(msg1.getKey(), msg1));

   for(auto it = mMessageMap.begin(); it != mMessageMap.end(); ++it)
   {
      std::cout << it->first << " " << it->second.getRemoteTerminal() << std::endl;
   }

   


	*/
   return 0;
}
