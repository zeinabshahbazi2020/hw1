/*
   2 ==================================================================================
   3         Copyright (c) 2019-2020 AT&T Intellectual Property.
   4 
   5    Licensed under the Apache License, Version 2.0 (the "License");
   6    you may not use this file except in compliance with the License.
   7    You may obtain a copy of the License at
   8 
   9        http://www.apache.org/licenses/LICENSE-2.0
  10 
  11    Unless required by applicable law or agreed to in writing, software
  12    distributed under the License is distributed on an "AS IS" BASIS,
  13    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  14    See the License for the specific language governing permissions and
  15    limitations under the License.
  16 ==================================================================================
  17 */
  18 /*
  19  * hw_xapp_main.cc
  20  * Created on: Dec, 2019
  21  * Author: Shraboni Jana
  22  */
  23 
  24 #include "xapp.hpp"
  25 
  26 void signalHandler( int signum ) {
  27    cout << "Interrupt signal (" << signum << ") received.\n";
  28    exit(signum);
  29 }
  30 
  31 int main(int argc, char *argv[]){
  32 
  33         // Get the thread id
  34         std::thread::id my_id = std::this_thread::get_id();
  35         std::stringstream thread_id;
  36         std::stringstream ss;
  37 
  38         thread_id << my_id;
  39 
  40         mdclog_write(MDCLOG_INFO, "Starting thread %s",  thread_id.str().c_str());
  41 
  42         //get configuration
  43         XappSettings config;
  44         //change the priority depending upon application requirement
  45         config.loadDefaultSettings();
  46         config.loadEnvVarSettings();
  47         config.loadCmdlineSettings(argc, argv);
  48 
  49         //Register signal handler to stop
  50         signal(SIGINT, signalHandler);
  51         signal(SIGTERM, signalHandler);
  52 
  53         //getting the listening port and xapp name info
  54         std::string  port = config[XappSettings::SettingName::HW_PORT];
  55         std::string  name = config[XappSettings::SettingName::XAPP_NAME];
  56 
  57         //initialize rmr
  58         std::unique_ptr<XappRmr> rmr = std::make_unique<XappRmr>(port);
  59         rmr->xapp_rmr_init(true);
  60 
  61 
  62         //Create Subscription Handler if Xapp deals with Subscription.
  63         //std::unique_ptr<SubscriptionHandler> sub_handler = std::make_unique<SubscriptionHandler>();
  64 
  65         SubscriptionHandler sub_handler;
  66 
  67         //create HelloWorld Xapp Instance.
  68         std::unique_ptr<Xapp> hw_xapp;
  69         hw_xapp = std::make_unique<Xapp>(std::ref(config),std::ref(*rmr));
  70 
  71         mdclog_write(MDCLOG_INFO, "Created Hello World Xapp Instance");
  72         //Startup E2 subscription and A1 policy
  73         hw_xapp->startup(sub_handler);
  74 
  75         sleep(10);
  76 
  77 
  78         //start listener threads and register message handlers.
  79         int num_threads = std::stoi(config[XappSettings::SettingName::THREADS]);
  80         mdclog_write(MDCLOG_INFO, "Starting Listener Threads. Number of Workers = %d", num_threads);
  81 
  82         std::unique_ptr<XappMsgHandler> mp_handler = std::make_unique<XappMsgHandler>(config[XappSettings::SettingName::XAPP_ID], sub_handler);
  83 
  84         hw_xapp->start_xapp_receiver(std::ref(*mp_handler));
  85 
  86         sleep(1);
  87 
  88 
  89 
  90     //hw_xapp->Run() //for spinning multiple receiving threads.
  91 
  92         //hw_xapp->shutdown();
  93 
  94         while(1){
  95                                 sleep(1);
  96                          }
  97 
  98         return 0;
  99 }
 100 
 101 
 102 
