/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/**
 * Copyright (c) 2014 Regents of the University of California.
 *
 * @author Lijing Wang <phdloli@ucla.edu>
 */

#include "video-generator.hpp"
#include <dirent.h>
//#include <iostream>
// Enclosing code in ndn simplifies coding (can also use `using namespace ndn`)
namespace ndn {
// Additional nested namespace could be used to prevent/limit name contentions


  int
  main(int argc, char** argv)
  {
    try {
      
      Producer *listProducer;
      ProducerCallback listCB;
      std::string prefix = "/ndn/ucla/recordvideo/";

      listCB.filepath = "/Users/Lijing/Test";
      listCB.prefix = prefix;

      listProducer = new Producer(prefix + "list");
      listCB.setProducer(listProducer); // needed for some callback functionality
//      listProducer->setContextOption(INTEREST_ENTER_CNTX,
//                    (ProducerInterestCallback)bind(&ProducerCallback::generateList, &listCB, _1, _2));
      listProducer->setContextOption(DATA_LEAVE_CNTX,
                    (ProducerDataCallback)bind(&ProducerCallback::processOutgoingData, &listCB, _1, _2));
      listProducer->setContextOption(CACHE_MISS,
                    (ProducerInterestCallback)bind(&ProducerCallback::generateList, &listCB, _1, _2));

//      std::string filelist;
//      filelist = listCB.getFilename(); 
      uint64_t timestamp = toUnixTimestamp(ndn::time::system_clock::now()).count();
      std::string timestamp_str = std::to_string(timestamp);
      std::cout << "Timestamp: " << timestamp_str << std::endl;
      Name timeSuffix("all/" + timestamp_str);
//      listProducer->produce(timeSuffix, (uint8_t *)filelist.c_str(), filelist.size());

      listProducer->attach();

 
//      /* VideoProducer Init */
//      Producer *streaminfovideoProducer;
//      Producer *samplevideoProducer;
//      ProducerCallback streaminfovideoCB;
//      ProducerCallback samplevideoCB;
//
//      Name videoName_streaminfo(prefix + "video/streaminfo");
//      /* streaminfoFrameProducer */
//      streaminfovideoProducer = new Producer(videoName_streaminfo);
//      streaminfovideoCB.setProducer(streaminfovideoProducer); // needed for some callback functionality
//      streaminfovideoProducer->setContextOption(INTEREST_ENTER_CNTX,
//                    (ProducerInterestCallback)bind(&ProducerCallback:
//      streaminfovideoProducer->setContextOption(DATA_LEAVE_CNTX,
//          (ProducerDataCallback)bind(&ProducerCallback::processOutgoingData, &streaminfovideoCB, _1, _2));
//      streaminfovideoProducer->attach();
//
//      Signer signer;
//      Name videoName_content(prefix + "video/content");
//      samplevideoProducer = new Producer(videoName_content);
//      samplevideoCB.setProducer(samplevideoProducer); // needed for some callback functionality
//      samplevideoCB.setSampleNumber(&samplenumber);
//
////      sampleProducer->setContextOption(DATA_TO_SECURE,
////                      (DataCallback)bind(&Signer::onPacket, &signer, _1));
//      samplevideoProducer->setContextOption(INTEREST_ENTER_CNTX,
//                      (ProducerInterestCallback)bind(&ProducerCallback::processIncomingInterest, &samplevideoCB, _1, _2));
//      samplevideoProducer->setContextOption(DATA_LEAVE_CNTX,
//          (ProducerDataCallback)bind(&ProducerCallback::processOutgoingData, &samplevideoCB, _1, _2));
//      samplevideoProducer->setContextOption(CACHE_MISS,
//                        (ProducerInterestCallback)bind(&ProducerCallback::processInterest, &samplevideoCB, _1, _2));
//      samplevideoProducer->attach();          
//
//      /* AudioProducer Init */
//      Producer *streaminfoaudioProducer;
//      Producer *sampleaudioProducer;
//      ProducerCallback streaminfoaudioCB;
//      ProducerCallback sampleaudioCB;
//
//      Name audioName_streaminfo(prefix + "audio/streaminfo");
//      /* streaminfoFrameProducer */
//      streaminfoaudioProducer = new Producer(audioName_streaminfo);
//      streaminfoaudioCB.setProducer(streaminfoaudioProducer); // needed for some callback functionality
//      streaminfoaudioProducer->setContextOption(INTEREST_ENTER_CNTX,
//                    (ProducerInterestCallback)bind(&ProducerCallback::processIncomingInterest, &streaminfoaudioCB, _1, _2));
//      streaminfoaudioProducer->setContextOption(DATA_LEAVE_CNTX,
//          (ProducerDataCallback)bind(&ProducerCallback::processOutgoingData, &streaminfoaudioCB, _1, _2));
//      streaminfoaudioProducer->attach();
//
//      Name audioName_content(prefix + "audio/content");
//      sampleaudioProducer = new Producer(audioName_content);
//      sampleaudioCB.setProducer(sampleaudioProducer); // needed for some callback functionality
//      sampleaudioCB.setSampleNumber(&samplenumber);
//
////      sampleProducer->setContextOption(DATA_TO_SECURE,
////                      (DataCallback)bind(&Signer::onPacket, &signer, _1));
//      sampleaudioProducer->setContextOption(INTEREST_ENTER_CNTX,
//                      (ProducerInterestCallback)bind(&ProducerCallback::processIncomingInterest, &sampleaudioCB, _1, _2));
//      sampleaudioProducer->setContextOption(DATA_LEAVE_CNTX,
//          (ProducerDataCallback)bind(&ProducerCallback::processOutgoingData, &sampleaudioCB, _1, _2));
//      sampleaudioProducer->setContextOption(CACHE_MISS,
//                        (ProducerInterestCallback)bind(&ProducerCallback::processInterest, &sampleaudioCB, _1, _2));
//      sampleaudioProducer->attach();          

      
//      generator.h264_generate_whole(filename);
      std::cout << "COOL~" << std::endl;
      sleep(30000); // because attach() is non-blocking
      
      std::cout << "HERE!!" << std::endl;

    }
    catch(std::exception& e) {
      std::cout << "HAHA" << std::endl;
      std::cerr << "ERROR: " << e.what() << std::endl;
      return 1;
    }
    return 0;
  }

} // namespace ndn

int
main(int argc, char** argv)
{
  return ndn::main(argc, argv);
}