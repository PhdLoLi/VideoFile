/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/**
 * Copyright (c) 2014 Regents of the University of California.
 *
 * @author Lijing Wang phdloli@ucla.edu
 */

#include "consumer.hpp"

// Enclosing code in ndn simplifies coding (can also use `using namespace ndn`)
namespace ndn {
// Additional nested namespace could be used to prevent/limit name contentions

  int
  main(int argc, char** argv)
  {
    try {
  
  		std::string prefix = "/ndn/ucla/recordvideo/";
      std::string filename;
      ConsumerCallback cb_consumer;

      Name listName(prefix + "list");
      Consumer* listConsumer = new Consumer(listName, SDR);
      listConsumer->setContextOption(MUST_BE_FRESH_S, true);
      listConsumer->setContextOption(RIGHTMOST_CHILD_S, true);
      listConsumer->setContextOption(INTEREST_LEAVE_CNTX, 
        (ConsumerInterestCallback)bind(&ConsumerCallback::processLeavingInterest, &cb_consumer, _1, _2));
      listConsumer->setContextOption(CONTENT_RETRIEVED, 
        (ConsumerContentCallback)bind(&ConsumerCallback::processList, &cb_consumer, _1, _2, _3));
      listConsumer->setContextOption(DATA_ENTER_CNTX, 
        (ConsumerDataCallback)bind(&ConsumerCallback::processData, &cb_consumer, _1, _2));
  		if(argc < 2 )
      {

        listConsumer->consume(Name("all"));

        sleep(3000);
        return 1;
      }
  		else
      {
  			filename = argv[1];
        listConsumer->consume(Name("file/"+filename));
        sleep(1);
      }


//      ConsumerCallback cb_consumer;

      Name videoinfoName(prefix + filename + "/video/streaminfo");
      Consumer* videoinfoConsumer = new Consumer(videoinfoName, SDR);
      videoinfoConsumer->setContextOption(MUST_BE_FRESH_S, true);
      videoinfoConsumer->setContextOption(INTEREST_LEAVE_CNTX, 
        (ConsumerInterestCallback)bind(&ConsumerCallback::processLeavingInterest, &cb_consumer, _1, _2));
      videoinfoConsumer->setContextOption(CONTENT_RETRIEVED, 
        (ConsumerContentCallback)bind(&ConsumerCallback::processStreaminfo, &cb_consumer, _1, _2, _3));

      videoinfoConsumer->consume(Name());

      Name audioinfoName(prefix + filename + "/audio/streaminfo");
      Consumer* audioinfoConsumer = new Consumer(audioinfoName, SDR);
      audioinfoConsumer->setContextOption(MUST_BE_FRESH_S, true);
      audioinfoConsumer->setContextOption(INTEREST_LEAVE_CNTX, 
        (ConsumerInterestCallback)bind(&ConsumerCallback::processLeavingInterest, &cb_consumer, _1, _2));
      audioinfoConsumer->setContextOption(CONTENT_RETRIEVED, 
        (ConsumerContentCallback)bind(&ConsumerCallback::processStreaminfoAudio, &cb_consumer, _1, _2, _3));

      audioinfoConsumer->consume(Name());

      sleep(1); // because consume() is non-blocking
      std::cout << "consume whole start!" <<std::endl;

      time_t time_start_0 = std::time(0);
      std::cout << "Before consume " << time_start_0 << std::endl;

      int rc_audio;
      Consumer_Need audioData;
      audioData.filename = prefix + filename;
      audioData.name = "audio";
      audioData.cb = &cb_consumer ;
      pthread_t thread_audio; 
      rc_audio = pthread_create(&thread_audio, NULL, consume_thread , (void *)&audioData);

      int rc_video;
      Consumer_Need videoData;
      videoData.filename = prefix + filename;
      videoData.name = "video";
      videoData.cb = &cb_consumer ;
      pthread_t thread_video; 
      rc_video = pthread_create(&thread_video, NULL, consume_thread , (void *)&videoData);

//      cb_consumer.player.consume_whole(videoConsumer, audioConsumer);
      time_t time_end_0  = std::time(0);
      std::cout << "After consume " << time_end_0 << std::endl;
      double seconds = difftime(time_end_0, time_start_0);
      std::cout << seconds << " seconds have passed" << std::endl;

      sleep(3000); // because consume() is non-blocking
      
    }
    catch(std::exception& e) {
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