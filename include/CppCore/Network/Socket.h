#pragma once

#include <CppCore/Root.h>

// Platform POSIX Socket
#if defined(CPPCORE_OS_WINDOWS)
#define NOMINMAX
#include <WinSock2.h>
#include <ws2ipdef.h>
#include <Ws2tcpip.h>
#include <mstcpip.h>
#undef NOMINMAX
#define socklen_t int
#pragma comment(lib, "Ws2_32.lib")
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <poll.h>
#include <netdb.h>
#define SOCKET int
#define INVALID_SOCKET  (SOCKET)(~0)
#define SOCKET_ERROR    -1
#endif

namespace CppCore
{
   /// <summary>
   /// Socket Wrapper Class using posix API.
   /// </summary>
   class Socket
   {
   public:
      /// <summary>
      /// Direct Access to POSIX Socket API Operations.
      /// </summary>
      class Op
      {
      private:
         INLINE Op() { }
      public:
         /// <summary>
         /// ::WSAStartup() on Windows.
         /// Nothing on others.
         /// </summary>
         static INLINE int initSockets()
         {
         #if defined(CPPCORE_OS_WINDOWS)
            WSADATA wsadat;
            return ::WSAStartup(MAKEWORD(2, 2), &wsadat);
         #else
            return 0;
         #endif
         }

         /// <summary>
         /// ::WSACleanup() on Windows.
         /// Nothing on others.
         /// </summary>
         static INLINE int shutdownSockets()
         {
         #if defined(CPPCORE_OS_WINDOWS)
            return ::WSACleanup();
         #else
            return 0;
         #endif
         }

         /// <summary>
         /// ::socket()
         /// </summary>
         static INLINE SOCKET socket(int af, int type, int protocol)
         {
            return ::socket(af, type, protocol);
         }

         /// <summary>
         /// ::closesocket() on Windows.
         /// ::close() on others.
         /// </summary>
         static INLINE int close(SOCKET s)
         {
         #if defined(CPPCORE_OS_WINDOWS)
            return ::closesocket(s);
         #else
            return ::close(s);
         #endif
         }

         /// <summary>
         /// ::shutdown(SD_BOTH) on Windows.
         /// ::shutdown(SHUT_RDWR) on others.
         /// </summary>
         static INLINE int shutdown(SOCKET s)
         {
         #if defined(CPPCORE_OS_WINDOWS)
            return ::shutdown(s, SD_BOTH);
         #else
            return ::shutdown(s, SHUT_RDWR);
         #endif
         }

         /// <summary>
         /// ::setsockopt()
         /// </summary>
         static INLINE int setsockopt(SOCKET s, int level, int optname, const char* optval, socklen_t optlen)
         {
            return ::setsockopt(s, level, optname, optval, optlen);
         }

         /// <summary>
         /// ::getsockopt()
         /// </summary>
         static INLINE int getsockopt(SOCKET s, int level, int optname, char* optval, socklen_t* optlen)
         {
            return ::getsockopt(s, level, optname, optval, optlen);
         }

         /// <summary>
         /// ::ioctlsocket() on Windows.
         /// ::ioctl() on others.
         /// </summary>
         static INLINE int ioctlsocket(SOCKET s, long cmd, u_long* argp)
         { 
         #if defined(CPPCORE_OS_WINDOWS)
            return ::ioctlsocket(s, cmd, argp);
         #else
            return ::ioctl(s, cmd, argp);
         #endif
         }

         /// <summary>
         /// ::listen()
         /// </summary>
         static INLINE int listen(SOCKET s, int backlog)
         { 
            return ::listen(s, backlog); 
         }

         /// <summary>
         /// ::bind()
         /// </summary>
         static INLINE int bind(SOCKET s, const sockaddr* name, socklen_t namelen)
         { 
            return ::bind(s, name, namelen);
         }

         /// <summary>
         /// ::connect()
         /// </summary>
         static INLINE int connect(SOCKET s, const sockaddr* name, socklen_t namelen)
         {
            return ::connect(s, name, namelen);
         }

         /// <summary>
         /// ::accept()
         /// </summary>
         static INLINE SOCKET accept(SOCKET s, sockaddr* addr, socklen_t* addrlen)
         {
            return ::accept(s, addr, addrlen);
         }

