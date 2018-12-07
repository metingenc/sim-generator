#ifndef TEST_CASE_LOADER_H
#define TEST_CASE_LOADER_H

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

	void load(std::map<short, AceBCMessage> &messages)
	{	
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
				AceBCMessage aceBcMessage;

		    	for (pugi::xml_attribute_iterator ait = it->attributes_begin(); ait != it->attributes_end(); ++ait)
			    {			        	        
			        std::cout<<"\t"<<"Test Case "<<ait->value()<<" loading..."<<std::endl;
			    }

			    for (pugi::xml_node_iterator itp = it->begin(); itp != it->end(); ++itp)
			    {
			    	for (pugi::xml_attribute_iterator aitp = itp->attributes_begin(); aitp != itp->attributes_end(); ++aitp)
				    {
				    	std::string attributeName(aitp->name());

				    	std::cout<<"\t\t"<<"Test Step "<<attributeName<<" is loading..."<<std::endl;;
				        
				        if(attributeName == "messageType")	        				        
				        {
				        	aceBcMessage.setMessageType(static_cast<MessageType>(aitp->as_int()));
				        }
				        else if(attributeName == "syncType")
				        {
				        	 aceBcMessage.setSyncType(static_cast<SyncType>(aitp->as_int()));
				        }
				        else if(attributeName == "remoteTerminal")
				        {
				        	aceBcMessage.setRemoteTerminal(aitp->as_uint());
				        }
				        else if(attributeName == "subAddress")
				        {
				        	aceBcMessage.setSubAdress(aitp->as_uint());
				        	
				        }
				        else if(attributeName == "wordCountIndex")
				        {
				        	//
				        }
				        else if(attributeName == "dataLsb")
				        {
				        	//
				        }
				        else if(attributeName == "dataSize")
				        {
				        	//
				        }				        
				        else if(attributeName == "dataValue1")
				        {
				        	//
				        }
				        else if(attributeName == "delay")
				        {
				        	//
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
			    
			}	    	

			std::cout << "[OK]\t"<<mFile<<" test case loading succeeded"<<std::endl;			
	    }
	}

private:
	std::string mFile;

};

#endif