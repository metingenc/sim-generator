#include <iostream>
#include <map>
#include <string>

#include "communication/BU67103x.h"
#include "communication/AceBCMessage.h"
#include "communication/AceDevice.h"
#include "communication/AceTestMessage.h"
#include "loader/ConfigLoader.h"
#include "loader/BcMessageLoader.h"
#include "loader/TestCaseLoader.h"

	

int main()
{
	  std::cout<<" ============================================================"<<std::endl;
    std::cout<<"|                     SIM-GENERATOR v0.1                     |"<<std::endl;
    std::cout<<" ============================================================"<<std::endl;    

    AceDevice aceConfig;
    std::map<short,AceBCMessage> messages;
    std::vector<AceTestMessage> testMessages;

    std::string configPath = "jhm_config.xml";  
    std::string messagePath = "jhm_idd.xml";
    std::string testMessagePath = "jhm_test.xml";  
   
    BU67103x device(aceConfig, messages);

    std::string cmd = "help";
    while(cmd != "exit")
    {
      std::cout<<"\n$ ";
      std::cin>>cmd;

      if( cmd == "load")
      {
         std::cout<<"Enter Config File: ";
         std::cin>>configPath;
         ConfigLoader configLoader(configPath);
         aceConfig = configLoader.load();
         std::cout<<"Enter IDD File: ";
         std::cin>>messagePath;
         BcMessageLoader messageLoader(messagePath);
         messages = messageLoader.load();
         std::cout<<"Enter Test File: ";
         std::cin>>testMessagePath;
         TestCaseLoader testCaseLoader(testMessagePath);
         testMessages = testCaseLoader.load();
      }      
      else if( cmd == "init")
      {
        device.initialize();
      }
      else if(cmd == "config")
      {
        device.configure();
      }
      else if( cmd == "start")
      {
        device.start();
      }
      else if( cmd == "stop")
      {
        device.stop();
      }
      else if( cmd == "free")
      {
        device.deInitialize();
      }
      else if( cmd == "exit")
      {
        device.deInitialize();
      }
      else if( cmd == "run")
      { 
        ConfigLoader configLoader(configPath);
        aceConfig = configLoader.load();
        BcMessageLoader messageLoader(messagePath);
        messages = messageLoader.load();
        TestCaseLoader testCaseLoader(testMessagePath);
        testMessages = testCaseLoader.load();

        device.initialize();
        device.configure();
        device.start();        
        device.write(testMessages); 
      }
      else if( cmd == "write")
      {                   
          device.write(testMessages);
      }
      else if( cmd == "help")
      {  
         std::cout<<"\tCommand  \tDefinition"<<std::endl;            
         std::cout<<"\t======================================================="<<std::endl;            
         std::cout<<"\t[load]  \tLoads configuration files."<<std::endl;            
         std::cout<<"\t[init]  \tInitializes hardware resources."<<std::endl;            
         std::cout<<"\t[config]\tConfigures the Bus Controller operation."<<std::endl;
         std::cout<<"\t[start] \tStarts the BC."<<std::endl;
         std::cout<<"\t[write] \tWrites test data from test files to the bus."<<std::endl;
         std::cout<<"\t[stop]  \tStops the BC."<<std::endl;
         std::cout<<"\t[free]  \tFrees all resources used by the hardware."<<std::endl;
         std::cout<<"\t[run]   \tRuns program with default values."<<std::endl;
         std::cout<<"\t[exit]  \tExit."<<std::endl;         
      }
      else
      {
         std::cout<<"Undefined command. Use [help] for comamnd list"<<std::endl;        
      }
    }

   return 0;
}
