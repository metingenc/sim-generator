#ifndef ACE_BC_MESSAGE_H
#define ACE_BC_MESSAGE_H

#include <iostream>

enum SyncType { SYNC = 0, ASYNC = 1};
enum MessageType {BCtoRT = 0, RTtoBC = 1, RTtoRT = 2};

union Key
{
	short value;
	struct sKey
	{
		unsigned sa:5; 
		unsigned type:4;
		unsigned rt:5;
		unsigned sync:5;
	}member;
};

class AceBCMessage
{
	public:		

		AceBCMessage() : mName("EmptyMessage"),
						 mMessageType(BCtoRT),
						 mSyncType(SYNC),
						 mFrequency(0),
						 mMessageBlockId(0),	// to be removed
						 mDataBlockId(0),		// to be removed
						 mRemoteTerminal(0),
						 mSubAdress(0),
						 mWordCount(0),
						 mMessageGapTime(0),
						 mMessageOptions(0),
						 mBuffer(NULL)
		{

		}

		AceBCMessage(MessageType messageType,
					std::string name,
					SyncType syncType, 
					unsigned frequency,
					short messageBlockId,
					short dataBlockId,
					unsigned short rt,
					unsigned short sa,
					unsigned short wc,
					unsigned short time,
					unsigned option
					/*unsigned short *buffer*/)
		{
			mName = name;
			mMessageType = messageType;
			mSyncType = syncType;
			mFrequency = frequency;
			mMessageBlockId = messageBlockId;
			mDataBlockId = dataBlockId;
			mRemoteTerminal = rt;
			mSubAdress = sa;
			mWordCount = wc;
			mMessageGapTime = time;
			mMessageOptions = option;
			generateKey();
			// mBuffer TBD
		}

		~AceBCMessage()
		{

		}

		short getKey()
		{
			return generateKey();			
		}

		std::string getName()
		{
			return mName;
		}

		MessageType getMessageType()
		{
			return mMessageType;
		}
		SyncType getSyncType()
		{
			return mSyncType;
		}

		unsigned getFrequency()
		{
			return mFrequency;
		}

		short getMessageBlockId()
		{
			return mMessageBlockId;
		}

		short getDataBlockId()
		{
			return mDataBlockId;
		}

		unsigned short getRemoteTerminal()
		{
			return mRemoteTerminal;
		}

		unsigned short getSubAddress()
		{
			return mSubAdress;
		}

		unsigned short getWordCount()
		{
			return mWordCount;
		}

		unsigned short getMessageGapTime()
		{
			return mMessageGapTime;
		}

		unsigned getMessageOptions()
		{
			return mMessageOptions;
		}

		unsigned short* getBuffer()
		{
			return mBuffer;
		}

		void setName(std::string name)
		{
			mName = name;
		}

		void setMessageType(MessageType type)
		{
			mMessageType = type;			
		}

		void setSyncType(SyncType type)
		{
			mSyncType = type;
		}

		void setFrequency(unsigned frequency)
		{
			mFrequency = frequency;
		}

		void setMessageBlockId(short id)
		{
			mMessageBlockId = id;
		}

		void setDataBlockId(short id)
		{
			mDataBlockId = id;
		}

		void setRemoteTerminal(unsigned short rt)
		{
			mRemoteTerminal = rt;
		}

		void setSubAdress(unsigned short sa)
		{
			mSubAdress = sa;
		}

		void setWordCount(unsigned short wc)
		{
			mWordCount = wc;
		}

		void setMessageGapTime(unsigned short time)
		{
			mMessageGapTime = time;
		}

		void setMessageOptions(unsigned option)
		{
			mMessageOptions = option;
		}

		void setBuffer(/*unsigned short *buffer*/)
		{			
			// copy buffer to mBuffer
		}

		short generateKey()
		{
			// Message Key will be used for message id and data block id
		    // Create uniq key value from message parameters
		    // Message key will be generated as following order.
		    // Priority
		    //  High (0)
		    //   .    Sync BC to RT Message
		    //   .    Sync RT to BC Message
		    //   .    Sync RT to RT Message
		    //   .   ASync BC to RT Message
		    //   .   ASync RT to BC Message
		    //   .   ASync RT to RT Message
		    //  Low (N)
		    // Creation formula of message id is
		    //  [14].bit    [13-9].bit    [8-5].bit     [4-0].bit       
		    //      0        00000          0000         00000 
		    //      |          |              |            |
		    // [SyncType][RemoteTerminal][MessageType][SubAddress]

		    
		    Key key;		    
		    key.value = 0;
		    
		    key.member.sync = static_cast<short>(mSyncType);
		    key.member.rt = mRemoteTerminal;
		    key.member.type = static_cast<short>(mMessageType);
		    key.member.sa = mSubAdress; 
		    
			return key.value;
		}
		
	private:		
		std::string mName;
		MessageType mMessageType;
		SyncType mSyncType;
		unsigned mFrequency;
		short mMessageBlockId;
		short mDataBlockId;
		unsigned short mRemoteTerminal;
		unsigned short mSubAdress;
		unsigned short mWordCount;
		unsigned short mMessageGapTime;
		unsigned mMessageOptions;
		unsigned short *mBuffer;
};

#endif