#include <iostream>

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

  std::map<unsigned, std::vector<short>> periodMap;
  std::vector<int> periodList;
  std::map<unsigned, std::vector<short>> minorFrameList;


  for(auto it = messages.begin(); it != messages.end(); ++it)
  {
    if(SyncType::SYNC == it->second.getSyncType())
    {      
      unsigned key = 1000/it->second.getFrequency();
      short value = it->second.getMessageBlockId();
      periodMap[key].push_back(value);      
    }
  }
  
  for(auto it = periodMap.begin(); it != periodMap.end(); ++it)
  {
      unsigned key = it->first;
      periodList.push_back(key);
      std::cout<<"\n["<<1000/key<<"Hz]\t";
      for(auto itv = it->second.begin(); itv != it->second.end(); ++itv)
      {
        short value = *itv;
        std::cout<<value<<" ";        
      }     
      
  }

  std::cout<<"\n[LCM]\t"<<getLCM(periodList)<<"ms"<<std::endl;
  std::cout<<"[GCD]\t"<<getGCD(periodList)<<"ms"<<std::endl;
  std::cout<<"[MJR]\t"<<getLCM(periodList)/getGCD(periodList)<<" Minor Frames"<<std::endl;

  for(int period = 0; period <getLCM(periodList); period += getGCD(periodList))
  {
     std::cout<<"\n["<<period<<"]\t";

      for(auto it = periodMap.begin(); it != periodMap.end(); ++it)
      {
        if((period % it->first) == 0)
        {
           for(auto itm = it->second.begin(); itm != it->second.end(); ++itm)
           {
              minorFrameList[period].push_back(*itm);  
              std::cout<<*itm<<" ";              
           }
           
        }
      }

     //if(period%)
     //minorFrameList[period].push_back( frequencyMap );
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


// Utility function to find 
// GCD of 'a' and 'b' 
int BU67103x::getGCD(int a, int b) 
{ 
    if (b == 0) 
        return a; 
    return getGCD(b, a % b); 
} 

// Function to find gcd of array of 
// numbers 
int BU67103x::getGCD(std::vector<int> list) 
{ 
    int gcd = list[0]; 

    for(auto it = list.begin(); it != list.end(); ++it)
    {
        gcd = getGCD(*it, gcd); 
    }   
  
    return gcd; 
} 

long long BU67103x::getLCM(std::vector<int> list)
{
    // Initialize result 
    long long lcm = list[0]; 
  
    // ans contains LCM of list[0], ..list[i] 
    // after i'th iteration,     
    for(auto it = list.begin(); it != list.end(); ++it)
    {
        lcm = (((*it * lcm)) / (getGCD(*it, lcm))); 
    }
  
    return lcm; 
}


