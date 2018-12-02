#ifndef CONFIG_LOADER_H
#define CONFIG_LOADER_H

#include <string>
#include "communication/aceDevice.h"
#include "pugixml.hpp"

class ConfigLoader
{
public:
	ConfigLoader(std::string file)
	{
		mFile = file;
	}

	~ConfigLoader()
	{

	}

	AceDevice load()
	{
		AceDevice device;

		pugi::xml_document doc;
	        
	    std::cout<<"\t"<<mFile<<" file is loading...";

	    if (!doc.load_file(mFile.c_str())) 
	    {
	    	std::cout<< "Xml Error: "<<std::endl;	    		    	
	    }
	    else
	    {
	    	
	    	std::cout<<"\r[OK]"<<std::endl;

		    pugi::xml_node config = doc.child("Config");		    
			
			pugi::xml_node nodes = config.child("Params");

		    for (pugi::xml_node_iterator it = nodes.begin(); it != nodes.end(); ++it)
			{
		    	for (pugi::xml_attribute_iterator ait = it->attributes_begin(); ait != it->attributes_end(); ++ait)
			    {			        
			        std::string name = ait->name();

			        if(name == "deviceNumber")
			        {
			        	device.setDeviceNumber(ait->as_int());
			        }
			        else if(name == "access")
			        {
			        	device.setAccess(ait->as_int());	
			        }
			        else if(name == "mode")
			        {
			        	device.setMode(ait->as_uint());
			        }
			        else if(name == "memoryWordSize")
			        {
			        	device.setMemoryWordSize(ait->as_uint());
			        }
			        else if(name == "registerAddress")
			        {
			        	device.setRegisterAddress(ait->as_uint());
			        }
			        else if(name == "deviceMemoryAddress")
			        {
			        	device.setDeviceMemoryAddress(ait->as_uint());
			        }
			        else if(name == "bcConfigureOptions")
			        {
			        	device.setBcConfigureOptions(ait->as_uint());			        	
			        }
			        else
			        {
			        	std::cout << "Invalid config param" + mFile <<std::endl;
			        }       	

			    }
		    	
			}	    	
	    }


		return device;
	}

private:
	std::string mFile;
};


#endif
