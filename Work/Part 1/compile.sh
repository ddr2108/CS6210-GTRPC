thrift --gen cpp rpc.thrift
cp Makefile gen-cpp/
cp Something_client.cpp gen-cpp/
cd gen-cpp
mv Something_server.skeleton.cpp Something_server.cpp 
