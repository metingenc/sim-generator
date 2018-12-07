#include <iostream>
#include <map>
#include <string>

#include "communication/BU67103x.h"
#include "communication/AceBCMessage.h"
#include "communication/AceDevice.h"
#include "loader/ConfigLoader.h"
#include "loader/BcMessageLoader.h"
#include "loader/TestCaseLoader.h"
	

int main()
{
	  std::cout<<" ============================================================"<<std::endl;
    std::cout<<"|                     SIM-GENERATOR v0.1                     |"<<std::endl;
    std::cout<<" ============================================================"<<std::endl;


    

    ConfigLoader configLoader("config.xml");
    AceDevice aceConfig = configLoader.load();

	  BcMessageLoader messageLoader("bc_message.xml");
	  std::map<short,AceBCMessage> messages = messageLoader.load();

    TestCaseLoader testCaseLoader("TestCase1.xml");

    BU67103x *device = new BU67103x(aceConfig, messages);

    std::string cmd = "help";
    while(cmd != "exit")
    {
      std::cout<<"\n$ ";
      std::cin>>cmd;
      
      if( cmd == "init")
      {
        device->initialize();
      }
      else if(cmd == "config")
      {
        device->configure();
      }
      else if( cmd == "start")
      {
        device->start();
      }
      else if( cmd == "stop")
      {
        device->stop();
      }
      else if( cmd == "free")
      {
        device->deInitialize();
      }
      else if( cmd == "exit")
      {
        device->deInitialize();
      }
      else if( cmd == "run")
      {
        device->initialize();
        device->configure();
        device->start();        
      }
      else if( cmd == "write")
      { 
        for(auto it = messages.begin(); it != messages.end(); ++it)    
        {
          std::cout<<"X "<<it->second.getBuffer()<<std::endl;
          device->write(it->second);
          break;
        }   
          
      }
      else if( cmd == "help")
      {  
         std::cout<<"\t[init]  \tInitializes hardware resources."<<std::endl;            
         std::cout<<"\t[config]\tConfigures the Bus Controller operation."<<std::endl;
         std::cout<<"\t[start] \tStart the BC."<<std::endl;
         std::cout<<"\t[stop]  \tThis function stops the BC."<<std::endl;
         std::cout<<"\t[free]  \tFrees all resources used by the hardware."<<std::endl;
         std::cout<<"\t[exit]  \tExit."<<std::endl;         
      }
      else
      {
         std::cout<<"Undefined command. Use [help] for comamnd list"<<std::endl;        
      }
    }

   return 0;
}
