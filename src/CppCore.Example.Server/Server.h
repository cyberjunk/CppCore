#pragma once

#include <CppCore/Application.h> // the base class
#include "NetServer.h"           // own netserver

namespace CppCore { namespace Example 
{
   /// <summary>
   /// Example Server Application
   /// </summary>
   class Server : 
      public Application<Server, Logger>, 
      public NetServer::Callback
   {
   public:
      /// <summary>
      /// Log File
      /// </summary>
      static constexpr char LOGFILE[] = "CppCore.Example.Server.log";
      
      /// <summary>
      /// Epoch Length
      /// </summary>
      static constexpr seconds EPOCHLENGTH = seconds(10);

   protected:
      NetServer mNetServer;
      Runnable  mEpochTimer;

      ////////////////////////////////////////////////////////////////////////////////////
      // NETSESSION CALLBACKS
      ////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Executed on message handler on tcp message from client.
      /// </summary>
      INLINE void onSessionMessageTcp(NetSession& session, Message::Tcp& msg) override
      {
         session.logDebug("Processing TCP");
      }

      /// <summary>
      /// Executed on message handler on udp message from client.
      /// </summary>
      INLINE void onSessionMessageUdp(NetSession& session, Message::Udp& msg) override
      {
         session.logDebug("Processing UDP");
      }

      /// <summary>
      /// Executed on connection handler on disconnect of client.
      /// </summary>
      INLINE void onSessionDisconnected(NetSession& session) override
      {
         session.logDebug("Proccessing disconnected session in connection handler.");
      }

      /// <summary>
      /// Executed on connection handler on connect of new client.
      /// </summary>
      INLINE void onSessionAccepted(NetSession& session) override
      {
         session.logDebug("Proccessing accepted session in connection handler.");
      }

      /// <summary>
      /// Epoch Timer Code
      /// </summary>
      INLINE void runEpochTimer()
      {
         mNetServer.setEpoch(mNetServer.getEpoch() + 1);
      }

   public:
      /// <summary>
      /// Constructor
      /// </summary>
      INLINE Server(const uint16_t port) : 
         Application(true, true, LOGFILE),
         mNetServer(port, *this, mThreadPool, mThreadPool, mLogger, *this),
         mEpochTimer([this]() { runEpochTimer(); }, true, EPOCHLENGTH)
      {
         schedule(mEpochTimer, ClockHR::now() + mEpochTimer.getInterval());
      }
   };
}}
