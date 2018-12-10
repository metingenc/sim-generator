#include <iostream>
#include <iomanip>
#include <Windows.h>



#include "BU67103x.h"
#include "config.h"






BU67103x::BU67103x(AceDevice &aceConfig, std::map<short,AceBCMessage> &messages) : mIsInitialized(false),
 mIsConfigurated(false), mIsStarted(false), mLibVersion(0,0,0), mConfig(aceConfig), mMessages(messages)
{
  getVersion();
}

BU67103x::~BU67103x()
{

}

void BU67103x::initialize()
{ 
	S16BIT wResult = 0x0000;	

  std::cout << "\tBU67103x is initializing...";  
	
	wResult = aceInitialize(mConfig.getDeviceNumber(),mConfig.getAccess(),mConfig.getMode(),mConfig.getMemoryWordSize(),mConfig.getRegisterAddress(),mConfig.getDeviceMemoryAddres());
	
  if(ACE_ERR_SUCCESS != wResult)
	{
  		getError(wResult);  		
	}  
	else
	{
    mIsInitialized = true;
    std::cout <<"\r[OK]"<<std::endl;
		std::cout<<"[OK]\tBU67103x is initialized."<<std::endl;
		std::cout<<"\tLDN:\t" + std::to_string(mConfig.getDeviceNumber())<<std::endl;
		std::cout<<"\tAccess:\t" + std::to_string(mConfig.getAccess())<<std::endl;
		std::cout<<"\tMode:\t" + std::to_string(mConfig.getMode())<<std::endl;
	}  
}

void BU67103x::deInitialize()
{
   S16BIT wResult = 0x0000;

   std::cout<<"\n\tBU67103x is deInitializing";

   wResult = aceFree(mConfig.getDeviceNumber());
   if(ACE_ERR_SUCCESS != wResult)
   {
   	  getError(wResult);
   }
   else
   {
      mIsInitialized = false;
      mIsStarted = false;
      mIsConfigurated = false;
    	std::cout<<"\n[OK]\tBU67103x is deinitialized successfully: ";
    	std::cout<<"\n\tLDN: " + std::to_string(mConfig.getDeviceNumber());
   }

}

void BU67103x::configure()
{
  S16BIT wResult = 0x0000;

  if (!mIsInitialized)
  {
      std::cout<<"[WARN]\tBefore you configure, Device must be initialized."<<std::endl;
      return;
  }    
  
  std::cout<<"\tBU67103x is configuring..."; 

  wResult = aceBCConfigure(mConfig.getDeviceNumber(), mConfig.getBcConfigureOptions());

   if(ACE_ERR_SUCCESS != wResult)
   {
      mIsConfigurated = false;
      getError(wResult);
   }
   else
   {
      mIsConfigurated = true;
      std::cout<<"\r[OK]"<<std::endl;
      std::cout<<"\tOptions: "<<mConfig.getBcConfigureOptions()<<std::endl;
   }

   createBCObjects();
}