         /// <summary>
         /// Calls accept() on listener socket s and then shutdown() and close() on accepted socket.
         /// </summary>
         static INLINE void acceptAndClose(SOCKET s)
         {
            SOCKET temp(INVALID_SOCKET);
            sockaddr_in6 addr;
            socklen_t addrsize = sizeof(addr);
            temp = Op::accept(s, (sockaddr*)&addr, &addrsize);
            Op::shutdown(temp);
            Op::close(temp);
         }

         /// <summary>
         /// ::sendto()
         /// </summary>
         static INLINE int sendto(SOCKET s, const char* buf, int len, int flags, const sockaddr* to, socklen_t tolen)
         {
            return ::sendto(s, buf, len, flags, to, tolen);
         }

         /// <summary>
         /// ::recvfrom()
         /// </summary>
         static INLINE int recvfrom(SOCKET s, char* buf, int len, int flags, sockaddr* from, socklen_t* fromlen)
         {
            return ::recvfrom(s, buf, len, flags, from, fromlen);
         }

         /// <summary>
         /// ::send()
         /// </summary>
         static INLINE int send(SOCKET s, char* buf, int len, int flags = 0)
         {
            return ::send(s, buf, len, flags);
         }

         /// <summary>
         /// ::recv()
         /// </summary>
         static INLINE int recv(SOCKET s, char* buf, int len, int flags = 0)
         {
            return ::recv(s, buf, len, flags);
         }

         /// <summary>
         /// ::WSAPoll() on Windows. 
         /// ::poll() on others.
         /// </summary>
         static INLINE int poll(pollfd* fdArray, int fds, int timeout)
         {
         #if defined(CPPCORE_OS_WINDOWS)
            return ::WSAPoll(fdArray, fds, timeout);
         #else
            return ::poll(fdArray, fds, timeout);
         #endif
         }

         /// <summary>
         /// ::WSAGetLastError() on Windows.
         /// 'errno' global on others.
         /// </summary>
         /// <returns></returns>
         static INLINE int getLastError()
         {
         #if defined(CPPCORE_OS_WINDOWS)
            return ::WSAGetLastError();
         #else
            return errno;
         #endif
         }

         /// <summary>
         /// True if getLastError() is WSAEWOULDBLOCK on Windows or EWOULDBLOCK on others.
         /// </summary>
         static INLINE bool isLastErrorBlock()
         {
         #if defined(CPPCORE_OS_WINDOWS)
            return getLastError() == WSAEWOULDBLOCK;
         #else
            return errno == EWOULDBLOCK;
         #endif
         }

         /// <summary>
         /// True if getLastError() is WSAEINPROGRESS on Windows or EINPROGRESS on others.
         /// </summary>
         static INLINE bool isLastErrorInProgress()
         {
         #if defined(CPPCORE_OS_WINDOWS)
            return getLastError() == WSAEINPROGRESS;
         #else
            return errno == EINPROGRESS;
         #endif
         }

         /// <summary>
         /// True if getLastError() is WSAESHUTDOWN on Windows or ESHUTDOWN on others.
         /// </summary>
         static INLINE bool isLastErrorShutdown()
         {
         #if defined(CPPCORE_OS_WINDOWS)
            return getLastError() == WSAESHUTDOWN;
         #else
            return errno == ESHUTDOWN;
         #endif
         }
      };

   protected:
      union {
         SOCKET mSocket;
         pollfd mPoll;
      };

   public:
      /// <summary>
      /// Empty Constructor
      /// </summary>
      INLINE Socket() : mSocket(INVALID_SOCKET)
      {
         mPoll.events  = 0;
         mPoll.revents = 0;
      }

      INLINE Socket(int af, int type, int protocol) : mSocket(Op::socket(af, type, protocol))
      {
         mPoll.events = 0;
         mPoll.revents = 0;
      }

      /// <summary>
      /// Destructor
      /// </summary>
      INLINE ~Socket()
      {
         if (mSocket != INVALID_SOCKET)
         {
            shutdown();
            close();
         }
      }

      /// <summary>
      /// Returns current socket
      /// </summary>
      INLINE SOCKET getSocket() { return mSocket; }

      /// <summary>
      /// Set current socket
      /// </summary>
      INLINE void setSocket(SOCKET s) { mSocket = s; }

