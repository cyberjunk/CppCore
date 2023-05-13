#pragma once

#include <CppCore/Root.h>

#include <CppCore/Containers/Queue.h>
#include <CppCore/Containers/Pool.h>

#include <CppCore/Threading/Runnable.h>
#include <CppCore/Threading/Thread.h>

#include <CppCore/Network/Message.h>

#include <CppCore/Network/TcpSocket.h>
#include <CppCore/Network/TcpSession.h>
#include <CppCore/Logger.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// In-Place NetSession Constructor
#ifndef NS_CTR
#define NS_CTR(n) { (n), mHandler, mThreadPool, mMessageHandler, mLogger, *this, mSharedData }
#endif

// In-Place Constructor for 32 Sessions
#define CPPCORE_SFIXCTR32 \
  NS_CTR(0),   NS_CTR(1),   NS_CTR(2),   NS_CTR(3),   NS_CTR(4),   NS_CTR(5),   NS_CTR(6),   NS_CTR(7),  \
  NS_CTR(8),   NS_CTR(9),   NS_CTR(10),  NS_CTR(11),  NS_CTR(12),  NS_CTR(13),  NS_CTR(14),  NS_CTR(15), \
  NS_CTR(16),  NS_CTR(17),  NS_CTR(18),  NS_CTR(19),  NS_CTR(20),  NS_CTR(21),  NS_CTR(22),  NS_CTR(23), \
  NS_CTR(24),  NS_CTR(25),  NS_CTR(26),  NS_CTR(27),  NS_CTR(28),  NS_CTR(29),  NS_CTR(30),  NS_CTR(31)

// In-Place Constructor for 64 Sessions
#define CPPCORE_SFIXCTR64 CPPCORE_SFIXCTR32, \
  NS_CTR(32),  NS_CTR(33),  NS_CTR(34),  NS_CTR(35),  NS_CTR(36),  NS_CTR(37),  NS_CTR(38),  NS_CTR(39), \
  NS_CTR(40),  NS_CTR(41),  NS_CTR(42),  NS_CTR(43),  NS_CTR(44),  NS_CTR(45),  NS_CTR(46),  NS_CTR(47), \
  NS_CTR(48),  NS_CTR(49),  NS_CTR(50),  NS_CTR(51),  NS_CTR(52),  NS_CTR(53),  NS_CTR(54),  NS_CTR(55), \
  NS_CTR(56),  NS_CTR(57),  NS_CTR(58),  NS_CTR(59),  NS_CTR(60),  NS_CTR(61),  NS_CTR(62),  NS_CTR(63)

// In-Place Constructor for 128 Sessions
#define CPPCORE_SFIXCTR128 CPPCORE_SFIXCTR64, \
  NS_CTR(64),  NS_CTR(65),  NS_CTR(66),  NS_CTR(67),  NS_CTR(68),  NS_CTR(69),  NS_CTR(70),  NS_CTR(71), \
  NS_CTR(72),  NS_CTR(73),  NS_CTR(74),  NS_CTR(75),  NS_CTR(76),  NS_CTR(77),  NS_CTR(78),  NS_CTR(79), \
  NS_CTR(80),  NS_CTR(81),  NS_CTR(82),  NS_CTR(83),  NS_CTR(84),  NS_CTR(85),  NS_CTR(86),  NS_CTR(87), \
  NS_CTR(88),  NS_CTR(89),  NS_CTR(90),  NS_CTR(91),  NS_CTR(92),  NS_CTR(93),  NS_CTR(94),  NS_CTR(95), \
  NS_CTR(96),  NS_CTR(97),  NS_CTR(98),  NS_CTR(99),  NS_CTR(100), NS_CTR(101), NS_CTR(102), NS_CTR(103),\
  NS_CTR(104), NS_CTR(105), NS_CTR(106), NS_CTR(107), NS_CTR(108), NS_CTR(109), NS_CTR(110), NS_CTR(111),\
  NS_CTR(112), NS_CTR(113), NS_CTR(114), NS_CTR(115), NS_CTR(116), NS_CTR(117), NS_CTR(118), NS_CTR(119),\
  NS_CTR(120), NS_CTR(121), NS_CTR(122), NS_CTR(123), NS_CTR(124), NS_CTR(125), NS_CTR(126), NS_CTR(127)

