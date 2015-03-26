/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2014 Regents of the University of California.
 *
 * @author Lijing Wang <phdloli@ucla.edu>
 */


#ifndef CONSUMER_CALLBACK_HPP
#define CONSUMER_CALLBACK_HPP
#include <ndn-cxx/contexts/consumer-context.hpp>
#include <fstream>
#include <iostream>
#include "video-player.hpp"

// Enclosing code in ndn simplifies coding (can also use `using namespace ndn`)
namespace ndn {
// Additional nested namespace could be used to prevent/limit name contentions

  class ConsumerCallback
  {
      
  public:
    ConsumerCallback();
    
    void
    processPayload(Consumer& con, const uint8_t* buffer, size_t bufferSize);
    
    void
    processStreaminfo(Consumer& con, const uint8_t* buffer, size_t bufferSize);

    void
    processPayloadAudio(Consumer& con, const uint8_t* buffer, size_t bufferSize);
    
    void
    processStreaminfoAudio(Consumer& con, const uint8_t* buffer, size_t bufferSize);
    
    void
    processData(Consumer& con, const Data& data);
    
    bool
    verifyData(Consumer& con, Data& data);
    
    void
    processConstData(Consumer& con, const Data& data);
    
    void
    processLeavingInterest(Consumer& con, Interest& interest);
    
    void
    processList(Consumer& con, const uint8_t* buffer, size_t bufferSize);


    void
    onRetx(Consumer& con, Interest& interest)
    {
      std::cout << "Retransmitted " << interest.getName() << std::endl;
    }

    void
    processFile(Consumer& con, const uint8_t* buffer, size_t bufferSize)
    {
      std::ofstream filestr;
    	// binary open
      
    	filestr.open ("/Users/lijing/next-ndnvideo/build/haha.mp3",  std::ios::out | std::ios::app | std::ios::binary);
      filestr.write((char *)buffer, bufferSize);
      filestr.close();
 
    }

    VideoPlayer player;
    std::vector<std::string> list;
    boost::condition_variable cond;
    boost::mutex mut;
    bool data_ready;
    int finalframe_video;
    int finalframe_audio;
  };

} // namespace ndn
#endif
