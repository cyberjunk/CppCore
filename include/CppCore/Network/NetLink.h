#pragma once

#include <CppCore/Root.h>
#include <CppCore/Network/TcpLink.h>

namespace CppCore
{
   /// <summary>
   /// Custom Binary Tcp Protocol with Fixed Size Header
   /// </summary>
   template<
      typename TMSGTCP,
      typename TPOOL       = TcpLinkPool<TMSGTCP>,
      typename TQUEUEREAD  = TcpLinkQueueIn<TMSGTCP>,
      typename TQUEUEWRITE = TcpLinkQueueOut<TMSGTCP>>
   class NetLink : public TcpLink<TMSGTCP, TPOOL, TQUEUEREAD, TQUEUEWRITE>
   {
   public:
      typedef TcpLink<TMSGTCP, TPOOL, TQUEUEREAD, TQUEUEWRITE> Base;

      /// <summary>
      /// Constructor
      /// </summary>
      INLINE NetLink(TPOOL& poolMessageTcp) :
         Base(poolMessageTcp) { }

   protected:
      /// <summary>
      /// Raised by base class to check and suppress
      /// an outgoing message before it is sent.
      /// </summary>
      INLINE virtual bool onSendCheckTcp(TMSGTCP& msg) const override
      {
         return msg.hasCompleteHeader();
      }

      INLINE virtual bool isHeaderComplete(TMSGTCP& msg) const override 
      {
         return msg.hasCompleteHeader();
      }

      INLINE virtual bool isHeaderOK(TMSGTCP& msg) const override
      {
         return msg.getHeader().lengthok();
      }

      INLINE virtual bool isMessageComplete(TMSGTCP& msg) const override 
      {
         return msg.isComplete();
      }

      INLINE virtual size_t getMissingLength(TMSGTCP& msg) const override
      {
         return msg.hasCompleteHeader() ?
            msg.getMissingBodyLength() :
            msg.getMissingHeaderLength();
      }
   };
}
