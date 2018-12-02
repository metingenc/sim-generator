#include <iostream>
#include <map>
#include "BU67103x.h"
#include "config.h"


BU67103x::BU67103x() : mIsInitialized(false), mIsConfigurated(false), mLibVersion(0,0,0)
{
  getVersion();
}

BU67103x::~BU67103x()
{

}

void BU67103x::initialize()
{

}

void BU67103x::initialize(AceDevice device)
{ 
	S16BIT wResult = 0x0000;	

  std::cout << "\tBU67103x is initializing...";  
	
	wResult = aceInitialize(device.getDeviceNumber(),device.getAccess(),device.getMode(),device.getMemoryWordSize(),device.getRegisterAddress(),device.getDeviceMemoryAddres());
	
  if(ACE_ERR_SUCCESS != wResult)
	{
  		getError(wResult);  		
	}  
	else
	{
    mIsInitialized = true;
    std::cout <<"\r[OK]"<<std::endl;
		std::cout<<"[OK]\tBU67103x is initialized."<<std::endl;
		std::cout<<"\tLDN:\t" + std::to_string(device.getDeviceNumber())<<std::endl;
		std::cout<<"\tAccess:\t" + std::to_string(device.getAccess())<<std::endl;
		std::cout<<"\tMode:\t" + std::to_string(device.getMode())<<std::endl;
	}  
}

void BU67103x::deInitialize()
{

}

void BU67103x::deInitialize(AceDevice device)
{
   S16BIT wResult = 0x0000;

   show("BU67103x is deInitializing");

   wResult = aceFree(device.getDeviceNumber());
   if(ACE_ERR_SUCCESS != wResult)
   {
   	  getError(wResult);
   }
   else
   {
      mIsInitialized = false;
    	show("BU67103x is deinitialized successfully: ");
    	show("LDN: " + std::to_string(device.getDeviceNumber()));
   }

}

void BU67103x::configure()
{

}

void BU67103x::configure(AceDevice device, std::map<short, AceBCMessage> messages)
{
  S16BIT wResult = 0x0000;

  if (!mIsInitialized)
  {
      std::cout<<"[WARN]\tBefore you configure, device must be initialized."<<std::endl;
      return;
  }    
  
  std::cout<<"\tBU67103x is configuring..."; 

  wResult = aceBCConfigure(device.getDeviceNumber(), device.getBcConfigureOptions());

   if(ACE_ERR_SUCCESS != wResult)
   {
      mIsConfigurated = false;
      getError(wResult);
   }
   else
   {
      mIsConfigurated = true;
      std::cout<<"\r[OK]"<<std::endl;
      std::cout<<"\tOptions: "<<device.getBcConfigureOptions()<<std::endl;
   }

   createBCObjects(device, messages);
}

