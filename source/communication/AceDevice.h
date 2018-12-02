#ifndef ACE_DEVICE_H
#define ACE_DEVICE_H

class AceDevice
{
public:

	AceDevice(): mDeviceNumber(0), 
                 mAccess(0),
                 mMode(0x0001),
                 mMemoryWordSize(0),
                 mRegisterAddress(0),
                 mDeviceMemoryAddres(0),
                 mBcConfigureOptions(0)
	{
        
	}

	AceDevice(short deviceNumber, 
			  short access,	       			  
			  unsigned short mode,
			  unsigned memoryWordSize,
			  unsigned registerAddress,
			  unsigned deviceMemoryAddres,
			  unsigned bcConfigureOptions
			  )
	{
		mDeviceNumber = deviceNumber;
		mAccess = access;
		mMode = mode;
		mMemoryWordSize = memoryWordSize;
		mRegisterAddress = registerAddress;
		mDeviceMemoryAddres = deviceMemoryAddres;
		mBcConfigureOptions = bcConfigureOptions;
	}

	~AceDevice()
	{

	}
	
	short getDeviceNumber()
	{
		return mDeviceNumber;
	}

	short getAccess()
	{
		return mAccess;
	}

	unsigned short getMode()
	{
		return mMode;
	}

	unsigned getMemoryWordSize()
	{
		return mMemoryWordSize;
	}

	unsigned getRegisterAddress()
	{
		return mRegisterAddress;
	}

	unsigned getDeviceMemoryAddres()
	{
		return mDeviceMemoryAddres;
	}

	unsigned getBcConfigureOptions()
	{
		return mBcConfigureOptions;
	}

	void setDeviceNumber(short number)
	{
		mDeviceNumber = number;
	}

	void setAccess(short access)
	{
		mAccess = access;
	}

	void setMode(unsigned short mode)
	{
		mMode = mode;
	}

	void setMemoryWordSize(unsigned size)
	{
		mMemoryWordSize = size;
	}

	void setRegisterAddress(unsigned address)
	{
		mRegisterAddress = address;
	}

	void setDeviceMemoryAddress(unsigned address)
	{
		mDeviceMemoryAddres = address;
	}

	void setBcConfigureOptions(unsigned options)
	{
		mBcConfigureOptions = options;
	}

private:
	short		   mDeviceNumber;       // Logical Device Number [0-31]
	short          mAccess;		        // ACE_ACCESS_CARD [Only valid option for aceXtreme]
	unsigned short mMode;               // ACE_MODE_BC :Sets up the device to run as a bus controller
	unsigned       mMemoryWordSize;     // [No valid option for aceXtreme]
	unsigned       mRegisterAddress;    // [No valid option for aceXtreme]
	unsigned       mDeviceMemoryAddres; // [No valid option for aceXtreme]
	unsigned	   mBcConfigureOptions; // BC operation options
};

#endif