#pragma once

#include <CppCore/Application.h> // the base class
#include "NetClient.h"           // own netclient

//#define HOST "::1"
#define HOST "127.0.0.1"
//#define HOST "localhost"
//#define HOST "::ffff:127.0.0.1"

#define PORT 4321

namespace CppCore { namespace Example 
{
   /// <summary>
   /// Example Client Application using Example NetClient
   /// </summary>
   class Client : 
      public Application<Client, Logger>, 
      public NetClient::Callback
   {
   public:
      static constexpr char LOGFILE[] = "CppCore.Example.Client.log";

   protected:
      NetClient mNetClient;
      Runnable  mRunnableStats;
      Runnable  mRunnableConnect;
      Runnable  mRunnableDisconnect;
      Runnable  mRunnableTest;

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // NETCLIENT CALLBACKS
      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Raised for new message received from server.
      /// Return true to auto-push it back to pool.
      /// </summary>
      INLINE bool onTcpClientMessage(Message::Tcp& msg) override
      {
         return true;
      }

      /// <summary>
      /// Raised if net client disconnected
      /// </summary>
      INLINE void onTcpClientDisconnected() override
      {
         // try again
         logError("Connection lost. Retry in 3s.");
         schedule(mRunnableConnect, StdClock::now() + StdSeconds(3));
      }

      /// <summary>
      /// Raised if net client connected
      /// </summary>
      INLINE void onTcpClientConnected() override
      {
      }

      /// <summary>
      /// Raised if net client connection attempt failed
      /// </summary>
      INLINE void onTcpClientConnectionFailed() override
      {
         // try again
         logError("Connection failed. Retry in 3s.");
         schedule(mRunnableConnect, CppCore::StdClock::now() + StdSeconds(3));
      }

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      INLINE void runTest()
      {
         logDebug("Executed Test Runnable.");
      }

   public:
      /// <summary>
      /// Constructor
      /// </summary>
      INLINE Client() :
         Application(true, true, LOGFILE),
         mNetClient(*this, mThreadPool, *this, mLogger, *this),
         mRunnableConnect([this]() { mNetClient.connect(HOST, PORT); }),
         mRunnableDisconnect([this]() { mNetClient.disconnect(); }),
         mRunnableTest([this]() { runTest(); })
      {
         schedule(mRunnableConnect);
         schedule(mRunnableTest);
      }

      /// <summary>
      /// Destructor
      /// </summary>
      INLINE ~Client() { }
   };
}}