// In-Place Constructor for 256 Sessions
#define CPPCORE_SFIXCTR256 CPPCORE_SFIXCTR128, \
  NS_CTR(128), NS_CTR(129), NS_CTR(130), NS_CTR(131), NS_CTR(132), NS_CTR(133), NS_CTR(134), NS_CTR(135),\
  NS_CTR(136), NS_CTR(137), NS_CTR(138), NS_CTR(139), NS_CTR(140), NS_CTR(141), NS_CTR(142), NS_CTR(143),\
  NS_CTR(144), NS_CTR(145), NS_CTR(146), NS_CTR(147), NS_CTR(148), NS_CTR(149), NS_CTR(150), NS_CTR(151),\
  NS_CTR(152), NS_CTR(153), NS_CTR(154), NS_CTR(155), NS_CTR(156), NS_CTR(157), NS_CTR(158), NS_CTR(159),\
  NS_CTR(160), NS_CTR(161), NS_CTR(162), NS_CTR(163), NS_CTR(164), NS_CTR(165), NS_CTR(166), NS_CTR(167),\
  NS_CTR(168), NS_CTR(169), NS_CTR(170), NS_CTR(171), NS_CTR(172), NS_CTR(173), NS_CTR(174), NS_CTR(175),\
  NS_CTR(176), NS_CTR(177), NS_CTR(178), NS_CTR(179), NS_CTR(180), NS_CTR(181), NS_CTR(182), NS_CTR(183),\
  NS_CTR(184), NS_CTR(185), NS_CTR(186), NS_CTR(187), NS_CTR(188), NS_CTR(189), NS_CTR(190), NS_CTR(191),\
  NS_CTR(192), NS_CTR(193), NS_CTR(194), NS_CTR(195), NS_CTR(196), NS_CTR(197), NS_CTR(198), NS_CTR(199),\
  NS_CTR(200), NS_CTR(201), NS_CTR(202), NS_CTR(203), NS_CTR(204), NS_CTR(205), NS_CTR(206), NS_CTR(207),\
  NS_CTR(208), NS_CTR(209), NS_CTR(210), NS_CTR(211), NS_CTR(212), NS_CTR(213), NS_CTR(214), NS_CTR(215),\
  NS_CTR(216), NS_CTR(217), NS_CTR(218), NS_CTR(219), NS_CTR(220), NS_CTR(221), NS_CTR(222), NS_CTR(223),\
  NS_CTR(224), NS_CTR(225), NS_CTR(226), NS_CTR(227), NS_CTR(228), NS_CTR(229), NS_CTR(230), NS_CTR(231),\
  NS_CTR(232), NS_CTR(233), NS_CTR(234), NS_CTR(235), NS_CTR(236), NS_CTR(237), NS_CTR(238), NS_CTR(239),\
  NS_CTR(240), NS_CTR(241), NS_CTR(242), NS_CTR(243), NS_CTR(244), NS_CTR(245), NS_CTR(246), NS_CTR(247),\
  NS_CTR(248), NS_CTR(249), NS_CTR(250), NS_CTR(251), NS_CTR(252), NS_CTR(253), NS_CTR(254), NS_CTR(255)

