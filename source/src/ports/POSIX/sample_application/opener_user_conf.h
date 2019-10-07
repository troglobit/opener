/*******************************************************************************
 * Copyright (c) 2009, Rockwell Automation, Inc.
 * All rights reserved.
 *
 ******************************************************************************/
#ifndef OPENER_USER_CONF_H_
#define OPENER_USER_CONF_H_

/** @file POSIX/sample_application/opener_user_conf.h
 * @brief OpENer configuration setup
 *
 * This file contains the general application specific configuration for OpENer.
 *
 * Furthermore you have to specific platform specific network include files.
 * OpENer needs definitions for the following data-types
 * and functions:
 *    - struct sockaddr_in
 *    - AF_INET
 *    - INADDR_ANY
 *    - htons
 *    - ntohl
 *    - inet_addr
 */
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <assert.h>

#include "typedefs.h"

/** @brief Define the number of objects that may be used in connections
 *
 *  This number needs only to consider additional objects. Connections to
 *  the connection manager object as well as to the assembly object are supported
 *  in any case.
 */
#define OPENER_CIP_NUM_APPLICATION_SPECIFIC_CONNECTABLE_OBJECTS 1

/** @brief Define the number of supported explicit connections.
 *  According to ODVA's PUB 70 this number should be equal or greater than 6.
 */
#define OPENER_CIP_NUM_EXPLICIT_CONNS 6

/** @brief Define the number of supported exclusive owner connections.
 *  Each of these connections has to be configured with the function
 *  void configureExclusiveOwnerConnectionPoint(unsigned int pa_unConnNum, unsigned int pa_unOutputAssembly, unsigned int pa_unInputAssembly, unsigned int pa_unConfigAssembly)
 *
 */
#define OPENER_CIP_NUM_EXLUSIVE_OWNER_CONNS 1

/** @brief  Define the number of supported input only connections.
 *  Each of these connections has to be configured with the function
 *  void configureInputOnlyConnectionPoint(unsigned int pa_unConnNum, unsigned int pa_unOutputAssembly, unsigned int pa_unInputAssembly, unsigned int pa_unConfigAssembly)
 *
 */
#define OPENER_CIP_NUM_INPUT_ONLY_CONNS 1

/** @brief Define the number of supported input only connections per connection path
 */
#define OPENER_CIP_NUM_INPUT_ONLY_CONNS_PER_CON_PATH 3

/** @brief Define the number of supported listen only connections.
 *  Each of these connections has to be configured with the function
 *  void configureListenOnlyConnectionPoint(unsigned int pa_unConnNum, unsigned int pa_unOutputAssembly, unsigned int pa_unInputAssembly, unsigned int pa_unConfigAssembly)
 *
 */
#define OPENER_CIP_NUM_LISTEN_ONLY_CONNS 1

/** @brief Define the number of supported Listen only connections per connection path
 */
#define OPENER_CIP_NUM_LISTEN_ONLY_CONNS_PER_CON_PATH   3

/** @brief Number of sessions that can be handled at the same time
 */
#define OPENER_NUMBER_OF_SUPPORTED_SESSIONS 20

/** @brief The time in ms of the timer used in this implementations, time base for time-outs and production timers
 */
static const MilliSeconds kOpenerTimerTickInMilliSeconds = 10;

#ifdef OPENER_WITH_TRACES
/* If we have tracing enabled provide print tracing macro */
#include <stdio.h>

#define LOG_TRACE(...)  fprintf(stderr,__VA_ARGS__)

/*#define PRINT_TRACE(args...)  fprintf(stderr,args);*/

/** @brief A specialized assertion command that will log the assertion and block
 *  further execution in an while(1) loop.
 */
#ifdef IDLING_ASSERT
#define OPENER_ASSERT(assertion) \
  do { \
    if( !(assertion) ) { \
      LOG_TRACE("Assertion \"%s\" failed: file \"%s\", line %d\n", \
                # assertion, \
                __FILE__, \
                __LINE__); \
      while(1) {  } \
    } \
  } while(0);

/* else use standard assert() */
//#include <assert.h>
//#include <stdio.h>
//#define OPENER_ASSERT(assertion) assert(assertion)
#else
#define OPENER_ASSERT(assertion) assert(assertion);
#endif
#else

/* for release builds remove assertion */
#define OPENER_ASSERT(assertion)

/* if there are any strange timing issues, you can try the version below, where the assertion is performed but the assert
 * function is not used
 */
//#define OPENER_ASSERT(assertion) (assertion)
/* else if you still want assertions to stop execution but without tracing, use the following */
//#define OPENER_ASSERT(assertion) do { if(!(assertion)) { while(1){;} } } while (0)
/* else use standard assert() */
//#include <assert.h>
//#include <stdio.h>
//#define OPENER_ASSERT(assertion) assert(assertion)

#endif

/** @brief The number of bytes used for the Ethernet message buffer on
 * the PC port. For different platforms it may makes sense to
 * have more than one buffer.
 *
 *  This buffer size will be used for any received message.
 *  The same buffer is used for the replied explicit message.
 */
#define PC_OPENER_ETHERNET_BUFFER_SIZE 512

#endif /*OPENER_USER_CONF_H_*/
