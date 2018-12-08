#ifndef ACE_TEST_MESSAGE_H
#define ACE_TEST_MESSAGE_H

#include <iostream>
#include <vector>
#include <string>

#include "AceBCMessage.h"

class AceTestMessage : public AceBCMessage
{
    
public:		
	AceTestMessage() : mWordCountIndex(0),
    				   mDataType("None"),
    				   mLsbScale(1),
    				   mDataSize(0),
    				   mDataLSW(0),
    				   mDataMSW(0),
    				   mDelay(0)
	{

	}

	~AceTestMessage()
	{

	}

	unsigned getWordCountIndex()
	{
		return mWordCountIndex;
	}

    std::string getDataType()
	{
		return mDataType;
	}

    double getLsbScale()
	{
		return mLsbScale;
	}

    unsigned getDataSize()
	{
		return mDataSize;
	}

    unsigned short getDataLSW()
	{
		return mDataLSW;
	}

    unsigned short getDataMSW()
	{
		return mDataMSW;
	}

    unsigned getDelay()
	{
		return mDelay;
	}
		
	void setWordCountIndex(unsigned index)
	{
		mWordCountIndex = index;
	}

    void setDataType(std::string type)
	{
		mDataType = type;
	}

    void setLsbScale(double scale)
	{
		mLsbScale = scale;
	}

    void setDataSize(unsigned size)
	{
		mDataSize = size;
	}

    void setDataLSW(unsigned short lsw)
	{
		mDataLSW = lsw;
	}

    void setDataMSW(unsigned short msw)
	{
		mDataMSW = msw;
	}

    void setDelay(unsigned delay)
	{
		mDelay = delay;
	}

private:
    unsigned mWordCountIndex;
    std::string mDataType;
    double mLsbScale;
    unsigned mDataSize;
    unsigned short mDataLSW;
    unsigned short mDataMSW;
    unsigned mDelay;
	
};

#endif