// In-Place Constructor for 512 Sessions
#define CPPCORE_SFIXCTR512 CPPCORE_SFIXCTR256, \
  NS_CTR(256), NS_CTR(257), NS_CTR(258), NS_CTR(259), NS_CTR(260), NS_CTR(261), NS_CTR(262), NS_CTR(263),\
  NS_CTR(264), NS_CTR(265), NS_CTR(266), NS_CTR(267), NS_CTR(268), NS_CTR(269), NS_CTR(270), NS_CTR(271),\
  NS_CTR(272), NS_CTR(273), NS_CTR(274), NS_CTR(275), NS_CTR(276), NS_CTR(277), NS_CTR(278), NS_CTR(279),\
  NS_CTR(280), NS_CTR(281), NS_CTR(282), NS_CTR(283), NS_CTR(284), NS_CTR(285), NS_CTR(286), NS_CTR(287),\
  NS_CTR(288), NS_CTR(289), NS_CTR(290), NS_CTR(291), NS_CTR(292), NS_CTR(293), NS_CTR(294), NS_CTR(295),\
  NS_CTR(296), NS_CTR(297), NS_CTR(298), NS_CTR(299), NS_CTR(300), NS_CTR(301), NS_CTR(302), NS_CTR(303),\
  NS_CTR(304), NS_CTR(305), NS_CTR(306), NS_CTR(307), NS_CTR(308), NS_CTR(309), NS_CTR(310), NS_CTR(311),\
  NS_CTR(312), NS_CTR(313), NS_CTR(314), NS_CTR(315), NS_CTR(316), NS_CTR(317), NS_CTR(318), NS_CTR(319),\
  NS_CTR(320), NS_CTR(321), NS_CTR(322), NS_CTR(323), NS_CTR(324), NS_CTR(325), NS_CTR(326), NS_CTR(327),\
  NS_CTR(328), NS_CTR(329), NS_CTR(330), NS_CTR(331), NS_CTR(332), NS_CTR(333), NS_CTR(334), NS_CTR(335),\
  NS_CTR(336), NS_CTR(337), NS_CTR(338), NS_CTR(339), NS_CTR(340), NS_CTR(341), NS_CTR(342), NS_CTR(343),\
  NS_CTR(344), NS_CTR(345), NS_CTR(346), NS_CTR(347), NS_CTR(348), NS_CTR(349), NS_CTR(350), NS_CTR(351),\
  NS_CTR(352), NS_CTR(353), NS_CTR(354), NS_CTR(355), NS_CTR(356), NS_CTR(357), NS_CTR(358), NS_CTR(359),\
  NS_CTR(360), NS_CTR(361), NS_CTR(362), NS_CTR(363), NS_CTR(364), NS_CTR(365), NS_CTR(366), NS_CTR(367),\
  NS_CTR(368), NS_CTR(369), NS_CTR(370), NS_CTR(371), NS_CTR(372), NS_CTR(373), NS_CTR(374), NS_CTR(375),\
  NS_CTR(376), NS_CTR(377), NS_CTR(378), NS_CTR(379), NS_CTR(380), NS_CTR(381), NS_CTR(382), NS_CTR(383),\
  NS_CTR(384), NS_CTR(385), NS_CTR(386), NS_CTR(387), NS_CTR(388), NS_CTR(389), NS_CTR(390), NS_CTR(391),\
  NS_CTR(392), NS_CTR(393), NS_CTR(394), NS_CTR(395), NS_CTR(396), NS_CTR(397), NS_CTR(398), NS_CTR(399),\
  NS_CTR(400), NS_CTR(401), NS_CTR(402), NS_CTR(403), NS_CTR(404), NS_CTR(405), NS_CTR(406), NS_CTR(407),\
  NS_CTR(408), NS_CTR(409), NS_CTR(410), NS_CTR(411), NS_CTR(412), NS_CTR(413), NS_CTR(414), NS_CTR(415),\
  NS_CTR(416), NS_CTR(417), NS_CTR(418), NS_CTR(419), NS_CTR(420), NS_CTR(421), NS_CTR(422), NS_CTR(423),\
  NS_CTR(424), NS_CTR(425), NS_CTR(426), NS_CTR(427), NS_CTR(428), NS_CTR(429), NS_CTR(430), NS_CTR(431),\
  NS_CTR(432), NS_CTR(433), NS_CTR(434), NS_CTR(435), NS_CTR(436), NS_CTR(437), NS_CTR(438), NS_CTR(439),\
  NS_CTR(440), NS_CTR(441), NS_CTR(442), NS_CTR(443), NS_CTR(444), NS_CTR(445), NS_CTR(446), NS_CTR(447),\
  NS_CTR(448), NS_CTR(449), NS_CTR(450), NS_CTR(451), NS_CTR(452), NS_CTR(453), NS_CTR(454), NS_CTR(455),\
  NS_CTR(456), NS_CTR(457), NS_CTR(458), NS_CTR(459), NS_CTR(460), NS_CTR(461), NS_CTR(462), NS_CTR(463),\
  NS_CTR(464), NS_CTR(465), NS_CTR(466), NS_CTR(467), NS_CTR(468), NS_CTR(469), NS_CTR(470), NS_CTR(471),\
  NS_CTR(472), NS_CTR(473), NS_CTR(474), NS_CTR(475), NS_CTR(476), NS_CTR(477), NS_CTR(478), NS_CTR(479),\
  NS_CTR(480), NS_CTR(481), NS_CTR(482), NS_CTR(483), NS_CTR(484), NS_CTR(485), NS_CTR(486), NS_CTR(487),\
  NS_CTR(488), NS_CTR(489), NS_CTR(490), NS_CTR(491), NS_CTR(492), NS_CTR(493), NS_CTR(494), NS_CTR(495),\
  NS_CTR(496), NS_CTR(497), NS_CTR(498), NS_CTR(499), NS_CTR(500), NS_CTR(501), NS_CTR(502), NS_CTR(503),\
  NS_CTR(504), NS_CTR(505), NS_CTR(506), NS_CTR(507), NS_CTR(508), NS_CTR(509), NS_CTR(510), NS_CTR(511)

