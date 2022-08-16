#pragma once

#include <CppCore/Root.h>
#include <CppCore/Network/Socket.h>

namespace CppCore
{
   /// <summary>
   /// TcpSocket (IPv6 Dual-Stack)
   /// </summary>
   class TcpSocket : public Socket
   {
   protected:
      CPPCORE_ALIGN16 sockaddr_in6 mAddress;
      CPPCORE_ALIGN16 char         mAddressString[INET6_ADDRSTRLEN];

      /// <summary>
      /// Validate Size of IPv6 Address
      /// </summary>
      static_assert(sizeof(mAddress.sin6_addr) == 16U);

      /// <summary>
      /// Updates Address String from Address.
      /// </summary>
      INLINE void updateAddressString()
      {
         ::inet_ntop(AF_INET6, &(mAddress.sin6_addr), mAddressString, INET6_ADDRSTRLEN);
      }

      /// <summary>
      /// Sets IPv4 address and port as IPv4-Mapped IPv6 address and port,
      /// e.g. "127.0.0.1:1234" --> "::ffff:127.0.0.1:1234"
      /// </summary>
      INLINE void storeIPv4MappedIPv6(const sockaddr_in& ipv4)
      {
         // set basics
         mAddress.sin6_family = AF_INET6;
         mAddress.sin6_scope_id = 0;
         mAddress.sin6_flowinfo = 0;

         // set port from ipv4 address
         mAddress.sin6_port = ipv4.sin_port;
            
         // get pointer on address
         uint32_t* p = (uint32_t*)&mAddress.sin6_addr;

         // set ipv4 as ipv4 mapped ipv6 address
         p[0] = 0x00000000;
         p[1] = 0x00000000;
         p[2] = 0xFFFF0000;
         p[3] = ipv4.sin_addr.s_addr;// S_un.S_addr;
      }

   public:
      /// <summary>
      /// Constructor
      /// </summary>
      INLINE TcpSocket() : Socket()
      {
         ::memset(&mAddress, 0, sizeof(mAddress));
         ::memset(&mAddressString, 0, sizeof(mAddressString));
      }

      /// <summary>
      /// Returns currently linked IPv6 address of socket
      /// </summary>
      INLINE const sockaddr_in6& getAddress() const { return mAddress; }

      /// <summary>
      /// Returns currently linked IPv6 address of socket as string.
      /// </summary>
      /// <returns></returns>
      INLINE const char* getAddressString() const { return mAddressString; }

      /// <summary>
      /// True if parameter address matches the linked address of this socket.
      /// </summary>
      INLINE bool isEndpoint(const sockaddr_in6& address) const
      {
         return CppCore::equal(address.sin6_addr, mAddress.sin6_addr);
      }

   public:
      /// <summary>
      /// Return Values of listen()
      /// </summary>
      enum class ListenReturn {
         OK               = 0,
         NotClosed        = 1,
         FailOnInit       = 2,
         FailOnOptNoBlock = 3,
         FailOnOptIP6Only = 4,
         FailOnBind       = 5,
         FailOnListen     = 6
      };

      /// <summary>
      /// Defaults used in listen() if not specified.
      /// </summary>
      class ListenDefaults
      {
      private:
         INLINE ListenDefaults() { }
      public:
         static constexpr bool NODELAY   = true;
         static constexpr bool REUSEADDR = true;
         static constexpr bool LINGER    = true;
         static constexpr int  LTIME     = 2;
         static constexpr bool KEEPALIVE = true;
      };

      /// <summary>
      /// Tries to start listening on specififed 
      /// tcp port with specified options.
      /// </summary>
      INLINE ListenReturn listen(
         const uint16_t port,
         const bool     nodelay   = ListenDefaults::NODELAY,
         const bool     reuseaddr = ListenDefaults::REUSEADDR,
         const bool     linger    = ListenDefaults::LINGER,
         const int      ltime     = ListenDefaults::LTIME,
         const bool     keepalive = ListenDefaults::KEEPALIVE)
      {
         if (mSocket != INVALID_SOCKET)
            return ListenReturn::NotClosed;

         // configure listen address
         mAddress.sin6_family = AF_INET6;
         mAddress.sin6_addr = in6addr_any;
         mAddress.sin6_port = htons(port);

         // convert to string
         this->updateAddressString();

         // create socket
         mSocket = Socket::Op::socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
         if (mSocket == INVALID_SOCKET)
            return ListenReturn::FailOnInit;

         // required: FIONBIO
         if (!this->setNoBlock(true))
         {
            this->close();
            return ListenReturn::FailOnOptNoBlock;
         }

         // required: IPV6_V6ONLY
         if (!this->setOptionIPv6Only(false))
         {
            this->close();
            return ListenReturn::FailOnOptIP6Only;
         }

         // set optional options
         this->setOptionTcpNoDelay(nodelay);
         this->setOptionReuseAddress(reuseaddr);
         this->setOptionLinger(linger, ltime);
         this->setOptionKeepAlive(keepalive);

         // bind tcp socket
         if (SOCKET_ERROR == Socket::bind(mAddress))
         {
            this->close();
            return ListenReturn::FailOnBind;
         }

         // listen on tcp socket
         if (SOCKET_ERROR == Socket::listen(16))
         {
            this->close();
            return ListenReturn::FailOnListen;
         }

         // all good
         return ListenReturn::OK;
      }
 