      /// <summary>
      /// True if mSocket != INVALID_SOCKET
      /// </summary>
      INLINE bool isUsed() const { return mSocket != INVALID_SOCKET; }

      ////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // BASIC OPS
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Calls Op::setsockopt() for current socket.
      /// </summary>
      INLINE int setsockopt(int level, int optname, const char* optval, socklen_t optlen)
      {
         return Op::setsockopt(mSocket, level, optname, optval, optlen);
      }

      /// <summary>
      /// Calls Op::getsockopt() for current socket.
      /// </summary>
      INLINE int getsockopt(int level, int optname, char* optval, socklen_t* optlen) const
      {
         return Op::getsockopt(mSocket, level, optname, optval, optlen);
      }

      /// <summary>
      /// Calls Op::ioctlsocket() for current socket.
      /// </summary>
      INLINE int ioctlsocket(long cmd, u_long* argp) 
      { 
         return Op::ioctlsocket(mSocket, cmd, argp);
      }

      /// <summary>
      /// Calls Op::listen() for current socket.
      /// </summary>
      INLINE int listen(int backlog)
      { 
         return Op::listen(mSocket, backlog); 
      }

      /// <summary>
      /// Calls Op::bind() for current socket.
      /// </summary>
      INLINE int bind(const sockaddr* name, socklen_t namelen)
      { 
         return Op::bind(mSocket, name, namelen);
      }

      /// <summary>
      /// Calls Op::bind() for current socket with IPv4 addr.
      /// </summary>
      INLINE int bind(const sockaddr_in& name)
      { 
         return Op::bind(mSocket, (sockaddr*)&name, sizeof(sockaddr_in));
      }

      /// <summary>
      /// Calls Op::bind() for current socket with IPv6 addr.
      /// </summary>
      INLINE int bind(const sockaddr_in6& name)
      { 
         return Op::bind(mSocket, (sockaddr*)&name, sizeof(sockaddr_in6));
      }

      /// <summary>
      /// Calls Op::connect() for current socket.
      /// </summary>
      INLINE int connect(const sockaddr* name, socklen_t namelen)
      {
         return Op::connect(mSocket, name, namelen);
      }

      /// <summary>
      /// Calls Op::connect() for current socket with IPv4 addr.
      /// </summary>
      INLINE int connect(const sockaddr_in& name)
      {
         return Op::connect(mSocket, (sockaddr*)&name, sizeof(sockaddr_in));
      }

      /// <summary>
      /// Calls Op::connect() for current socket with IPv6 addr.
      /// </summary>
      INLINE int connect(const sockaddr_in6& name)
      {
         return Op::connect(mSocket, (sockaddr*)&name, sizeof(sockaddr_in6));
      }

      /// <summary>
      /// Calls Op::accept() for current socket and returns accepted SOCKET.
      /// </summary>
      INLINE SOCKET accept(sockaddr* addr, socklen_t* addrlen)
      {
         return Op::accept(mSocket, addr, addrlen);
      }

      /// <summary>
      /// Calls Op::acceptAndClose() for current socket.
      /// </summary>
      INLINE void acceptAndClose()
      {
         Op::acceptAndClose(mSocket);
      }

      /// <summary>
      /// Calls Op::shutdown() for current socket.
      /// </summary>
      INLINE int shutdown()
      {
         return Op::shutdown(mSocket);
      }

      /// <summary>
      /// Calls Op::close() for current socket.
      /// </summary>
      INLINE int close() 
      {
         int r = Op::close(mSocket);
         mSocket = INVALID_SOCKET;
         return r;
      }

      /// <summary>
      /// Polls the socket for up to timeout using events and returns revents.
      /// </summary>
      INLINE uint16_t poll(const uint16_t events, const int timeout = 16)
      {
         // set events and reset revents
         mPoll.events  = events;
         mPoll.revents = 0;

         // < 0 error || = 0 timeout || > 0 new tcp data or write recover
         const int r = Socket::Op::poll(&mPoll, 1, timeout);
         if (r > 0) return mPoll.revents;
         else       return 0;
      }

      ////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // UDP SEND/RECV
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Calls Op::sendto() for current socket.
      /// </summary>
      INLINE int sendto(const char* buf, int len, int flags, const sockaddr* to, socklen_t tolen)
      {
         return Op::sendto(mSocket, buf, len, flags, to, tolen);
      }