// Select In-Place Constructor
#if   CPPCORE_NETSERVER_MAXCLIENTS == 32
#define CPPCORE_NETSERVER_SESSION_CTR CPPCORE_SFIXCTR32
#elif CPPCORE_NETSERVER_MAXCLIENTS == 64
#define CPPCORE_NETSERVER_SESSION_CTR CPPCORE_SFIXCTR64
#elif CPPCORE_NETSERVER_MAXCLIENTS == 128
#define CPPCORE_NETSERVER_SESSION_CTR CPPCORE_SFIXCTR128
#elif CPPCORE_NETSERVER_MAXCLIENTS == 256
#define CPPCORE_NETSERVER_SESSION_CTR CPPCORE_SFIXCTR256
#elif CPPCORE_NETSERVER_MAXCLIENTS == 512
#define CPPCORE_NETSERVER_SESSION_CTR CPPCORE_SFIXCTR512
#else
#error "Unsupported CPPCORE_NETSERVER_MAXCLIENTS"
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace CppCore
{
   /// <summary>
   /// TcpServer
   /// </summary>
   template<
      typename TMSGTCP      = TcpLinkMessage<>, 
      typename TSHAREDDATA  = TcpSessionSharedData<TMSGTCP>,
      typename TSESSION     = TcpSession<TMSGTCP, TSHAREDDATA>,
      typename TPOOLSESSION = TcpSessionPool<TSESSION, CPPCORE_NETSERVER_MAXCLIENTS>,
      typename TPOLLSESSION = Array::Fix::ST<TSESSION*, CPPCORE_NETSERVER_MAXCLIENTS>>
   class CPPCORE_ALIGN16 TcpServer : 
      public Logger::Producer<Logger, Logger::Channel::Network>, 
      public TSESSION::Callback
   {
   public:
      /// <summary>
      /// TcpServer Callback
      /// </summary>
      class Callback
      {
      public:
         /// <summary>
         /// Raised if new tcp message is available on a session.
         /// Executed on message handler.
         /// </summary>
         INLINE virtual void onSessionMessageTcp(TSESSION& session, TMSGTCP& msg) { }

         /// <summary>
         /// Raised after client connection was accepted.
         /// Executed on connection handler.
         /// </summary>
         INLINE virtual void onSessionAccepted(TSESSION& session) { }

         /// <summary>
         /// Raised after disconnect of client or in case of connection error.
         /// Executed on connection handler.
         /// </summary>
         INLINE virtual void onSessionDisconnected(TSESSION& session) { }
      };

   protected:
      CPPCORE_ALIGN16 Handler&     mHandler;
      CPPCORE_ALIGN16 Handler&     mThreadPool;
      CPPCORE_ALIGN16 Handler&     mMessageHandler;
      CPPCORE_ALIGN16 Callback&    mCallback;
      CPPCORE_ALIGN16 uint16_t     mPort;
      CPPCORE_ALIGN16 TcpSocket    mSocketTcp;
      CPPCORE_ALIGN16 DurationHR   mTimeoutReceive;
      CPPCORE_ALIGN16 Runnable     mRunnablePollAccept;
      CPPCORE_ALIGN16 Runnable     mRunnablePollTcp;
      CPPCORE_ALIGN16 pollfd       mPollTcp[CPPCORE_NETSERVER_MAXCLIENTS];
      CPPCORE_ALIGN16 TSHAREDDATA  mSharedData;
      CPPCORE_ALIGN16 TPOLLSESSION mPollSessions;
      CPPCORE_ALIGN16 TPOOLSESSION mSessionsFree;
      CPPCORE_ALIGN16 TSESSION     mSessions[CPPCORE_NETSERVER_MAXCLIENTS]{ CPPCORE_NETSERVER_SESSION_CTR };

      ///////////////////////////////////////////////////////////////////////////////////////////////////////////
      // RUNNABLES
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Accepts incoming TCP connections
      /// </summary>
      INLINE void runPollAccept(const int timeout = 16)
      {
         // poll up to timeout
         if (mSocketTcp.poll(POLLIN, timeout))
         {
            TSESSION* session;
            if (mSessionsFree.popBack(session))
            {
               // try to accept new client
               if (session->acceptFrom(mSocketTcp))
                  session->logDebug("New session accepted");

               else
               {
                  mSessionsFree.pushBack(session);
                  session->logWarn("Failed to accept client socket");
               }
            }
            else
            {
               // reject new client (max reached)
               mSocketTcp.acceptAndClose();
               logWarn("New session rejected. All slots full.");
            }
         }
      }

      /// <summary>
      /// Polls the TCP sockets of clients and reads pending data if any.
      /// Also observes writability after send blocks.
      /// </summary>
      INLINE void runPollTcp()
      {
         // clear sessions to poll
         mPollSessions.clear();

         // current timestamp
         const TimePointHR now = ClockHR::now();

         // build poll data of connected clients
         for (int i = 0; i < CPPCORE_NETSERVER_MAXCLIENTS; i++)
         {
            TSESSION& session = mSessions[i];

            // ignore unused sessions
            if (!session.isActive())
               continue;

            // disconnect idle/timed-out sessions
            if (now - session.getLastReceiveTcp() > mTimeoutReceive)
            {
               session.log("Disconnecting timed-out client.");
               session.close();
               continue;
            }

            // by default poll incoming only, unless the sending is blocked
            const short EVENTS = !session.isBlockedSend() ? 
               POLLIN : POLLIN | POLLOUT;

            // idx of next poll entry
            const size_t IDX = mPollSessions.length();

            // set poll entry
            mPollTcp[IDX].fd = session.getSocketOS();
            mPollTcp[IDX].events = EVENTS;
            mPollTcp[IDX].revents = 0;

            // save polled session
            mPollSessions.pushBack(&mSessions[i]);
         }

         // how many we're going to observe
         const size_t LEN = mPollSessions.length();

         // and how long we will poll them
         constexpr int POLLMS = 16;

         // if no client is connected, we have to do the same sleep manual
         // because poll won't sleep and hence we would eat a lot of cpu
         if (LEN == 0)
            ::std::this_thread::sleep_for(milliseconds(POLLMS));

         else
         {
            // poll them now
            const int r = Socket::Op::poll(mPollTcp, (int)LEN, POLLMS);

            // < 0 error || = 0 timeout || > 0 new tcp data or write recover for this many sockets
            if (r <= 0)
               return;

            // process the ones that have data
            // TODO: consider triggering this as runnable on pool?
            for (size_t i = 0; i < LEN; i++)
               if (mPollTcp[i].revents)
                  mPollSessions[i]->recvPendingTcp(mPollTcp[i]);
         }
      }

      ///////////////////////////////////////////////////////////////////////////////////////////////////////////
      // TCPSESSION CALLBACK
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Callback from Session
      /// </summary>
      INLINE void onSessionMessageTcp(typename TSESSION::TCPSESSION& session, TMSGTCP& msg) override
      {
         auto& s = dynamic_cast<TSESSION&>(session);
         mCallback.onSessionMessageTcp(s, msg);
      }

      /// <summary>
      /// Callback from Session
      /// </summary>
      INLINE void onSessionDisconnected(typename TSESSION::TCPSESSION& session) override
      {
         auto& s = dynamic_cast<TSESSION&>(session);
         mCallback.onSessionDisconnected(dynamic_cast<TSESSION&>(session));
         mSessionsFree.pushBack(&s);
      }

      /// <summary>
      /// Callback from Session
      /// </summary>
      INLINE void onSessionAccepted(typename TSESSION::TCPSESSION& session) override
      {
         auto& s = dynamic_cast<TSESSION&>(session);
         mCallback.onSessionAccepted(s);
      }

   public:
      /// <summary>
      /// Constructor
      /// </summary>
      INLINE TcpServer(
         uint16_t  port,
         Handler&  handler,
         Handler&  threadPool,
         Handler&  messageHandler,
         Logger&   logger,
         Callback& callBack,
         const DurationHR& timeoutReceive = seconds(5)) :
         Logger::Producer<Logger, Logger::Channel::Network>(logger),
         mPort(port),
         mSocketTcp(),
         mTimeoutReceive(timeoutReceive),
         mRunnablePollAccept([this]() { runPollAccept(); }, milliseconds(0)),
         mRunnablePollTcp([this]() { runPollTcp(); }, milliseconds(0)),
         mHandler(handler),
         mThreadPool(threadPool),
         mMessageHandler(messageHandler),
         mCallback(callBack)
      {
         // add all sessions to free ones
         for (int i = CPPCORE_NETSERVER_MAXCLIENTS - 1; i >= 0; i--)
            mSessionsFree.pushBack(&mSessions[i]);

         // log listen start
         log("Creating TCP socket and binding to port " + std::to_string(mPort));

         // start listening
         const TcpSocket::ListenReturn lr = 
            mSocketTcp.listen(mPort);

         if (lr == TcpSocket::ListenReturn::OK)
         {
            // schedule poll runnables
            mThreadPool.schedule(mRunnablePollAccept);
            mThreadPool.schedule(mRunnablePollTcp);
         }

         // failed to listen on tcp socket
         else
         {
            switch (lr)
            {
            case TcpSocket::ListenReturn::NotClosed:
               logError("Existing socket not closed.");
               break;
            case TcpSocket::ListenReturn::FailOnInit:
               logError("Failed to create tcp socket.");
               break;
            case TcpSocket::ListenReturn::FailOnOptNoBlock:
               logError("Failed to enable FIONBIO (noblock) on tcp socket.");
               break;
            case TcpSocket::ListenReturn::FailOnOptIP6Only:
               logError("Failed to disable IPV6_V6ONLY on tcp socket.");
               break;
            case TcpSocket::ListenReturn::FailOnBind:
               logError("Failed to bind tcp socket.");
               break;
            case TcpSocket::ListenReturn::FailOnListen:
               logError("Failed to listen on tcp socket.");
               break;
            default:
               break;
            }
            //TODO: Add some kind of auto-repeat?
         }
      }

      /// <summary>
      /// Destructor
      /// </summary>
      INLINE ~TcpServer()
      {
         // disable timers
         mRunnablePollAccept.setRepeat(false);
         mRunnablePollTcp.setRepeat(false);

         // remove from schedule
         mThreadPool.cancel(mRunnablePollAccept);
         mThreadPool.cancel(mRunnablePollTcp);

         // delete sessions ?
      }

      /// <summary>
      /// Gets the shared data between server and all sessions.
      /// </summary>
      INLINE TSHAREDDATA& getSharedData() { return mSharedData; }

      /// <summary>
      /// 
      /// </summary>
      INLINE bool pushFreeSession(TSESSION& s)
      {
         return mSessionsFree.pushBack(&s);
      }
   };
}
