/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2014 Regents of the University of California.
 *
 * @author Lijing Wang <phdloli@ucla.edu>
 */

#ifndef CONSUMER_HPP
#define CONSUMER_HPP
#include "consumer-callback.hpp"
#include <pthread.h>
#include <ndn-cxx/security/validator.hpp>

namespace ndn{

#define IDENTITY_NAME "/Lijing/Wang"
  
  class Verificator
  {
  public:
    Verificator()
    {
      Name identity(IDENTITY_NAME);
      Name keyName = m_keyChain.getDefaultKeyNameForIdentity(identity);
      m_publicKey = m_keyChain.getPublicKey(keyName); 
    };
    
    bool
    onPacket(Data& data)
    {
    //  return true;
      if (Validator::verifySignature(data, *m_publicKey))
      {
        std::cout << "Verified Name:" << data.getName() <<  std::endl;
        return true;
      }
      else
      {
        std::cout << "NOT Verified" << data.getName() << std::endl;
        return false;
      }
    }
    
  private:
    KeyChain m_keyChain;
    shared_ptr<PublicKey> m_publicKey;
  };

  struct Consumer_Need
  {
    std::string filename;
    std::string name;
    ConsumerCallback *cb;
  };

  static void
  *consume_thread (void * threadData)
  {
    Verificator* verificator = new Verificator();
    Consumer_Need *con;
    con = (Consumer_Need *) threadData;
    int end;
    int sleeptime;

    Name sampleName(con->filename + "/" + con->name + "/" + "content");

    Consumer* sampleConsumer = new Consumer(sampleName, RDR);

    if(con->name == "video")
    {
//      sampleConsumer->setContextOption(EMBEDDED_MANIFESTS, true);
//      sampleConsumer->setContextOption(CONTENT_RETRIEVAL_SIZE, 1024*1024);
//      sampleConsumer->setContextOption(MIN_WINDOW_SIZE, 8);
      sampleConsumer->setContextOption(CONTENT_RETRIEVED, 
                          (ConsumerContentCallback)bind(&ConsumerCallback::processPayload, con->cb, _1, _2, _3));

      ndn::shared_ptr<Face> f1;
      sampleConsumer->getContextOption(FACE, f1);
//      std::cout << " Video Face = " << f1 << std::endl;

      end = con->cb->finalframe_video;
      sleeptime = 3;
    }else
    {
      sampleConsumer->setContextOption(CONTENT_RETRIEVED, 
                          (ConsumerContentCallback)bind(&ConsumerCallback::processPayloadAudio, con->cb, _1, _2, _3));
      ndn::shared_ptr<Face> f2;
      sampleConsumer->getContextOption(FACE, f2);
//      std::cout << " Audio Face = " << f2 << std::endl;
      sleeptime = 0;
      end = con->cb->finalframe_audio;
    }
        
    sampleConsumer->setContextOption(MUST_BE_FRESH_S, true);
    sampleConsumer->setContextOption(INTEREST_LIFETIME, 200);

//    sampleConsumer->setContextOption(INTEREST_RETX,5); //Retransmitted Attempted Time.
   // there is no need for other callback now
//    sampleConsumer->setContextOption(DATA_TO_VERIFY,
//                    (DataVerificationCallback)bind(&Verificator::onPacket, verificator, _1));
//    sampleConsumer->setContextOption(MIN_WINDOW_SIZE, 1);
    sampleConsumer->setContextOption(INTEREST_LEAVE_CNTX, 
                              (ConsumerInterestCallback)bind(&ConsumerCallback::processLeavingInterest, con->cb, _1, _2));
    sampleConsumer->setContextOption(INTEREST_RETRANSMIT, 
                              (ConsumerInterestCallback)bind(&ConsumerCallback::onRetx, con->cb, _1, _2));
    sampleConsumer->setContextOption(DATA_ENTER_CNTX, 
                              (ConsumerDataCallback)bind(&ConsumerCallback::processData, con->cb, _1, _2));

    
    for (int i=0; i<end; i++)
    { 
      Name sampleSuffix(std::to_string(i));
      sampleConsumer->consume(sampleSuffix);
//      if(i % 500 == 0)
//      {
//        std::cout << "Time Reached!" << i << std::endl;
//        sleep(sleeptime);
//      }
    }
    pthread_exit(NULL);
  }
}
#endif
