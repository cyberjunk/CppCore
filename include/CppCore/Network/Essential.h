#pragma once

#include <CppCore/Root.h>

// Settings for NetServer/Session/NetClient

#ifndef CPPCORE_BUFFERSIZE_TCP
#define CPPCORE_BUFFERSIZE_TCP   8192  // buffer size, tcp (keep as multiple of 4096)
#endif
#ifndef CPPCORE_BUFFERSIZE_UDP
#define CPPCORE_BUFFERSIZE_UDP   4096  // buffer size, udp (keep as multiple of 4096)
#endif

// Settings for NetServer/Session

#ifndef CPPCORE_NETSERVER_MAXCLIENTS
#define CPPCORE_NETSERVER_MAXCLIENTS  256 // maximum supported clients/sessions , if overwritten you must also adjust fixed size constructor
#endif
#ifndef CPPCORE_NETSERVER_SENDSTUCKDISCTIME
#define CPPCORE_NETSERVER_SENDSTUCKDISCTIME  3000 // milliseconds until a client gets kicked if socket does not recover from WSAEWOULDBLOCK
#endif
#ifndef CPPCORE_NETSERVER_BUFFERCOUNT_TCP
#define CPPCORE_NETSERVER_BUFFERCOUNT_TCP  (CPPCORE_NETSERVER_MAXCLIENTS * 16)  // available tcp messagebuffers for all sessions combined (send+recv)
#endif
#ifndef CPPCORE_NETSERVER_BUFFERCOUNT_UDP
#define CPPCORE_NETSERVER_BUFFERCOUNT_UDP  (CPPCORE_NETSERVER_MAXCLIENTS * 8)  // available udp messagebuffers for all sessions combined (recv)
#endif
#ifndef CPPCORE_NETSERVER_QUEUESIZE_UDP_IN
#define CPPCORE_NETSERVER_QUEUESIZE_UDP_IN   64  // per session, client kicked if full
#endif
#ifndef CPPCORE_NETSERVER_QUEUESIZE_TCP_OUT
#define CPPCORE_NETSERVER_QUEUESIZE_TCP_OUT  32  // per session, client kicked if full,
#endif
#ifndef CPPCORE_NETSERVER_QUEUESIZE_TCP_IN
#define CPPCORE_NETSERVER_QUEUESIZE_TCP_IN   64  // per session, client kicked if full
#endif