      /// <summary>
      /// Calls Op::recvfrom() for current socket.
      /// </summary>
      INLINE int recvfrom(char* buf, int len, int flags, sockaddr* from, socklen_t* fromlen)
      {
         return Op::recvfrom(mSocket, buf, len, flags, from, fromlen);
      }

      ////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // TCP SEND/RECV
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Calls Op::send() for current socket.
      /// </summary>
      INLINE int send(char* buf, int len, int flags = 0) 
      { 
         return Op::send(mSocket, buf, len, flags);
      }

      /// <summary>
      /// Calls Op::recv() for current socket.
      /// </summary>
      INLINE int recv(char* buf, int len, int flags = 0) 
      { 
         return Op::recv(mSocket, buf, len, flags);
      }

      /// <summary>
      /// Returns amount of bytes that can be read from the socket.
      /// </summary>
      INLINE bool getReadableBytesCount(u_long& argp)
      {
         return (SOCKET_ERROR != ioctlsocket(FIONREAD, &argp));
      }

      ////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // EASY CUSTOM OPTIONS
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////

      INLINE bool setNoBlock(bool enabled)
      {
         u_long VALUE = (u_long)enabled;
         return (SOCKET_ERROR != ioctlsocket(FIONBIO, &VALUE));
      }

      INLINE bool getOptionIPv6Only() const
      {
         int VALUE; socklen_t LEN = sizeof(VALUE);
         return (SOCKET_ERROR != getsockopt(IPPROTO_IPV6, IPV6_V6ONLY, (char*)&VALUE, &LEN) && VALUE);
      }
      
      INLINE bool setOptionIPv6Only(bool enabled)
      {
         const int VALUE = (int)enabled;
         return (SOCKET_ERROR != setsockopt(IPPROTO_IPV6, IPV6_V6ONLY, (char*)&VALUE, sizeof(VALUE)));
      }

      INLINE bool getOptionReuseAddress() const
      {
         int VALUE; socklen_t LEN = sizeof(VALUE);
         return (SOCKET_ERROR != getsockopt(SOL_SOCKET, SO_REUSEADDR, (char*)&VALUE, &LEN) && VALUE);
      }
      
      INLINE bool setOptionReuseAddress(bool enabled)
      {
         const int VALUE = (int)enabled;
         return (SOCKET_ERROR != setsockopt(SOL_SOCKET, SO_REUSEADDR, (char*)&VALUE, sizeof(VALUE)));
      }

      INLINE bool getOptionTcpNoDelay() const
      {
         int VALUE; socklen_t LEN = sizeof(VALUE);
         return (SOCKET_ERROR != getsockopt(IPPROTO_TCP, TCP_NODELAY, (char*)&VALUE, &LEN) && VALUE);
      }
      
      INLINE bool setOptionTcpNoDelay(bool enabled)
      {
         const int VALUE = (int)enabled;
         return (SOCKET_ERROR != setsockopt(IPPROTO_TCP, TCP_NODELAY, (char*)&VALUE, sizeof(VALUE)));
      }

      INLINE bool getOptionLinger() const
      {
         linger VALUE; socklen_t LEN = sizeof(VALUE);
         return (SOCKET_ERROR != getsockopt(SOL_SOCKET, SO_LINGER, (char*)&VALUE, &LEN) && VALUE.l_onoff);
      }

      INLINE bool setOptionLinger(bool enabled, uint16_t time)
      {
         linger VALUE;
         VALUE.l_onoff = (u_short)enabled;
         VALUE.l_linger = (u_short)time;
         return (SOCKET_ERROR != setsockopt(SOL_SOCKET, SO_LINGER, (char*)&VALUE, sizeof(VALUE)));
      }

      INLINE bool getOptionKeepAlive() const
      {
         int VALUE; socklen_t LEN = sizeof(VALUE);
         return (SOCKET_ERROR != getsockopt(SOL_SOCKET, SO_KEEPALIVE, (char*)&VALUE, &LEN) && VALUE);
      }

      INLINE bool setOptionKeepAlive(bool enabled)
      {
         const int VALUE = (int)enabled;
         return (SOCKET_ERROR != setsockopt(SOL_SOCKET, SO_KEEPALIVE, (char*)&VALUE, sizeof(VALUE)));
      }
   };
}
