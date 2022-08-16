#pragma once

#include <CppCore/Network/NetServer.h> // the base class
#include "NetSession.h"                // own netsession

namespace CppCore { namespace Example 
{
   /// <summary>
   /// Example NetServer
   /// </summary>
   class NetServer : public CppCore::NetServer<
      Message::Tcp, 
      Message::Udp,
      NetSessionSharedData,
      NetSession>
   {
   public:
      /// <summary>
      /// Base Class
      /// </summary>
      using Base = CppCore::NetServer<
         Message::Tcp,
         Message::Udp,
         NetSessionSharedData,
         NetSession>;

   public:
      /// <summary>
      /// Constructor
      /// </summary>
      INLINE NetServer(
         uint16_t  port,
         Handler&  handlerMain,
         Handler&  handlerThreadPool,
         Handler&  handlerMessage,
         Logger&   logger,
         Callback& callBack) :
         Base(port, handlerMain, handlerThreadPool, 
            handlerMessage, logger, callBack) { }

      /// <summary>
      /// Returns the current epoch
      /// </summary>
      INLINE uint8_t getEpoch() { return mSharedData.mEpoch;  }

      /// <summary>
      /// Sets a new epoch and notifies all clients
      /// </summary>
      INLINE void setEpoch(uint8_t value) 
      {
         mSharedData.mEpoch = value;

         for (int i = 0; i < CPPCORE_NETSERVER_MAXCLIENTS; i++)
            this->mSessions[i].sendEpoch();
      }
   };
}}
