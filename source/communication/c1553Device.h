#ifndef c1553_DEVICE_H
#define c1553_DEVICE_H

class c1553Device
{
public:
	virtual void initialize() = 0;
	virtual void deInitialize() = 0;
	virtual void configure() = 0;
	virtual void start() = 0;
	virtual void stop() = 0;
	virtual void read() = 0;
	virtual void write() = 0;
};

#endif 
