#ifndef TEST_CASE_LOADER_H
#define TEST_CASE_LOADER_H


#include "Communication/AceTestMessage.h"



class TestCaseLoader
{
public:
	TestCaseLoader(std::string file)
	{
		mFile = file;
	}

	~TestCaseLoader()
	{

	}

	std::vector<AceTestMessage> load()
	{	
		std::vector<AceTestMessage> testMessages;

		pugi::xml_document doc;

		std::cout << "\tTest Case are loading...";
	           
	    if (!doc.load_file(mFile.c_str())) 
	    {
	    	std::cout<< "Xml Error: "<<std::endl;	    		    	
	    }
	    else
	    {
	    	std::cout << "\r[OK]"<<std::endl;

		    pugi::xml_node bcMessageList = doc.child("TestCase");		    
			
			pugi::xml_node testSteps = bcMessageList.child("TestSteps");			

		    for (pugi::xml_node_iterator it = testSteps.begin(); it != testSteps.end(); ++it)
			{
				AceTestMessage testMessage;

		    	for (pugi::xml_attribute_iterator ait = it->attributes_begin(); ait != it->attributes_end(); ++ait)
			    {		
			    	std::string attributeName(ait->name());	        	        
			        std::cout<<"\t"<<"Test Case "<<ait->value()<<" loading..."<<std::endl;
			        if(attributeName == "name")	        				        
				    {
				       	testMessage.setName(ait->value());
				    }
			    }

			    for (pugi::xml_node_iterator itp = it->begin(); itp != it->end(); ++itp)
			    {
			    	for (pugi::xml_attribute_iterator aitp = itp->attributes_begin(); aitp != itp->attributes_end(); ++aitp)
				    {
				    	std::string attributeName(aitp->name());				    	
				        
				        if(attributeName == "messageType")	        				        
				        {
				        	testMessage.setMessageType(static_cast<MessageType>(aitp->as_int()));
				        }
				        else if(attributeName == "syncType")
				        {
				        	 testMessage.setSyncType(static_cast<SyncType>(aitp->as_int()));
				        }
				        else if(attributeName == "remoteTerminal")
				        {
				        	testMessage.setRemoteTerminal(aitp->as_uint());
				        }
				        else if(attributeName == "subAddress")
				        {
				        	testMessage.setSubAdress(aitp->as_uint());
				        	
				        }
				        else if(attributeName == "wordCountIndex")
				        {
				        	testMessage.setWordCountIndex(aitp->as_uint());
				        }
				        else if(attributeName == "dataType")
				        {
				        	testMessage.setDataType(aitp->value());
				        }
				        else if(attributeName == "lsbScale")
				        {
				        	testMessage.setLsbScale(aitp->as_double());
				        }				        
				        else if(attributeName == "dataSize")
				        {
				        	testMessage.setDataSize(aitp->as_uint());
				        }
				        else if(attributeName == "dataLsw")
				        {				        	
				        	std::string hexStr = aitp->value();				        	
				        	unsigned value = std::stoi(hexStr,0,16);
				        	testMessage.setDataLSW(value);							        		        	
				        }
				        else if(attributeName == "dataMsw")
				        {
				        	std::string hexStr = aitp->value();				        	
				        	unsigned value = std::stoi(hexStr,0,16);
				        	testMessage.setDataMSW(value);
				        }
				        else if(attributeName == "delay")
				        {
				        	testMessage.setDelay(aitp->as_uint());
				        }
				        else
				        {
							std::cout << "Error: Invalid bcmesage param" + mFile <<std::endl;
				        }				        
				    }
			    }  
			    
			    testMessages.push_back(testMessage);
			    /*
			    std::cout << "===============================================================" << std::endl;
			    std::cout << "pKey: "<<testMessage.getKey() <<std::endl;
			    std::cout << "Name: "<<testMessage.getName() <<std::endl;
			    std::cout << "MessageType: "<<testMessage.getMessageType() <<std::endl;
			    std::cout << "SyncType: "<<testMessage.getSyncType() <<std::endl;			    
			    std::cout << "RemoteTerminal: "<<testMessage.getRemoteTerminal() <<std::endl;
			    std::cout << "SubAddress: "<<testMessage.getSubAddress() <<std::endl;			    		    

			    std::cout << "wordCountIndex: "<<testMessage.getWordCountIndex() <<std::endl;	
			    std::cout << "dataType: "<<testMessage.getDataType() <<std::endl;	
			    std::cout << "lsbScale: "<<testMessage.getLsbScale() <<std::endl;	
			    std::cout << "dataSize: "<<testMessage.getDataSize() <<std::endl;	
			    std::cout << "dataLsw: "<<testMessage.getDataLSW() <<std::endl;	
			    std::cout << "dataMsw: "<<testMessage.getDataMSW() <<std::endl;	
			    std::cout << "delay: "<<testMessage.getDelay() <<std::endl;	

			    testMessage.generateKey();			   
			    std::cout << "===============================================================" << std::endl;
			    */   						    			    			       	
			    
			}	    	

			std::cout << "[OK]\t"<<mFile<<" test case(s) loading succeeded."<<std::endl;	
			
	    }

	    return testMessages;
	}

private:
	std::string mFile;

};

#endif