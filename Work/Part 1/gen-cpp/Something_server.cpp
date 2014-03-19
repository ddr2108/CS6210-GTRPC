// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "Something.h"
#include <math.h>
#include <curl/curl.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

using namespace ::Test;

//////////////////////////////////////////////////////////////////////////////////////////////////////
//Cache entry Structure
typedef struct _cacheEntry{
	std::string url;
	std::string data;
	int size;
	int valid;
	int timeStamp;
} cacheEntry;
//////////////////////////////////////////////////////////////////////////////////////////////////////
//Hash table structure for maintaining cache
class SimpleHash {
private:
	// data
	cacheEntry* cacheData;
	// hash table size
	unsigned int cacheLength;
	//Size in bytes
	int cacheCurBytes = 0;
	int cacheBytes = 170000;
	//Next timestamp
	int timeStamp = 0;

	// djb2 hash function
	int djb2(const char* key) {
		unsigned int hash = 5381;	//Initial hash

		//Hash function
		for (int i = 0; i < strlen(key); i++)
			hash = ((hash << 5) + hash) + (int)key[i];

        	return hash%cacheLength;
    	}

public:
	//Constructor function
	SimpleHash(unsigned int size): cacheLength(size) {
		// init hash table data given table size
		cacheData = new cacheEntry[cacheLength];
    	}

	//Deconstructor
	~SimpleHash() {
		delete[] cacheData;
	}

	//overload = operator
	SimpleHash& operator=(int byteSize){
		cacheBytes = byteSize;	//Set size limit

		return *this;
	}

	//Add to hash table
	void set(std::string& key, std::string& value) {
		if (value.size()>cacheBytes){
			return;		//if size of page is larger then cache, return
		}	
				
		cacheCurBytes += value.size();	//add to cache
		std::cout<<cacheCurBytes<<"\n";

		int indexDelete;
		while (cacheCurBytes>cacheBytes){
			indexDelete = rand()%cacheLength;	//generate index to delete
			if (cacheData[indexDelete].valid==1 && cacheData[indexDelete].size>0){
				cacheCurBytes-=cacheData[indexDelete].size;
				cacheData[indexDelete].url = "";
				cacheData[indexDelete].data = "";
				cacheData[indexDelete].size = 0;
				cacheData[indexDelete].valid = 0;
			}

		}

		std::cout<<cacheCurBytes<<"\n";

		//Get hash index
		int index = djb2(key.c_str());

		//Set up data in table
		cacheData[index].url = key;
		cacheData[index].data = value;
		cacheData[index].size = value.size();
		cacheData[index].valid = 1;
		cacheData[index].timeStamp = timeStamp++;
	}

	//Pull data from hash table
	std::string get(std::string& key) {
		std::string returnString  = "";		//String to return

		//Get index in hash table
		int index = djb2(key.c_str());

		//If data entry valid, return string
		if (cacheData[index].valid==1 && cacheData[index].size>0){
			returnString = cacheData[index].data;
			//cacheData[index].timeStamp = timeStamp++;	//change to newer timestamp - good for LRU
		}
	
		return returnString;
	}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////
//Handler for Proxy
class SomethingHandler : virtual public SomethingIf {
public:
 
	SimpleHash cacheTable = 1000;		//Hash table of size 1000

	//Constructor
	SomethingHandler(int size) {
		//Set number of bytes in cacheTable
		cacheTable = size;

	}
 	
	//Add data to cache
	void addToCache(std::string url, std::string curlData){
		cacheTable.set(url, curlData);	//put in hash table for cache
	}

	//Get data from cache
	std::string getFromCache(std::string url){
		return cacheTable.get(url);	//return data obtained
	}

	//Create string from data obtained from curl
	static size_t write_to_string(void *ptr, size_t size, size_t count, std::string *stream) {
		stream->append((char*)ptr, 0, size*count);
		return size*count;
	}

	void time(std::string& _return, const std::string& url) {
		//Curl variables 
		CURL *curl;
		CURLcode res;
		std::string response;
	
		response=getFromCache(url);	//Get data from cache
		if (response.empty()){		//if not in the cache
std::cout<<"in\n";
	    		//Do curl
			curl = curl_easy_init();
			if(curl) {	//if succeeded
				curl_easy_setopt(curl, CURLOPT_URL, url.c_str());	//set url
				curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);	//follow redirect
				//Save response to string response
				curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_to_string);
				curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

				// Perform the request, res will get the return code 
				res = curl_easy_perform(curl);
				// Check for errors 
				if(res != CURLE_OK){
		  			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
	 			}

				// always cleanup 
				curl_easy_cleanup(curl);
			}
			//Add respose to cache
			addToCache(url, response);
	}
std::cout<<"out\n";
		//Return response
		_return = response;
	}

};
//////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv) {
	int port = 9090;
	shared_ptr<SomethingHandler> handler(new SomethingHandler(atoi(argv[1])));
	shared_ptr<TProcessor> processor(new SomethingProcessor(handler));
	shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
	shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
	shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

	TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
	server.serve();
	return 0;
}

