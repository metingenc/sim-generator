#ifndef BC_MESSAGE_LOADER_H
#define BC_MESSAGE_LOADER_H

#include <map>
#include "communication/AceBCMessage.h"


class BcMessageLoader
{

public:
	BcMessageLoader(std::string file)
	{
		mFile = file;
	}

	~BcMessageLoader()
	{

	}

	std::map<short, AceBCMessage> load()
	{
		int messageCount = 0;

		std::map<short, AceBCMessage> messageMap;

		pugi::xml_document doc;

		std::cout << "\tMessages are loading...";
	           
	    if (!doc.load_file(mFile.c_str())) 
	    {
	    	std::cout<< "Xml Error: "<<std::endl;	    		    	
	    }
	    else
	    {
	    	std::cout << "\r[OK]"<<std::endl;

		    pugi::xml_node bcMessageList = doc.child("BCMessageList");		    
			
			pugi::xml_node messages = bcMessageList.child("Messages");			

		    for (pugi::xml_node_iterator it = messages.begin(); it != messages.end(); ++it)
			{
				AceBCMessage aceBcMessage;

		    	for (pugi::xml_attribute_iterator ait = it->attributes_begin(); ait != it->attributes_end(); ++ait)
			    {			        	        
			        aceBcMessage.setName(ait->value());
			    }

			    for (pugi::xml_node_iterator itp = it->begin(); itp != it->end(); ++itp)
			    {
			    	for (pugi::xml_attribute_iterator aitp = itp->attributes_begin(); aitp != itp->attributes_end(); ++aitp)
				    {
				    	std::string attributeName(aitp->name());
				        
				        if(attributeName == "messageType")	        				        
				        {
				        	aceBcMessage.setMessageType(static_cast<MessageType>(aitp->as_int()));
				        }
				        else if(attributeName == "syncType")
				        {
				        	 aceBcMessage.setSyncType(static_cast<SyncType>(aitp->as_int()));
				        }
				        else if(attributeName == "frequency")
				        {
				        	aceBcMessage.setFrequency(aitp->as_uint());
				        }
				        else if(attributeName == "remoteTerminal")
				        {
				        	aceBcMessage.setRemoteTerminal(aitp->as_uint());
				        }
				        else if(attributeName == "subAddress")
				        {
				        	aceBcMessage.setSubAdress(aitp->as_uint());
				        	
				        }
				        else if(attributeName == "wordCount")
				        {
				        	aceBcMessage.setWordCount(aitp->as_uint());
				        }
				        else if(attributeName == "messageGapTime")
				        {
				        	aceBcMessage.setMessageGapTime(aitp->as_uint());
				        }
				        else if(attributeName == "messageOptions")
				        {
				        	aceBcMessage.setMessageOptions(aitp->as_uint());				        
				        }
				        else
				        {
							std::cout << "Error: Invalid bcmesage param" + mFile <<std::endl;
				        }
				    }
			    }  
			    
			    /*
			    std::cout << "===============================================================" << std::endl;
			    std::cout << "pKey: "<<aceBcMessage.getKey() <<std::endl;
			    std::cout << "Name: "<<aceBcMessage.getName() <<std::endl;
			    std::cout << "MessageType: "<<aceBcMessage.getMessageType() <<std::endl;
			    std::cout << "SyncType: "<<aceBcMessage.getSyncType() <<std::endl;
			    std::cout << "Frequency: "<<aceBcMessage.getFrequency() <<std::endl;
			    std::cout << "RemoteTerminal: "<<aceBcMessage.getRemoteTerminal() <<std::endl;
			    std::cout << "SubAddress: "<<aceBcMessage.getSubAddress() <<std::endl;			    
			    std::cout << "WordCount: "<<aceBcMessage.getWordCount() <<std::endl;
			    std::cout << "MessageGapTime: "<<aceBcMessage.getMessageGapTime() <<std::endl;
			    std::cout << "MessageOptions: "<<aceBcMessage.getMessageOptions() <<std::endl;
			    aceBcMessage.generateKey();			   
			    std::cout << "===============================================================" << std::endl;
			    */
				messageCount++;			    			    
			    messageMap.insert(std::pair<short, AceBCMessage>(aceBcMessage.generateKey(),aceBcMessage));    	
			    
			}	    	

			std::cout << "[OK]\tMessage Loading completed: "<< messageMap.size() << "/" <<messageCount <<" message(s) loaded"<<std::endl;			
	    }


		return messageMap;
	}

private:
	std::string mFile;

};

#endif