void BU67103x::createBCObjects()
{
  std::vector<unsigned short> wBuffer { 0xFFFF,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
                                  0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
                                  0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
                                  0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000};

  signed short wResult;
  
  if (!mIsConfigurated)
  {
      std::cout<<"[WARN]\tBefore you create objects, Device must be configurated."<<std::endl;
      return;
  } 

  
  // # Step1 Creating BC Data Blocks=======================================================================  

  std::cout<<"\n\tBC data blocks are creating..."<<std::endl;

  for(auto it = mMessages.begin(); it != mMessages.end(); ++it)
  {    
    it->second.setBuffer(wBuffer);
    if(SyncType::SYNC == it->second.getSyncType())
    {      
      wResult = aceBCDataBlkCreate(mConfig.getDeviceNumber(), it->first, ACE_BC_DBLK_SINGLE, it->second.getBuffer(), 32); 
      
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
  
  std::cout<<"\n\tBC message blocks are creating..."<<std::endl;
  
  for(auto it = mMessages.begin(); it != mMessages.end(); ++it)
  {  
    it->second.setBuffer(wBuffer);
    if(MessageType::BCtoRT == it->second.getMessageType())  
    {
        if(SyncType::SYNC == it->second.getSyncType())
        {
          wResult = aceBCMsgCreateBCtoRT(mConfig.getDeviceNumber(), 
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
            wResult = aceBCAsyncMsgCreateBCtoRT(mConfig.getDeviceNumber(), 
                                                it->first,
                                                it->first,
                                                it->second.getRemoteTerminal(),
                                                it->second.getSubAddress(),
                                                it->second.getWordCount(),
                                                it->second.getMessageGapTime(),
                                                it->second.getMessageOptions(),
                                                it->second.getBuffer()
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
          wResult = aceBCMsgCreateRTtoBC(mConfig.getDeviceNumber(), 
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
            wResult = aceBCAsyncMsgCreateRTtoBC(mConfig.getDeviceNumber(), 
                                                it->first,
                                                it->first,
                                                it->second.getRemoteTerminal(),
                                                it->second.getSubAddress(),
                                                it->second.getWordCount(),
                                                it->second.getMessageGapTime(),
                                                it->second.getMessageOptions(),
                                                it->second.getBuffer()
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

  //  #Step3 Building BC Frames ===========================================================================
     // Creating Message Opcodes
  std::cout<<"\n\tBC message opcodes are creating..."<<std::endl;
 
  for(auto it = mMessages.begin(); it != mMessages.end(); ++it)
  {  
    if(SyncType::SYNC == it->second.getSyncType())
    {
      wResult = aceBCOpCodeCreate(mConfig.getDeviceNumber(), 
                                     it->first,
                                     ACE_OPCODE_XEQ,
                                     ACE_CNDTST_ALWAYS,
                                     it->first,
                                     0,
                                     0);

      if(ACE_ERR_SUCCESS != wResult)
      {
        getError(wResult);
        std::cout<<"\t"<<it->first<<"\t"<<it->second.getName()<<" Message opcode creation failed." <<std::endl;
        return;
      }
      else
      {
        std::cout<<"[OK]\t"<<it->first<<"\t"<<it->second.getName()<<" Message opcode creation succeeded." <<std::endl;     
      }  
    }      
  } 
 // ===================================================================================================================================

  std::map<unsigned, std::vector<short>> periodMap;
  std::vector<short> periodList;
  std::map<unsigned, std::vector<short>> minorFrameMap;
  std::vector<short> minorFrameList;

  // Create Period,OUID List
  for(auto it = mMessages.begin(); it != mMessages.end(); ++it)
  {
    if(SyncType::SYNC == it->second.getSyncType())
    {      
      unsigned key = 1000/it->second.getFrequency();
      short value = it->second.getMessageBlockId();
      periodMap[key].push_back(value);      
    }
  }
  
  // Print List
  std::cout<<"\n\tFrequency OUID List";
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

  std::cout<<"\n\n\tFrame Creation Parameters:";
  std::cout<<"\n[LCM]\t"<<getLCM(periodList)<<"ms"<<std::endl;
  std::cout<<"[GCD]\t"<<getGCD(periodList)<<"ms"<<std::endl;
  std::cout<<"[MJR]\t"<<getLCM(periodList)/getGCD(periodList)<<" Minor Frames"<<std::endl;

  // Major Frame Structure
  for(int period = 0; period <getLCM(periodList); period += getGCD(periodList))
  {
      minorFrameList.push_back(period);
      for(auto it = periodMap.begin(); it != periodMap.end(); ++it)
      {        
        if((period % it->first) == 0)
        {
           for(auto itm = it->second.begin(); itm != it->second.end(); ++itm)
           {
              minorFrameMap[period].push_back(*itm);                            
           }
           
        }
        else if(minorFrameMap[period].size() == 0)
        {
            minorFrameMap[period].push_back(0); 
        }
      }    
     
  }

  // Print Major Frame Structure
  std::cout<<"\n\tMajor Frame Structure";
  for(auto it = minorFrameMap.begin(); it != minorFrameMap.end(); ++it)
  {
    std::cout<<"\n["<<it->first<<"]\t";             
    for(auto itm = it->second.begin(); itm != it->second.end(); ++itm)
    {       
      std::cout<<*itm<<" ";              
    }
  }

  // Creating Minor Frame Opcodes
  std::cout<<"\n\tBC minor frame opcodes are creating..."<<std::endl;

  for(auto it = minorFrameMap.begin(); it != minorFrameMap.end(); ++it)
  {
     if(0 != it->second[0] ) 
     {
        wResult = aceBCOpCodeCreate(mConfig.getDeviceNumber(), 
                                       it->first,
                                       ACE_OPCODE_CAL,
                                       ACE_CNDTST_ALWAYS,
                                       it->first,
                                       0,
                                       0);              
     }
     else
     {
        wResult = aceBCOpCodeCreate(mConfig.getDeviceNumber(), 
                                       it->first,
                                       ACE_OPCODE_CAL,
                                       ACE_CNDTST_NEVER,
                                       it->first,
                                       0,
                                       0);      
     }



      if(ACE_ERR_SUCCESS != wResult)
      {
        getError(wResult);
        std::cout<<"[FAIL]\t"<<it->first<<".ms"<<"Message opcode creation failed." <<std::endl;
        return;
      }
      else
      {
        std::cout<<"[OK]\t"<<it->first<<".ms"<<"Message opcode creation succeeded." <<std::endl;     
      }        

  }

  // Creating BC Minor Frames
  std::cout<<"\n\tBC minor frame(s) are creating..."<<std::endl;

  for(auto it = minorFrameMap.begin(); it != minorFrameMap.end(); ++it)
  {
 
      wResult = aceBCFrameCreate(mConfig.getDeviceNumber(), 
                                       it->first,
                                       ACE_FRAME_MINOR,
                                       &it->second[0],
                                       it->second.size(),
                                       getGCD(periodList) * 10, // 0 durumunu test et
                                       0);              

      if(ACE_ERR_SUCCESS != wResult)
      {
        getError(wResult);
        std::cout<<"[FAIL]\t"<<it->first<<".ms"<<"BC minor frame(s) are creation failed." <<std::endl;
        return;
      }
      else
      {
        std::cout<<"[OK]\t"<<it->first<<".ms"<<"BC minor frame(s) are creation succeeded.\n\tACE_FRAME_MINOR\n\t"<<"Frame Time:"<<getGCD(periodList) * 10<<".ms" <<std::endl;     
      }        

  }

   // Creating BC Major Frames
  std::cout<<"\n\tBC major frame is creating..."<<std::endl;

  wResult = aceBCFrameCreate(mConfig.getDeviceNumber(), 
                             cMajorFrameId,
                             ACE_FRAME_MAJOR,
                             &minorFrameList[0],
                             minorFrameList.size(),
                             (getGCD(periodList) * 10), // 0 durumunu test et
                             0);              

  if(ACE_ERR_SUCCESS != wResult)
  {
    getError(wResult);
    std::cout<<"[FAIL]\t"<<"1 BC major frame(s) are creation failed." <<std::endl;
    return;
  }
  else
  {
    std::cout<<"[OK]\t"<<"1 BC major frame(s) are creation succeeded.\n\tACE_FRAME_MAJOR\n\t"<<"Frame Time:"<<getGCD(periodList) * 10<<".ms" <<std::endl;     
  }        

  mIsConfigurated = true;

 // #STEP4 Creating Host Buffer ================================  
     // aceBCInstallHBuf()
 // ===========================================================        

}

void BU67103x::start()
{
  signed short wResult;

  if(!mIsConfigurated)
  {
    if (!mIsConfigurated)
    {
        std::cout<<"[WARN]\tBefore you start, Device must be configurated."<<std::endl;
        return;
    }     
  }

  std::cout<<"\n\tBU67103x is starting..."<<std::endl;

  wResult  = aceBCStart(mConfig.getDeviceNumber(), cMajorFrameId, -1);

  if(ACE_ERR_SUCCESS != wResult)
  {
    mIsStarted = false;
    getError(wResult);
    std::cout<<"[FAIL]\t"<<"Device could not be started." <<std::endl;
    return;
  }
  else
  {
    mIsStarted = true;
    std::cout<<"[OK]\t"<<"Device has just been started successfully." <<std::endl;     
    std::cout<<"[OK]\t"<<"Running . . ." <<std::endl;     
  }  
}


void BU67103x::stop()
{
  signed short wResult;
 

  if (!mIsStarted)
  {
      std::cout<<"[WARN]\tBefore you configure, Device must be started."<<std::endl;
      return;
  }     
  

  std::cout<<"\n\tBU67103x is stoping..."<<std::endl;

  wResult  = aceBCStop(mConfig.getDeviceNumber());

  if(ACE_ERR_SUCCESS != wResult)
  {
    getError(wResult);
    std::cout<<"[FAIL]\t"<<"Device could not be stopped." <<std::endl;
    return;
  }
  else
  {
    std::cout<<"[OK]\t"<<"Device has just been stopped successfully." <<std::endl;         
  }
}

void BU67103x::read()
{
   show("BU67103x is reading");
   // aceBCGetHBufMsgDecoded()
   // aceBCDataBlkRead()
}

void BU67103x::write(std::vector<AceTestMessage> &testMessages)
{   
  signed short wResult = -1;

  if (!mIsStarted)
  {
      std::cout<<"[WARN]\tBefore you write, device must be started."<<std::endl;
      return;
  }   

  for(auto itv = testMessages.begin(); itv != testMessages.end(); ++itv)
  {
    if(SyncType::SYNC == (itv->getSyncType()))
    {
      short key = itv->getKey();
      unsigned index = itv->getWordCountIndex()-1; 
         
      mMessages[key].getBuffer()[index] = itv->getDataLSW();
      
      if(itv->getDataSize() == 2)
      {        
        mMessages[key].getBuffer()[index+1] = itv->getDataMSW();
      }     

      wResult = aceBCDataBlkWrite(mConfig.getDeviceNumber(), mMessages[key].generateKey(),mMessages[key].getBuffer(),mMessages[key].getWordCount(),0);       

      if(ACE_ERR_SUCCESS != wResult)
      {
        getError(wResult);
        std::cout<<"[FAIL]\t"<<mMessages[key].generateKey()<<"\tMSG "<<mMessages[key].getRemoteTerminal()<<"-"<<mMessages[key].getSubAddress()<<"-"<<mMessages[key].getWordCount()<<std::endl;    
        return;
      }
      else
      {
        std::cout<<"[OK]\t"<<mMessages[key].generateKey()<<"\tMSG\t["<<mMessages[key].getRemoteTerminal()<<"-"<<mMessages[key].getSubAddress()<<"-"<<mMessages[key].getWordCount()<<"]\t";
        std::cout<<itv->getName()<<std::endl;
        std::cout<<"\t\tDATA\t";
        for(int i = 0; i<mMessages[key].getWordCount(); i++)
        {
             std::cout<<std::hex<<std::uppercase<<std::setfill('0') << std::setw(4)<<mMessages[key].getBuffer()[i]<<" ";
             if(i==mMessages[key].getWordCount()/2)
              std::cout<<"\n\t\t\t";
        }
        std::cout<<"\n\n";
        
      }       

      Sleep(itv->getDelay());   
      
    }

  }




}


void BU67103x::write()
{   
   //aceBCDataBlkWrite()
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
	  std::cout<<version<<std::endl;
    std::cout<<" ============================================================"<<std::endl;

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
short BU67103x::getGCD(short a, short b) 
{ 
    if (b == 0) 
        return a; 
    return getGCD(b, a % b); 
} 

// Function to find gcd of array of 
// numbers 
short BU67103x::getGCD(std::vector<short> list) 
{ 
    short gcd = list[0]; 

    for(auto it = list.begin(); it != list.end(); ++it)
    {
        gcd = getGCD(*it, gcd); 
    }   
  
    return gcd; 
} 

short BU67103x::getLCM(std::vector<short> list)
{
    // Initialize result 
    short lcm = list[0]; 
  
    // ans contains LCM of list[0], ..list[i] 
    // after i'th iteration,     
    for(auto it = list.begin(); it != list.end(); ++it)
    {
        lcm = (((*it * lcm)) / (getGCD(*it, lcm))); 
    }
  
    return lcm; 
}