void BU67103x::createBCObjects(AceDevice device, std::map<short, AceBCMessage> messages)
{
  unsigned short wBuffer[32] =  { 0x0000,0x1111,0x2222,0x3333,0x4444,0x5555,0x6666,0x7777,
                                  0x8888,0x9999,0xAAAA,0xBBBB,0xCCCC,0xDDDD,0xEEEE,0XFFFF,
                                  0x0000,0x1111,0x2222,0x3333,0x4444,0x5555,0x6666,0x7777,
                                  0x8888,0x9999,0xAAAA,0xBBBB,0xCCCC,0xDDDD,0xEEEE,0XFFFF};

  S16BIT wResult;
  
  if (!mIsConfigurated)
  {
      std::cout<<"[WARN]\tBefore you create objects, device must be configurated."<<std::endl;
      return;
  } 

  
  // # Step1 Creating BC Data Blocks=======================================================================  

  std::cout<<"\tBC data blocks are creating..."<<std::endl;

  for(auto it = messages.begin(); it != messages.end(); ++it)
  {    
    if(SyncType::SYNC == it->second.getSyncType())
    {
      wResult = aceBCDataBlkCreate(device.getDeviceNumber(), it->first, ACE_BC_DBLK_SINGLE, wBuffer, 32); 

      if(ACE_ERR_SUCCESS != wResult)
      {
         getError(wResult);
         std::cout<<"\t"<<it->first<<"\t"<<it->second.getName()<<" bc data creation failed.\n" <<std::endl;
         return;
      }
      else
      {
        std::cout<<"\r[OK]\t"<<it->first<<"\t"<<it->second.getName()<<" bc data block creation succeeded." <<std::endl;     
      }       
    }
      
  }    
  // ======================================================================================================

  // # Step2 Creating Message Blocks ======================================================================
  
  std::cout<<"\tBC message blocks are creating..."<<std::endl;
  
  for(auto it = messages.begin(); it != messages.end(); ++it)
  {  

    if(MessageType::BCtoRT == it->second.getMessageType())  
    {
        if(SyncType::SYNC == it->second.getSyncType())
        {
          wResult = aceBCMsgCreateBCtoRT(device.getDeviceNumber(), 
                                         it->first,
                                         it->first,
                                         it->second.getRemoteTerminal(),
                                         it->second.getSubAddress(),
                                         it->second.getWordCount(),
                                         it->second.getMessageGapTime(),
                                         it->second.getMessageOptions());

          if(ACE_ERR_SUCCESS != wResult)
          {
            getError(wResult);
            std::cout<<"\t"<<it->first<<"\t"<<it->second.getName()<<" bc to rt message block creation failed." <<std::endl;
            return;
          }
          else
          {
            std::cout<<"[OK]\t"<<it->first<<"\t"<<it->second.getName()<<" bc to rt message block creation succeeded." <<std::endl;     
          }
        }
        else if(SyncType::ASYNC == it->second.getSyncType())
        {
            wResult = aceBCAsyncMsgCreateBCtoRT(device.getDeviceNumber(), 
                                                it->first,
                                                it->first,
                                                it->second.getRemoteTerminal(),
                                                it->second.getSubAddress(),
                                                it->second.getWordCount(),
                                                it->second.getMessageGapTime(),
                                                it->second.getMessageOptions(),
                                                wBuffer
                                                );

            if(ACE_ERR_SUCCESS != wResult)
            {
               getError(wResult);
               std::cout<<"\t"<<it->first<<"\t"<<it->second.getName()<<" bc to rt async message block creation failed: " <<std::endl;               
               return;
            }
            else
            {
              std::cout<<"[OK]\t"<<it->first<<"\t"<<it->second.getName()<<" bc to rt async message block creation succeeded." <<std::endl;     
            }                    
        }
        else
        {
          std::cout<<"Error: Unsupported sync type: " <<it->second.getMessageType()<<std::endl;
        }
    }
    else if(MessageType::RTtoBC == it->second.getMessageType())
    {
        if(SyncType::SYNC == it->second.getSyncType())
        {
          wResult = aceBCMsgCreateRTtoBC(device.getDeviceNumber(), 
                                         it->first,
                                         it->first,
                                         it->second.getRemoteTerminal(),
                                         it->second.getSubAddress(),
                                         it->second.getWordCount(),
                                         it->second.getMessageGapTime(),
                                         it->second.getMessageOptions());

          if(ACE_ERR_SUCCESS != wResult)
          {
             getError(wResult);
             std::cout<<"\t"<<it->first<<"\t"<<it->second.getName()<<" rt to bc message block creation failed: " <<std::endl;
             return;
          }
          else
          {
            std::cout<<"[OK]\t"<<it->first<<"\t"<<it->second.getName()<<" rt to bc message block creation succeeded." <<std::endl;     
          }
        }
        else if(SyncType::ASYNC == it->second.getSyncType())
        {
            wResult = aceBCAsyncMsgCreateRTtoBC(device.getDeviceNumber(), 
                                                it->first,
                                                it->first,
                                                it->second.getRemoteTerminal(),
                                                it->second.getSubAddress(),
                                                it->second.getWordCount(),
                                                it->second.getMessageGapTime(),
                                                it->second.getMessageOptions(),
                                                wBuffer
                                                );

            if(ACE_ERR_SUCCESS != wResult)
            {
               getError(wResult);
               std::cout<<"\t"<<it->first<<"\t"<<it->second.getName()<<" rt to bc async message block creation failed: " <<std::endl;
               return;
            }
            else
            {
              std::cout<<"[OK]\t"<<it->first<<"\t"<<it->second.getName()<<" rt to bc async message block created succesfully." <<std::endl;     
            }           
        }
        else
        {
          std::cout<<"Error: Unsupported sync type: " <<it->second.getMessageType()<<std::endl;
        }
    }
    else
    {
      std::cout<<"Error: Unsupported message type: " <<it->second.getMessageType()<<std::endl;
    }
  
  }

  // ======================================================================================================

  //  #Step3 Building BC Frames =================================
     // Creating Message Opcodes
        // aceBCOpCodeCreate()
     // Creating Minor Frame Opcodes
        // aceBCOpCodeCreate : ACE_OPCODE_CAL
     // Creating BC Major Frames
        // aceBCFrameCreate()
   // ===========================================================  

   // #STEP4 Creating Host Buffer ================================  
       // aceBCInstallHBuf()
   // ===========================================================       
   
   // aceBCOpCodeCreate() ACE_OPCODE_XEQ
   // aceBCFrameCreate() ACE_FRAME_MINOR
   // aceBCOpcodeCreate() ACE_OPCODE_CAL
   // aceBCFrameCreate() ACE_FRAME_MAJOR
}

void BU67103x::start()
{
   show("BU67103x is starting");
   // aceBCStart()
}

void BU67103x::stop()
{
   show("BU67103x is stoping");
   // aceBCStop()
}

void BU67103x::read()
{
   show("BU67103x is reading");
   // aceBCGetHBufMsgDecoded()
   // aceBCDataBlkRead()
}

void BU67103x::write()
{
   show("BU67103x is writing");
   // aceBCDataBlkWrite()
   // aceBCSendAsyncMsgHP()
}

void BU67103x::show(const std::string text)
{
	std::cout << text << std::endl;
  std::cout<< "================================================"<<std::endl;
}

/*******************************************************************************
 * Name:    PrintHeader
 *
 * Description:
 *
 *      Prints the sample program header.
 *
 * In   none
 * Out  none
 ******************************************************************************/

void BU67103x::getVersion(void)
{
    U16BIT wLibVer;
    std::string version = ""; 

    wLibVer = aceGetLibVersion();

    mLibVersion.major = wLibVer>>8;
    mLibVersion.minor = (wLibVer&0xF0)>>4;
    mLibVersion.development = (wLibVer&0xF);

    
    version.append("\tAceXtreme Integrated 1553 Terminal            \n");
    version.append("\tBU-69092 1553 Runtime Library                 \n");
    version.append("\tRelease Rev: ");
    version.append(std::to_string(mLibVersion.major) + ".");
    version.append(std::to_string(mLibVersion.minor)+ ".");
    version.append(std::to_string(mLibVersion.development)+ ".");
    if ((wLibVer&0xF)!=0)
    version.append(" (INTERIM VERSION)");
	show(version);

}

void BU67103x::getError(S16BIT nResult)
{
   std::string errorMessage = "";
   char buf[80];
   aceErrorStr(nResult,buf,80);
   errorMessage.append("\n[ERROR]\tRTL Function Failure:");
   errorMessage.append(buf);
   std::cout<<errorMessage<<std::endl;   
}


