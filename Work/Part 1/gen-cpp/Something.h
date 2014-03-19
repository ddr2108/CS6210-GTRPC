/**
 * Autogenerated by Thrift Compiler (0.9.1)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef Something_H
#define Something_H

#include <thrift/TDispatchProcessor.h>
#include "rpc_types.h"

namespace Test {

class SomethingIf {
 public:
  virtual ~SomethingIf() {}
  virtual void time(std::string& _return, const std::string& url) = 0;
};

class SomethingIfFactory {
 public:
  typedef SomethingIf Handler;

  virtual ~SomethingIfFactory() {}

  virtual SomethingIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) = 0;
  virtual void releaseHandler(SomethingIf* /* handler */) = 0;
};

class SomethingIfSingletonFactory : virtual public SomethingIfFactory {
 public:
  SomethingIfSingletonFactory(const boost::shared_ptr<SomethingIf>& iface) : iface_(iface) {}
  virtual ~SomethingIfSingletonFactory() {}

  virtual SomethingIf* getHandler(const ::apache::thrift::TConnectionInfo&) {
    return iface_.get();
  }
  virtual void releaseHandler(SomethingIf* /* handler */) {}

 protected:
  boost::shared_ptr<SomethingIf> iface_;
};

class SomethingNull : virtual public SomethingIf {
 public:
  virtual ~SomethingNull() {}
  void time(std::string& /* _return */, const std::string& /* url */) {
    return;
  }
};

typedef struct _Something_time_args__isset {
  _Something_time_args__isset() : url(false) {}
  bool url;
} _Something_time_args__isset;

class Something_time_args {
 public:

  Something_time_args() : url() {
  }

  virtual ~Something_time_args() throw() {}

  std::string url;

  _Something_time_args__isset __isset;

  void __set_url(const std::string& val) {
    url = val;
  }

  bool operator == (const Something_time_args & rhs) const
  {
    if (!(url == rhs.url))
      return false;
    return true;
  }
  bool operator != (const Something_time_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Something_time_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class Something_time_pargs {
 public:


  virtual ~Something_time_pargs() throw() {}

  const std::string* url;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _Something_time_result__isset {
  _Something_time_result__isset() : success(false) {}
  bool success;
} _Something_time_result__isset;

class Something_time_result {
 public:

  Something_time_result() : success() {
  }

  virtual ~Something_time_result() throw() {}

  std::string success;

  _Something_time_result__isset __isset;

  void __set_success(const std::string& val) {
    success = val;
  }

  bool operator == (const Something_time_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const Something_time_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Something_time_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _Something_time_presult__isset {
  _Something_time_presult__isset() : success(false) {}
  bool success;
} _Something_time_presult__isset;

class Something_time_presult {
 public:


  virtual ~Something_time_presult() throw() {}

  std::string* success;

  _Something_time_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

class SomethingClient : virtual public SomethingIf {
 public:
  SomethingClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) :
    piprot_(prot),
    poprot_(prot) {
    iprot_ = prot.get();
    oprot_ = prot.get();
  }
  SomethingClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) :
    piprot_(iprot),
    poprot_(oprot) {
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  void time(std::string& _return, const std::string& url);
  void send_time(const std::string& url);
  void recv_time(std::string& _return);
 protected:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
};

class SomethingProcessor : public ::apache::thrift::TDispatchProcessor {
 protected:
  boost::shared_ptr<SomethingIf> iface_;
  virtual bool dispatchCall(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, const std::string& fname, int32_t seqid, void* callContext);
 private:
  typedef  void (SomethingProcessor::*ProcessFunction)(int32_t, ::apache::thrift::protocol::TProtocol*, ::apache::thrift::protocol::TProtocol*, void*);
  typedef std::map<std::string, ProcessFunction> ProcessMap;
  ProcessMap processMap_;
  void process_time(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
 public:
  SomethingProcessor(boost::shared_ptr<SomethingIf> iface) :
    iface_(iface) {
    processMap_["time"] = &SomethingProcessor::process_time;
  }

  virtual ~SomethingProcessor() {}
};

class SomethingProcessorFactory : public ::apache::thrift::TProcessorFactory {
 public:
  SomethingProcessorFactory(const ::boost::shared_ptr< SomethingIfFactory >& handlerFactory) :
      handlerFactory_(handlerFactory) {}

  ::boost::shared_ptr< ::apache::thrift::TProcessor > getProcessor(const ::apache::thrift::TConnectionInfo& connInfo);

 protected:
  ::boost::shared_ptr< SomethingIfFactory > handlerFactory_;
};

class SomethingMultiface : virtual public SomethingIf {
 public:
  SomethingMultiface(std::vector<boost::shared_ptr<SomethingIf> >& ifaces) : ifaces_(ifaces) {
  }
  virtual ~SomethingMultiface() {}
 protected:
  std::vector<boost::shared_ptr<SomethingIf> > ifaces_;
  SomethingMultiface() {}
  void add(boost::shared_ptr<SomethingIf> iface) {
    ifaces_.push_back(iface);
  }
 public:
  void time(std::string& _return, const std::string& url) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->time(_return, url);
    }
    ifaces_[i]->time(_return, url);
    return;
  }

};

} // namespace

#endif
