#include "Something.h"
#include <curl/curl.h>
#include <transport/TSocket.h>
#include <transport/TBufferTransports.h>
#include <protocol/TBinaryProtocol.h>
#include <string.h>

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using namespace Test;

int main(int argc, char **argv) {
  boost::shared_ptr<TSocket> socket(new TSocket("localhost", 9090));
  boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
  boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));

  SomethingClient client(protocol);
  transport->open();

  std::string url = "www.google.com";
  std::string data;
  client.time(data, url);

  url = "www.yahoo.com";
  client.time(data, url);

  url = "www.google.com";
  client.time(data, url);

  url = "www.yahoo.com";
  client.time(data, url);
  
  transport->close();

  return 0;
}
