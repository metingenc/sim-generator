// aceInitialize======================================================================================
const short int          cDeviceNumber = 0;       // Logical Device Number [0-31]
const short int          cAccess = 0;		      // ACE_ACCESS_CARD [Only valid option for aceXtreme]
const unsigned short int cMode = 0x0001;          // ACE_MODE_BC :Sets up the device to run as a bus controller
const unsigned int       cMemoryWordSize = 0;     // [No valid option for aceXtreme]
const unsigned int       cRegisterAddress = 0;    // [No valid option for aceXtreme]
const unsigned int       cDeviceMemoryAddres = 0; // [No valid option for aceXtreme]
// ====================================================================================================

// aceBCConfigure======================================================================================
 const unsigned int      cOptions = 0;            // 0 or ACE_BC_ASYNC_LMODE or ACE_BC_ASYNC_LMODE
// ====================================================================================================

//aceBCDataBlkCreate: the maximum number of data blocks available is limited to 2047.==================
const short int          cDataBlockId = 0x0001;   // [must be > 0] 
const unsigned short int cDataBlockSize = 32;     // [1 - 32768] word
// unsigned short int *pBuffer
const unsigned short int cBufferSize = 32;        // [less or equal to buffer and cDataBlockSize]
// ====================================================================================================

// ====================================================================================================
// Option 1 aceBCMsgCreateBCtoRT
// Option 2 aceBCMsgCreateRTtoBC
// Option 3 aceBCAsyncMsgCreateRTtoBC +unsigned short int *pBuffer
// Option 4 aceBCAsyncMsgCreateBCtoRT +unsigned short int *pBuffer
// const short int deviceNumber = 0;
const short int          cMessageBlockkId = 0;    // [must be unique and > 0]
const short int          cDataBlockId2 = 0;  	  // cDataBlockId
const unsigned short int cRemoteTerminal = 0;     // Remote Terminal address of destination RT [x-x]
const unsigned short int cSubAddress = 0;         // Remote Terminal subaddress [x-x]
const unsigned short int cBCtoRTWordCount = 0;    // Message word count of message [1-32]
const unsigned short int cBCtoRTMessageGapTime = 0;// The time to next msg in μ seconds
const unsigned int       cBCtoRTMessageOptions = 0;// use ACE_BCCTRL_CHL_A


// Option 5 aceBCMsgCreateRTtoRT
// Option 6 aceBCAsyncMsgCreateRTtoRT const unsigned short int *pBuffer 
// const short int deviceNumber = 0; 
const short int          cMessageBlockId = 0;     // [must be unique and >= 0]
const short int 		 cRTtoRTDataBlockId = 0;  // cDataBlockId
const unsigned short int cRemoteTerminalRx = 0;   // Receiving Remote Terminal address of destination RT
const unsigned short int cSubAddressRx = 0;       // Receiving Remote Terminal subaddress
const unsigned short int cRTtoRTWordCount = 0;    // Message word count of message
const unsigned short int cRemoteTerminalTx = 0;   // Transmitting Remote Terminal address of RT
const unsigned short int cSubAddressTx = 0;       // Transmitting Remote Terminal subaddress
const unsigned short int cRTtoRTMessageGapTime = 0;// The time to next msg in μ seconds
const unsigned int       cRTtoRTMessageOptions = 0x0110;// ACE_BCCTRL_EOM_IRQ | ACE_BCCTRL_RETRY_ENA
// ====================================================================================================

// aceBCOpCodeCreate
const short int          cOpCodeId = 0;           // Unique, user supplied ID number of Opcode
const unsigned short int cOpCodeType = 0;         // ACE_OPCODE_XEQ or ACE_OPCODE_CAL
const unsigned short int cCondition = 0;          // ACE_CNDTST_ALWAYS
const unsigned int       cOpCpdeParameter1 = 0;   // cMessageBlockId or cMinorBlockId
const unsigned int       cOpCodeParameter2 = 0;   // parameter info depends on opcode (see opcode)
const unsigned int       cReserved = 0;           // Reserved

// aceBCFrameCreate
const short int          cFrameId = 0;            // A unique and must be >= 0
const unsigned short int cFrameType = 0;          // ACE_FRAME_MAJOR or ACE_FRAME_MINOR
//const short int cOpCodeIDs[] = 0;               // word array of the opcodes to be used for the frame
const unsigned short int cOpCodeCount = 0;        // number of opcodes in the cOpCodeIds and must be > 0
const unsigned short int cMinorFrameTime = 0;     // frame complete time in μs, the least 100 μSec
const unsigned short int cFlags = 0;              // Allows the SDK to use default options

// aceBCInstallHBuf
const unsigned int       cHBufSize = 0;           // [(NUM_MESSSAGES)*40words]*256 -> 4K – 5000K 16-bit words

// cMajorFrameId
const unsigned short cMajorFrameId = 1;

// ====================================================================================================

// BC Message Gap 		: >= 6μs
// RT Response Time 	: 7μs
// BC Frame Time 		: 16-bit

// MIL-STD-1553 Channel Modes 		: ACE_MODE_BC, ACE_MODE_RT

// Object Unique Identifiers (OUID):	[1-65535]

// Operation Mode 		Data Object Type
// BC 	 				Instruction Opcodes
// BC 					Data Blocks
// BC 					Messages
// BC   				Frames
// RT/multi-RT			Data Blocks



































