.. This work is licensed under a Creative Commons Attribution 4.0 International License.
   2 .. SPDX-License-Identifier: CC-BY-4.0
   3 .. Copyright (C) 2020 AT&T
   4 
   5 
   6 Release Notes
   7 =============
   8 
   9 
  10 This document provides the release notes for the Bronze Release of the HelloWorld (HW) xAPP.
  11 
  12 .. contents::
  13    :depth: 3
  14    :local:
  15 
  16 
  17 Version history
  18 ---------------
  19 
  20 +--------------------+--------------------+--------------------+--------------------+
  21 | **Date**           | **Ver.**           | **Author**         | **Comment**        |
  22 |                    |                    |                    |                    |
  23 +--------------------+--------------------+--------------------+--------------------+
  24 | 2020-06-08         | 1.0.5              |   Shraboni Jana    | Fifth draft        |
  25 |                    |                    |                    |                    |
  26 +--------------------+--------------------+--------------------+--------------------+
  27 
  28 
  29 
  30 Summary
  31 -------
  32 
  33 The Bronze release of the HW xAPP demonstrates E2 and A1 interface interactions, persistent storage read-write, RMR and A1 healthcheck. 
  34 HW xAPP uses its HelloWorld E2SM (can be found at hw/src/xapp-asn/e2sm/) for ASN PDUs.
  35 
  36 
  37 Release Data
  38 ------------
  39 
  40 +--------------------------------------+--------------------------------------+
  41 | **Project**                          | RAN Intelligent Controller           |
  42 |                                      |                                      |
  43 +--------------------------------------+--------------------------------------+
  44 | **Repo/commit-ID**                   |        ric-app/hw                    |
  45 |                                      |                                      |
  46 +--------------------------------------+--------------------------------------+
  47 | **Release designation**              |              Bronze                  |
  48 |                                      |                                      |
  49 +--------------------------------------+--------------------------------------+
  50 | **Release date**                     |      2020-21-05                      |
  51 |                                      |                                      |
  52 +--------------------------------------+--------------------------------------+
  53 | **Purpose of the delivery**          | open-source Hello World xAPP         |
  54 |                                      |                                      |
  55 |                                      |                                      |
  56 +--------------------------------------+--------------------------------------+
  57 
  58 Components
  59 ----------
  60 
  61 - *src/* contains the main source code. Under that directory :
  62   
  63   + *xapp.hpp, xapp.cc* is generic class which implements all the xAPP functionalities for xapp developer to pick and choose.
  64   + *xapp-utils/* contains generic classes for - persistent data management, configuration management, RMR send/receive etc.
  65   + *xapp-asn/* contains generic classes for generating/processing ASN1  E2AP and E2SM messages.
  66   + *xapp-mgmt/* contains code specific xapp management of subscriptions and received messages.
  67 
  68 - *test/* contains unit tests showing how to use various components.
  69 
  70   
  71     
  72 
  73 Limitations
  74 -----------
  75 - The HW xAPP doesn't have any usecase in particular to display SDL capabilities and hence incorporated only in unit tests.
  76 
  77 - The subscription process assumes, on sending subscription request results in valid subscription response. 
  78 
  79 - The HW xAPP doesn't address any RIC usecase in particular.
