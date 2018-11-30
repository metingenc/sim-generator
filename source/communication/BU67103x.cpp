#include <iostream>
#include "BU67103x.h"
#include "config.h"


BU67103x::BU67103x() : mLibVersion(0,0,0)
{
  
}

BU67103x::~BU67103x()
{

}

void BU67103x::initialize()
{ 
	S16BIT wResult = 0x0000;

	show("BU67103x is initializing...");    	

	getVersion();
	
	wResult = aceInitialize(cDeviceNumber,cAccess,cMode,cMemoryWordSize,cRegisterAddress,cDeviceMemoryAddres);
	if(ACE_ERR_SUCCESS != wResult)
	{
  		getError(wResult);  		
	}  
	else
	{
		show("BU67103x is initialized succcesfully:");
		show("LDN: " + std::to_string(cDeviceNumber));
		show("Access: " + std::to_string(cAccess));
		show("Mode: " + std::to_string(cMode));
	}  
}

void BU67103x::deInitialize()
{
   S16BIT wResult = 0x0000;

   show("BU67103x is deInitializing");

   wResult = aceFree(cDeviceNumber);
   if(ACE_ERR_SUCCESS != wResult)
   {
   	  getError(wResult);
   }
   else
   {
    	show("BU67103x is deinitialized successfully: ");
    	show("LDN: " + std::to_string(cDeviceNumber));
   }

}

void BU67103x::configure()
{
   show("BU67103x is configuring");
   //aceBCConfigure()
   
  // #STEP1 Creating BC Objects ================================
       // Creating Data Blocks          
          // aceBCDataBlkCreate
  // ===========================================================

  // #STEP2 Creating Message Blocks ============================
          // aceBCMsgCreateBCtoRT() ||aceBCAsyncMsgCreateBCtoRT
          // aceBCMsgCreateRTtoBC() ||aceBCAsyncMsgCreateRTtoBC
  // ===========================================================  

  //  #STEP3 Building BC Frames =================================
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

    version.append("==============================================\n");    
    version.append("AceXtreme Integrated 1553 Terminal            \n");
    version.append("BU-69092 1553 Runtime Library                 \n");
    version.append("Release Rev: ");
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
   errorMessage.append("[Error]: RTL Function Failure: ");
   errorMessage.append(buf);
   show(errorMessage);   
}


