.. This work is licensed under a Creative Commons Attribution 4.0 International License.
   2 .. SPDX-License-Identifier: CC-BY-4.0
   3 .. Copyright (C) 2020 AT&T
   4 
   5 ============================================================================================ 
   6 HelloWorld xAPP (C++) 
   7 ============================================================================================ 
   8 -------------------------------------------------------------------------------------------- 
   9 User's Guide 
  10 -------------------------------------------------------------------------------------------- 
  11  
  12 Introduction 
  13 ============================================================================================ 
  14 
  15 The RIC platform provides set of functions that the xAPPs can use to accomplish their tasks. 
  16 The HW xAPP is envisioned to provide xAPP developers, examples of implementing these sets of functions. 
  17 Note, HW xAPP does not address/implement any RIC Usecases. 
  18 
  19 HelloWorld xAPP Features 
  20 ============================================================================================ 
  21 
  22 RIC Platform provides many APIs and libraries to aid the development of xAPPs. All xAPPs will have some custom 
  23 processing functional logic core to the xApp and some additional non-functional platform related processing using 
  24 these APIs and libraries. HW xAPP attempts to show the usage of such additional platform processing using RIC platform APIs and libraries.
  25 
  26 
  27 The Hello World xApp demonstrates how an xApp uses the A1, and E2 interfaces and persistent database read-write operations.
  28 The following paragraphs cover the various steps involved to create an HelloWorld xApp instance, setting its configuration,
  29 retrieving R-NIB data, sending subscription, connecting SDL, RME & A1 Healthcheck and usage of "Hello World SM"
  30 
  31 HelloWorld Creation
  32 ============================================================================================ 
  33  
  34 The creation of the xApp instance is as simple as invoking 
  35 the object's constructor with two required parameters: 
  36 
  37 
  38 HW xAPP, may choose to create following objects for obtaining desired set of functionalities provided under xapp-utils:
  39 
  40 XappRmr
  41 -------------------------------------------------------------------------------------------- 
  42 An xAPP can have the capability of receiving and sending rmr messages. This is achieved by creating an XappRmr object. The constructor of xAPPRMR object requires xAPP developer to provide  
  43 xAPP's listening port and developer configurable number of attempts need to be made to send the message. The key functionalities of the class being :
  44         
  45 1. Setting RMR initial context: ...xapp_rmr_init(...)
  46         
  47 2. Sending RMR message: ...xapp_rmr_send(xapp_rmr_header, void*)
  48         
  49 3. Receiving RMR message: ...xapp_rmr_receive(msghandler,...)
  50 
  51 The RMR Header can be defined using xapp_rmr_header :
  52 ::   
  53 
  54         typedef struct{
  55                         struct timespec ts;
  56                         int32_t message_type; //mandatory
  57                         int32_t state;
  58                         int32_t payload_length; //mandatory
  59                         unsigned char sid[RMR_MAX_SID]; 
  60                         unsigned char src[RMR_MAX_SRC]; 
  61                         unsigned char meid[RMR_MAX_MEID];
  62 
  63                 }  xapp_rmr_header;
  64 
  65 Except for message type and payload length, its developers prerogative to use remaining header information. 
  66 The XappMsgHandler (msghandler) instance in xapp_rmr_receive function handles received messages. The handling of messages is based on
  67 the usecase catered by a xAPP. Hence, XappMsgHandler class used in HW xAPP is not very comprehensive and addresses only Healthcheck Messages.
  68 
  69 XappSettings
  70 ------------------------------------------------------------------------------------------- 
  71 An xAPP has the capability to use environment variables or xapp-descriptor information as its configuration settings 
  72 creating XappSettings object, whose key functions being :
  73         
  74 1. Loading Default Settings: ...loadDefaultSettings()
  75         
  76 2. Loading Environment Variables: ...loadEnvVarSettings()
  77         
  78 3. Loading Command Line Settings: ...loadCmdlineSettings(argc, argv)
  79 
  80 XappSDL
  81 -------------------------------------------------------------------------------------------- 
  82 An xAPP can have the capability to read and write into a persistent storage (key-value store) creating XappSDL object. 
  83 for a namespace. The key functionalities available currently are: 
  84 
  85 
  86 1. Getting Data from SDL: ... get_data(...);
  87 
  88 2. Setting Data to SDL: ... set_data(...);      
  89 
  90 The HW xAPP can be instantiationed as following:
  91 ::
  92 
  93         HW_Xapp = Xapp(XappRmr object, XappSettings object,...);
  94 
  95 
  96 HelloWorld E2 and A1 Message Handling
  97 ============================================================================================ 
  98 Helper Objects
  99 -------------------------------------------------------------------------------------------- 
 100 HW xAPP creates wrapper datastructures mirroring ASN and JSON messages. These datastructures facilitate processing of 
 101 E2 and A1 messages in the xAPP. A sample  helper object for A1 Health Check message being:
 102 ::
 103 
 104         struct a1_policy_helper{
 105                 std::string operation;
 106                 std::string policy_type_id;
 107                 std::string policy_instance_id;
 108                 std::string handler_id;
 109                 std::string status;
 110         };
 111 
 112 And a sample E2AP Control datastructure:
 113 ::
 114 
 115         struct ric_control_helper{
 116                 ric_control_helper(void):req_id(1), req_seq_no(1), func_id(0), action_id(1), control_ack(-1), cause(0), sub_cause(0), control_status(1), control_msg(0), control_msg_size(0), control_header(0), control_header_size(0), call_process_id(0), call_process_id_size(0){};
 117                 long int req_id, req_seq_no, func_id, action_id,  control_ack, cause, sub_cause, control_status;
 118   
 119                 unsigned char* control_msg;
 120                 size_t control_msg_size;
 121   
 122                 unsigned char* control_header;
 123                 size_t control_header_size;
 124   
 125                 unsigned char *call_process_id;
 126                 size_t call_process_id_size;
 127   
 128         };
 129 
 130 As mentioned, these datastructures are very much tied to the message specifications.
 131 
 132 
 133 
 134 ASN Encoding/Decoding
 135 -------------------------------------------------------------------------------------------- 
 136 RIC platform provided ASN1C (modified) library is used for processing ASN1 messages. HW xAPP, for each 
 137 ASN message type, uses a class which is responsible for handling a particular message type.
 138 The class encapsulates, the APIs and datastructures used in ASN1C using helper objects. For example:
 139 ::
 140 
 141         class ric_control_response{
 142                 ...
 143                 bool encode_e2ap_control_response(..., ric_control_helper &);
 144                 bool set_fields(..., ric_control_helper &);
 145                 bool get_fields(..., ric_control_helper &);
 146                 ...
 147         }
 148 
 149 Note, the helper objects and message type processing classes can be found under xapp-asn subdirectories.
 150 
 151 E2AP Subscription
 152 -------------------------------------------------------------------------------------------- 
 153 In HW xAPP, we consider sunny-side scenario, in which for a E2AP subscription request sent, it is assumed, 
 154 that HW xAPP will be receiving E2AP subscription response. Handling advanced subscription (class SubscriptionHandler) flows is out of the 
 155 scope of HW xAPP. Current form of class SubscriptionHandler has following key functionalities:
 156 
 157 1. manage_subscription_request(...)
 158 
 159 2. manage_subscription_response(...)
 160 
 161 
 162 The manage_subscription_request function waits for the response for a specified time for subscription response 
 163 and if no response is received within a specified time, gives a time out error message. A subscription message 
 164 is created using ASN Encodong/Decoding and Helper classes. (Refer test_sub.h). HW xAPP sends the subscriptions based 
 165 on the gNodeB IDs received from RNIB. Please refer following function in xapp.* for RNIB transactions: set_rnib_gnblist(...) 
 166 
 167 
 168 E2SM Subscription, Indication, Control
 169 -------------------------------------------------------------------------------------------- 
 170 HellowWorld E2SM (e2sm-HelloWorld-v001.asn) is an example E2SM available in the docs directory. The Helper and 
 171 encoding/decoding classes are in xapp-asn/e2sm. Sample code for control message E2SM:
 172 ::
 173 
 174         //ControlHeader 
 175         unsigned char header_buf[128];
 176         size_t header_buf_len = 128;
 177 
 178         //ControlMessage
 179         unsigned char msg_buf[128];
 180         size_t msg_buf_len = 128;
 181 
 182         bool res;
 183         
 184         e2sm_control_helper e2sm_cntrldata; //helper object
 185         e2sm_control e2sm_cntrl; //encoding/decoding object
 186 
 187         unsigned char msg[20] = "HelloWorld";
 188 
 189         e2sm_cntrldata.header = 1001;
 190         e2sm_cntrldata.message = msg;
 191         e2sm_cntrldata.message_len = strlen((const char*)e2sm_cntrldata.message);
 192 
 193 
 194         // Encode the control header
 195         res = e2sm_cntrl.encode_control_header(&header_buf[0], &header_buf_len, e2sm_cntrldata);
 196         if(!res)
 197                 std::cout << e2sm_cntrl.get_error() << std::endl;
 198         
 199         // Encode the control message
 200         res = e2sm_cntrl.encode_control_message(&msg_buf[0], &msg_buf_len, e2sm_cntrldata);
 201         if(!res)
 202                 std::cout << e2sm_cntrl.get_error() << std::endl;
 203 
 204 
 205 RMR and A1 Healtcheck
 206 -------------------------------------------------------------------------------------------- 
 207 On receiving health check request message types (A1_HEALTHCHECK_REQ, RMR_HEALTHCHECK_REQ), HW xAPP sends RMR
 208 response (A1_HEALTHCHECK_RES, RMR_HEALTHCHECK_RESP) adding appropriate responses using RMR Return to Sender
 209 functionality.  
