/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2014 Regents of the University of California.
 *
 * @author Lijing Wang <phdloli@ucla.edu>
 */

#ifndef CONSUMER_HPP
#define CONSUMER_HPP

#include "validator.hpp"
#include <pthread.h>
#include <ndn-cxx/security/validator.hpp>
#include "consumer-callback.hpp"
//#include <boost/thread/thread.hpp>

namespace ndn{

#define IDENTITY_NAME "/Lijing/Wang"

class Verificator
{
public:
  Verificator()
    : m_enable(true)
    , m_hasError(false)
    , m_isRunning(false)
    , m_validator(m_face, ndn::ndns::Validator::DEFAULT_CONFIG_PATH + "/" + "validator-videoplayer.conf")
  {
  };

  bool
  onPacket(Data& data)
  {
    if (m_enable) {
      m_hasError = false;
      m_isRunning = true;
      m_validator.validate(data,
                     bind(&Verificator::onDataValidated, this, _1),
                     bind(&Verificator::onDataValidationFailed, this, _1, _2)
                     );

      try {
         m_face.processEvents(time::milliseconds(-1));
       }
       catch (std::exception& e) {
         std::cout << "Face fails to process events: " << e.what() << std::endl;
       }

      return m_hasError;
    }
    else
      return true;
  }

  void
  setEnable(bool enable)
  {
    m_enable = enable;
  }

  void
  onDataValidated(const shared_ptr<const Data>& data)
  {
    std::cout << " * final data pass verification" << std::endl;
    m_isRunning = false;
    m_hasError = false;
  }

  void
  onDataValidationFailed(const shared_ptr<const Data>& data, const std::string& str)
  {
    std::cout << " * final data does not pass verification" << std::endl;
    m_hasError = true;
    m_isRunning = false;
  }

private:
  bool m_enable;
  bool m_hasError;
  bool m_isRunning;
  ndn::Face m_face;
  ndn::ndns::Validator m_validator;
};
/*
class Verificator
{
};

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
*/
struct Consumer_Need
{
  std::string filename;
  std::string name;
  ConsumerCallback *cb;
};

static void
*consume_thread (void * threadData)
{
  //Face face;


  Consumer_Need *con;
  con = (Consumer_Need *) threadData;
  int end;
  int sleeptime;

  Name sampleName(con->filename + "/" + con->name + "/" + "content");

  Consumer* sampleConsumer = new Consumer(sampleName, RELIABLE, SEQUENCE);

  if(con->name == "video")
    {
      //      sampleConsumer->setContextOption(EMBEDDED_MANIFESTS, true);
      sampleConsumer->setContextOption(CONTENT_RETRIEVAL_SIZE, 1024*1024);
      sampleConsumer->setContextOption(CONTENT_RETRIEVED,
                                       (ContentCallback)bind(&ConsumerCallback::processPayload, con->cb, _1, _2));

      end = 1000000;
      sleeptime = 100;
      if (ndn::ndns::Validator::ENABLE_NDNS_BASED_VALIDATOR == 1) {
        // shared_ptr<Face> facep;
        // sampleConsumer->getContextOption(FACE, facep);
        Verificator* verificator = new Verificator();
        sampleConsumer->setContextOption(DATA_TO_VERIFY,
                                         (DataVerificationCallback)bind(&Verificator::onPacket, verificator, _1));

      }
    }else
    {
      sampleConsumer->setContextOption(CONTENT_RETRIEVED,
                                       (ContentCallback)bind(&ConsumerCallback::processPayloadAudio, con->cb, _1, _2));
      end = 1000000;
      sleeptime = 0;
    }

  sampleConsumer->setContextOption(MUST_BE_FRESH_S, true);
  sampleConsumer->setContextOption(INTEREST_LIFETIME, 200);
  //    sampleConsumer->setContextOption(INTEREST_RETX,5); //Retransmitted Attempted Time.
  // there is no need for other callback now


  //    sampleConsumer->setContextOption(MIN_WINDOW_SIZE, 1);
  sampleConsumer->setContextOption(INTEREST_LEAVE_CNTX,
                                   (InterestCallback)bind(&ConsumerCallback::processLeavingInterest, con->cb, _1));
  sampleConsumer->setContextOption(INTEREST_RETRANSMIT,
                                   (InterestCallback)bind(&ConsumerCallback::onRetx, con->cb, _1));
  sampleConsumer->setContextOption(DATA_ENTER_CNTX,
                                   (DataCallback)bind(&ConsumerCallback::processData, con->cb, _1));


  for (int i=0; i<end; i++)
    {
      Name sampleSuffix(std::to_string(i));
      sampleConsumer->consume(sampleSuffix);
      usleep(sleeptime);
    }
  pthread_exit(NULL);
}
}
#endif
