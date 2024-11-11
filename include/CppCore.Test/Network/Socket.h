#pragma once

#include <CppCore.Test/Root.h>

#ifndef CPPCORE_NO_SOCKET

#define CPPCORE_TEST_NETWORK_PORT 9999

namespace CppCore { namespace Test { namespace Network
{
   /// <summary>
   /// Tests for Socket.h in CppCore
   /// </summary>
   class Socket
   {
   public:
      INLINE static bool createcloseipv4tcp()
      {
         CppCore::Socket::Op::initSockets();
         CppCore::Socket s(AF_INET, SOCK_STREAM, IPPROTO_TCP);
         bool r = s.getSocket() != INVALID_SOCKET && 0 == s.close();
         CppCore::Socket::Op::shutdownSockets();
         return r;
      }
      INLINE static bool createcloseipv6tcp()
      {
         CppCore::Socket::Op::initSockets();
         CppCore::Socket s(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
         bool r = s.getSocket() != INVALID_SOCKET && 0 == s.close();
         CppCore::Socket::Op::shutdownSockets();
         return r;
      }
      INLINE static bool createcloseipv6dstcp()
      {
         CppCore::Socket::Op::initSockets();
         CppCore::Socket s(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
         bool r = s.getSocket() != INVALID_SOCKET && s.setOptionIPv6Only(false) && 0 == s.close();
         CppCore::Socket::Op::shutdownSockets();
         return r;
      }

      INLINE static bool createcloseipv4udp()
      {
         CppCore::Socket::Op::initSockets();
         CppCore::Socket s(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
         bool r = s.getSocket() != INVALID_SOCKET && 0 == s.close();
         CppCore::Socket::Op::shutdownSockets();
         return r;
      }
      INLINE static bool createcloseipv6udp()
      {
         CppCore::Socket::Op::initSockets();
         CppCore::Socket s(AF_INET6, SOCK_DGRAM, IPPROTO_UDP);
         bool r = s.getSocket() != INVALID_SOCKET && 0 == s.close();
         CppCore::Socket::Op::shutdownSockets();
         return r;
      }
      INLINE static bool createcloseipv6dsudp()
      {
         CppCore::Socket::Op::initSockets();
         CppCore::Socket s(AF_INET6, SOCK_DGRAM, IPPROTO_UDP);
         bool r = s.getSocket() != INVALID_SOCKET && s.setOptionIPv6Only(false) && 0 == s.close();
         CppCore::Socket::Op::shutdownSockets();
         return r;
      }

      INLINE static bool setoptsipv4tcp()
      {
         CppCore::Socket::Op::initSockets();
         CppCore::Socket s(AF_INET, SOCK_STREAM, IPPROTO_TCP);
         bool r = false;
         if (s.getSocket() != INVALID_SOCKET)
         {
            r = s.setNoBlock(true)            && // enable  FIONBIO (noblock)
                s.setOptionReuseAddress(true) && // enable  SO_REUSEADDR
                s.setOptionTcpNoDelay(true)   && // enable  TCP_NODELAY
                s.setOptionLinger(false, 0)   && // disable SO_LINGER
                s.setOptionKeepAlive(true)    && // enable  SO_KEEPALIVE
                (0 == s.close());                // Close successfully
            s.close();
         }
         CppCore::Socket::Op::shutdownSockets();
         return r;
      }
      INLINE static bool setoptsipv6tcp()
      {
         CppCore::Socket::Op::initSockets();
         CppCore::Socket s(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
         bool r = false;
         if (s.getSocket() != INVALID_SOCKET)
         {
            r = s.setNoBlock(true)            && // enable  FIONBIO (noblock)
                s.setOptionIPv6Only(false)    && // disable IPV6_V6ONLY (dualstack)
                s.setOptionReuseAddress(true) && // enable  SO_REUSEADDR
                s.setOptionTcpNoDelay(true)   && // enable  TCP_NODELAY
                s.setOptionLinger(false, 0)   && // disable SO_LINGER
                s.setOptionKeepAlive(true)    && // enable  SO_KEEPALIVE
                (0 == s.close());                // Close successfully
            s.close();
         }
         CppCore::Socket::Op::shutdownSockets();
         return r;
      }

      INLINE static bool bindlistenipv4tcp()
      {
         CppCore::Socket::Op::initSockets();
         CppCore::Socket s(AF_INET, SOCK_STREAM, IPPROTO_TCP);
         bool r = false;
         if (s.getSocket() != INVALID_SOCKET)
         {
            sockaddr_in addr;
            memset(&addr, 0, sizeof(addr));
            addr.sin_family = AF_INET;
            addr.sin_addr.s_addr = htonl(INADDR_ANY);
            addr.sin_port = htons(CPPCORE_TEST_NETWORK_PORT);
            r = (SOCKET_ERROR != s.bind((sockaddr*)&addr, sizeof(addr))) && SOCKET_ERROR != s.listen(16) && (0 == s.close());
            s.close();
         }
         CppCore::Socket::Op::shutdownSockets();
         return r;
      }
      INLINE static bool bindlistenipv6tcp()
      {
         CppCore::Socket::Op::initSockets();
         CppCore::Socket s(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
         bool r = false;
         if (s.getSocket() != INVALID_SOCKET)
         {
            sockaddr_in6 addr;
            memset(&addr, 0, sizeof(addr));
            addr.sin6_family = AF_INET6;
            addr.sin6_addr = in6addr_any;
            addr.sin6_port = htons(CPPCORE_TEST_NETWORK_PORT);
            r = (SOCKET_ERROR != s.bind((sockaddr*)&addr, sizeof(addr))) && SOCKET_ERROR != s.listen(16) && (0 == s.close());
            s.close();
         }
         CppCore::Socket::Op::shutdownSockets();
         return r;
      }
      INLINE static bool bindlistenipv6dstcp()
      {
         CppCore::Socket::Op::initSockets();
         CppCore::Socket s(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
         bool r = false;
         if (s.getSocket() != INVALID_SOCKET && s.setOptionIPv6Only(false))
         {
            sockaddr_in6 addr;
            memset(&addr, 0, sizeof(addr));
            addr.sin6_family = AF_INET6;
            addr.sin6_addr = in6addr_any;
            addr.sin6_port = htons(CPPCORE_TEST_NETWORK_PORT);
            r = (SOCKET_ERROR != s.bind((sockaddr*)&addr, sizeof(addr))) && SOCKET_ERROR != s.listen(16) && (0 == s.close());
            s.close();
         }
         CppCore::Socket::Op::shutdownSockets();
         return r;
      }
   };
}}}

#if defined(CPPCORE_COMPILER_MSVC)
namespace CppCore { namespace Test { namespace VS { namespace Network {
   /// <summary>
   /// Visual Studio Test Class
   /// </summary>
   TEST_CLASS(Socket)
   {
   public:
      TEST_METHOD(CREATECLOSEIPV4TCP)   { Assert::AreEqual(true, CppCore::Test::Network::Socket::createcloseipv4tcp()); }
      TEST_METHOD(CREATECLOSEIPV6TCP)   { Assert::AreEqual(true, CppCore::Test::Network::Socket::createcloseipv6tcp()); }
      TEST_METHOD(CREATECLOSEIPV6DSTCP) { Assert::AreEqual(true, CppCore::Test::Network::Socket::createcloseipv6dstcp()); }

      TEST_METHOD(SETOPTSIPV4TCP)       { Assert::AreEqual(true, CppCore::Test::Network::Socket::setoptsipv4tcp()); }
      TEST_METHOD(SETOPTSIPV6TCP)       { Assert::AreEqual(true, CppCore::Test::Network::Socket::setoptsipv6tcp()); }

      TEST_METHOD(CREATECLOSEIPV4UDP)   { Assert::AreEqual(true, CppCore::Test::Network::Socket::createcloseipv4udp()); }
      TEST_METHOD(CREATECLOSEIPV6UDP)   { Assert::AreEqual(true, CppCore::Test::Network::Socket::createcloseipv6udp()); }
      TEST_METHOD(CREATECLOSEIPV6DSUDP) { Assert::AreEqual(true, CppCore::Test::Network::Socket::createcloseipv6dsudp()); }
      
      TEST_METHOD(BINDIPV4TCP)   { Assert::AreEqual(true, CppCore::Test::Network::Socket::bindlistenipv4tcp()); }
      TEST_METHOD(BINDIPV6TCP)   { Assert::AreEqual(true, CppCore::Test::Network::Socket::bindlistenipv6tcp()); }
      TEST_METHOD(BINDIPV6DSTCP) { Assert::AreEqual(true, CppCore::Test::Network::Socket::bindlistenipv6dstcp()); }
   };
}}}}
#endif

#endif
