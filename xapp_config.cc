/*
   2 ==================================================================================
   3 
   4         Copyright (c) 2019-2020 AT&T Intellectual Property.
   5 
   6    Licensed under the Apache License, Version 2.0 (the "License");
   7    you may not use this file except in compliance with the License.
   8    You may obtain a copy of the License at
   9 
  10        http://www.apache.org/licenses/LICENSE-2.0
  11 
  12    Unless required by applicable law or agreed to in writing, software
  13    distributed under the License is distributed on an "AS IS" BASIS,
  14    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  15    See the License for the specific language governing permissions and
  16    limitations under the License.
  17 ==================================================================================
  18  */
  19 /*
  20  * xapp_config.cc
  21  * Created on: 2019
  22  * Author: Ashwin Shridharan, Shraboni Jana
  23  */
  24 
  25 #include "xapp_config.hpp"
  26 
  27 string& XappSettings::operator[](const SettingName& theName){
  28     return theSettings[theName];
  29 }
  30 
  31 void XappSettings::loadCmdlineSettings(int argc, char **argv){
  32 
  33            // Parse command line options to over ride
  34           static struct option long_options[] =
  35             {
  36                         {"xappname", required_argument, 0, 'n'},
  37                                 {"xappid", required_argument, 0, 'x'},
  38                                 {"port", required_argument, 0, 'p'},
  39                                 {"threads", required_argument,    0, 't'},
  40                                 {"ves-interval", required_argument, 0, 'i'},
  41                                 {"gNodeB", required_argument, 0, 'g'}
  42 
  43             };
  44 
  45 
  46            while(1) {
  47 
  48                 int option_index = 0;
  49                 char c = getopt_long(argc, argv, "n:p:t:s:g:a:v:u:i:c:x:", long_options, &option_index);
  50 
  51                 if(c == -1){
  52                     break;
  53                  }
  54 
  55                 switch(c)
  56                   {
  57 
  58                   case 'n':
  59                     theSettings[XAPP_NAME].assign(optarg);
  60                     break;
  61 
  62                   case 'p':
  63                     theSettings[HW_PORT].assign(optarg);
  64                     break;
  65 
  66                   case 't':
  67                         theSettings[THREADS].assign(optarg);
  68                     mdclog_write(MDCLOG_INFO, "Number of threads set to %s from command line e\n", theSettings[THREADS].c_str());
  69                     break;
  70 
  71 
  72                   case 'x':
  73                     theSettings[XAPP_ID].assign(optarg);
  74                     mdclog_write(MDCLOG_INFO, "XAPP ID set to  %s from command line ", theSettings[XAPP_ID].c_str());
  75                     break;
  76 
  77                   case 'h':
  78                     usage(argv[0]);
  79                     exit(0);
  80 
  81                   default:
  82                     usage(argv[0]);
  83                     exit(1);
  84                   }
  85            };
  86 
  87 }
  88 
  89 void XappSettings::loadDefaultSettings(){
  90 
  91 
  92                  if(theSettings[XAPP_NAME].empty()){
  93                   theSettings[XAPP_NAME] = DEFAULT_XAPP_NAME;
  94                   }
  95 
  96                   if(theSettings[XAPP_ID].empty()){
  97                           theSettings[XAPP_ID] = DEFAULT_XAPP_NAME; //for now xapp_id is same as xapp_name since single xapp instance.
  98                   }
  99                   if(theSettings[LOG_LEVEL].empty()){
 100                           theSettings[LOG_LEVEL] = DEFAULT_LOG_LEVEL;
 101                   }
 102                   if(theSettings[HW_PORT].empty()){
 103                           theSettings[HW_PORT] = DEFAULT_PORT;
 104                   }
 105                   if(theSettings[MSG_MAX_BUFFER].empty()){
 106                           theSettings[MSG_MAX_BUFFER] = DEFAULT_MSG_MAX_BUFFER;
 107                   }
 108 
 109                  if(theSettings[THREADS].empty()){
 110                                           theSettings[THREADS] = DEFAULT_THREADS;
 111                                   }
 112 
 113 
 114 }
 115 
 116 void XappSettings::loadEnvVarSettings(){
 117 
 118           if (const char *env_xname = std::getenv("XAPP_NAME")){
 119                   theSettings[XAPP_NAME].assign(env_xname);
 120                   mdclog_write(MDCLOG_INFO,"Xapp Name set to %s from environment variable", theSettings[XAPP_NAME].c_str());
 121           }
 122           if (const char *env_xid = std::getenv("XAPP_NAME")){
 123                    theSettings[XAPP_ID].assign(env_xid);
 124                    mdclog_write(MDCLOG_INFO,"Xapp ID set to %s from environment variable", theSettings[XAPP_ID].c_str());
 125           }
 126 
 127           if (const char *env_ports = std::getenv("HW_PORT")){
 128                   theSettings[HW_PORT].assign(env_ports);
 129                   mdclog_write(MDCLOG_INFO,"Ports set to %s from environment variable", theSettings[HW_PORT].c_str());
 130           }
 131           if (const char *env_ports = std::getenv("MSG_MAX_BUFFER")){
 132                           theSettings[MSG_MAX_BUFFER].assign(env_ports);
 133                           mdclog_write(MDCLOG_INFO,"Ports set to %s from environment variable", theSettings[MSG_MAX_BUFFER].c_str());
 134                   }
 135 
 136 }
 137 
 138 void XappSettings::usage(char *command){
 139         std::cout <<"Usage : " << command << " " << std::endl;
 140         std::cout <<" --name[-n] xapp_instance_name "<< std::endl;
 141     std::cout <<" --port[-p] port to listen on e.g tcp:4561  "<< std::endl;
 142     std::cout << "--threads[-t] number of listener threads "<< std::endl ;
 143 
 144 }