   public:
      /// <summary>
      /// Accepts a pending incoming TCP connection from a listenerSocket
      /// and assigns the accepted socket to this instance.
      /// </summary>
      INLINE bool acceptFrom(TcpSocket& listenerSocket)
      {
         // already in use
         if (mSocket != INVALID_SOCKET)
            return false;

         // address size
         socklen_t addrsize = sizeof(mAddress);

         // try to accept from listener, this sets mAddress
         mSocket = listenerSocket.accept((sockaddr*)&mAddress, &addrsize);

         // update string of address
         this->updateAddressString();

         // success or not
         return mSocket != INVALID_SOCKET;
      }

   public:
      /// <summary>
      /// Return Values of connect()
      /// </summary>
      enum class ConnectReturn { 
         OK                 = 0, 
         NotClosed          = 1,
         InvalidEndpoint    = 2, 
         FailOnInit         = 3, 
         FailOnOptNoBlock   = 4,
         FailOnOptIP6Only   = 5,
         TimeOut            = 6,
         ConnectError       = 7
      };

      /// <summary>
      /// Defaults used in connect() if not specified.
      /// </summary>
      class ConnectDefaults 
      {
      private:
         INLINE ConnectDefaults() { }
      public:
         static constexpr int  TIMEOUT   = 3000;
         static constexpr bool NODELAY   = true;
         static constexpr bool REUSEADDR = true;
         static constexpr bool LINGER    = true;
         static constexpr int  LTIME     = 2;
         static constexpr bool KEEPALIVE = true;
      };

      /// <summary>
      /// Tries to connect the socket to the specitifed host and tcp port.
      /// Blocks until successfully connected, error occured or specified timeout reached.
      /// </summary>
      INLINE ConnectReturn connect(
         const char* host, 
         const char* port, 
         const int   timeout   = ConnectDefaults::TIMEOUT,
         const bool  nodelay   = ConnectDefaults::NODELAY,
         const bool  reuseaddr = ConnectDefaults::REUSEADDR,
         const bool  linger    = ConnectDefaults::LINGER,
         const int   ltime     = ConnectDefaults::LTIME,
         const bool  keepalive = ConnectDefaults::KEEPALIVE)
      {
         // must be fresh instance or close() must have been called
         if (mSocket != INVALID_SOCKET)
            return ConnectReturn::NotClosed;

         // hints for getaddrinfo and return
         addrinfo  hints;
         addrinfo* addr = 0;

         // configure hints for getaddrinfo
         ::memset(&hints, 0, sizeof(hints));
         hints.ai_family = PF_UNSPEC;
         hints.ai_socktype = SOCK_STREAM;
         hints.ai_protocol = IPPROTO_TCP;
         hints.ai_flags |= AI_CANONNAME;

         // try to lookup ip endpoint for host and port
         // note: this may already have a notable delay
         if (::getaddrinfo(host, port, &hints, &addr) != 0)
            return ConnectReturn::InvalidEndpoint;

         // copy IPv6 return directly
         if (addr->ai_family == AF_INET6)
            mAddress = *(sockaddr_in6*)addr->ai_addr;

         // convert IPv4 to IPv4-mapped IPv6 address
         // e.g. "127.0.0.1" --> "::ffff:127.0.0.1"
         else if (addr->ai_family == AF_INET)
            this->storeIPv4MappedIPv6(*(sockaddr_in*)addr->ai_addr);
            
         // unknown IP endpoint protocol
         else
         {
            ::freeaddrinfo(addr);
            return ConnectReturn::InvalidEndpoint;
         }

         // free address info
         ::freeaddrinfo(addr);

         // convert to string
         this->updateAddressString();

         // init a socket for that protocol family (ipv4/ipv6)
         mSocket = Socket::Op::socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);

         // failed to init socket
         if (mSocket == INVALID_SOCKET)
            return ConnectReturn::FailOnInit;

         // required option: set FIONBIO (noblock)
         if (!this->setNoBlock(true))
         {
            this->close();
            return ConnectReturn::FailOnOptNoBlock;
         }

         // required: IPV6_V6ONLY
         if (!this->setOptionIPv6Only(false))
         {
            this->close();
            return ConnectReturn::FailOnOptIP6Only;
         }

         // optional options: todo, give some feedback which failed
         this->setOptionTcpNoDelay(nodelay);     // TCP_NODELAY
         this->setOptionReuseAddress(reuseaddr); // SO_REUSEADDR
         this->setOptionLinger(linger, ltime);   // SO_LINGER
         this->setOptionKeepAlive(keepalive);    // SO_KEEPALIVE

         // call connect on base class
         // this call is not blocking due to FIONBIO (noblock)
         const int rc = Socket::connect(mAddress);

         // 1) async blocking error, expected
         if (rc < 0 && (Socket::Op::isLastErrorBlock() || Socket::Op::isLastErrorInProgress()))
         {
            // wait for socket to be connected or until timeout
            const uint16_t R = this->poll(POLLOUT, timeout);

            if (R == 0)
            {
               this->close();
               return ConnectReturn::TimeOut;
            }
            else if (R & POLLERR)
            {
               this->close();
               return ConnectReturn::ConnectError;
            }
            else if (R & POLLOUT)
            {
               return ConnectReturn::OK;
            }
            else
            {
               this->close();
               return ConnectReturn::ConnectError;
            }
         }
         // 2) real socket error
         else
         {
            this->close();
            return ConnectReturn::ConnectError;
         }
      }
   };
}
