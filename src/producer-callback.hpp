/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/**
 * Copyright (c) 2014 Regents of the University of California.
 *
 * @author Lijing Wang <phdloli@ucla.edu>
 */
#ifndef PRODUCER_CALLBACK_HPP
#define PRODUCER_CALLBACK_HPP
#include <ndn-cxx/contexts/producer-context.hpp>
#include <ndn-cxx/contexts/application-nack.hpp>
namespace ndn {
// Additional nested namespace could be used to prevent/limit name contentions
  class ProducerCallback
  {
  public:
    ProducerCallback();
    
    void
    setProducer(Producer* p);
    
    void
    setSampleNumber(size_t* n);

    void
    processConstData(Producer& pro, const Data& data);
    
    void
    processInterest(Producer& pro, const Interest& interest);
    
    void
    processOutgoingData(Producer& pro, const Data& data)
    {
      std::cout << "OutgoingData " << data.getName() << std::endl;
//      std::cout << data.getFinalBlockId() << std::endl;
    }
    void
    processIncomingInterest(Producer& pro, const Interest& interest);
    
    bool
    verifyInterest(Interest& interest);
    
    void
    processConstInterest(Producer& pro, const Interest& interest);

    void
    generateList(Producer& pro, const Interest& interest);
    
    std::string
    getFilename();
  
    std::string filepath;
    std::string prefix;

  private:
    Producer* m_producer;
    size_t* m_curnum;
  };
  
} // namespace ndn
#endif
