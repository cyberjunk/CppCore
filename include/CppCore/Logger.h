#pragma once

#ifndef CPPCORE_LOGSIZE
#define CPPCORE_LOGSIZE 512
#endif

#include <CppCore/Root.h>
#include <CppCore/Threading/Handler.h>
#include <CppCore/Containers/Queue.h>
#include <CppCore/Containers/Pool.h>

namespace CppCore
{
   /// <summary>
   /// Logger
   /// </summary>
   class Logger
   {
   public:
      enum Channel { App, Log, Network, GUI, Resources, Data, Chat, Factory, Other };
      enum Type { Error, Warning, Info, Debug };

      /// <summary>
      /// Log Entry
      /// </summary>
      struct LogEntry
      {
      public:
         size_t     Channel;
         Type       Type;
         time_t     Time;
         thread::id ThreadId;
         string     Message;
         INLINE size_t memOnHeap() { return Message.capacity() + 1; }
      };

      /// <summary>
      /// For components using a reference to the logger
      /// </summary>
      template<typename TLOGGER, Logger::Channel CHANNEL>
      class Producer
      {
      protected:
         TLOGGER& mLogger;
      public:
         INLINE Producer(TLOGGER& logger) : mLogger(logger) { }
         INLINE void log(const string& message, const Logger::Type logType = Logger::Type::Info)
         {
            mLogger.log(message, CHANNEL, logType);
         }
         INLINE void logError(const string& message) { this->log(message, Logger::Type::Error);   }
         INLINE void logWarn(const string& message)  { this->log(message, Logger::Type::Warning); }
         INLINE void logDebug(const string& message) { this->log(message, Logger::Type::Debug);   }
      };

      typedef Queue::MT<LogEntry*, CPPCORE_LOGSIZE>    LogQueue;
      typedef Pool::Fix::MT<LogEntry, CPPCORE_LOGSIZE> LogPool;

   protected:
      Handler&    mThreadPool;
      Runnable    mRunnableLog;
      LogQueue    mQueue;
      LogPool     mPool;
      ofstream    mStream;
      std::locale mLocale;
      bool        mLogToConsole;
      bool        mLogToFile;

   private:
      /// <summary>
      /// Internal Writer Method executed by ThreadPool
      /// </summary>
      INLINE void writer()
      {
         LogEntry* entry;

         // try get pending log entry
         while (mQueue.popFront(entry))
         {
            // write it
            write(*entry);

            // add back to free ones
            mPool.pushBack(entry);
         }
      }

   protected:
      /// <summary>
      /// Returns a 3 letter string for the LogType
      /// </summary>
      INLINE virtual const char* stringOfLogType(const size_t type)
      {
         switch (type)
         {
         case Type::Info:    return "INF";
         case Type::Warning: return "WRN";
         case Type::Error:   return "ERR";
         case Type::Debug:   return "DBG";
         default:            return "UNK";
         }
      }

      /// <summary>
      /// Returns a 3 letter string for the Channel.
      /// </summary>
      INLINE virtual const char* stringOfChannel(const size_t channel)
      {
         switch (channel)
         {
         case Channel::App:       return "APP";
         case Channel::Log:       return "LOG";
         case Channel::Network:   return "NET";
         case Channel::GUI:       return "GUI";
         case Channel::Resources: return "RES";
         case Channel::Data:      return "DAT";
         case Channel::Chat:      return "CHT";
         case Channel::Factory:   return "FAC";
         case Channel::Other:     return "OTH";
         default:                 return "UNK";
         }
      }

      /// <summary>
      /// Override this with logging to somewhere else than console
      /// </summary>
      INLINE virtual void write(const LogEntry& entry)
      {
         // convert timestamp to utc time
         const ::std::tm* gm = ::std::gmtime(&entry.Time);

         stringstream ss;

         // workaround? (fixes comma in thread id ints but maintains ßöä in message)
         ss.imbue(mLocale);

         // build log
         ss << ::std::put_time(gm, "%Y/%m/%d|%H:%M:%S|")
            << ::std::setw(5) << ::std::setfill('0') << entry.ThreadId << '|'
            << stringOfChannel(entry.Channel) << '|'
            << stringOfLogType(entry.Type) << "||"
            << entry.Message << ::std::endl;

         // log to console
         if (mLogToConsole)
            ::std::cout << ss.str();

         // log to file
         if (mLogToFile && mStream.is_open())
         {
            mStream << ss.str();
            mStream.flush();
         }
      }

   public:
      /// <summary>
      /// Constructor
      /// </summary>
      INLINE Logger(
         Handler& threadPool, 
         bool     logToConsole           = true, 
         bool     logToFile              = true, 
         const    string& logFile        = "app.log",
         const    DurationHR logInterval = milliseconds(100)) :
         mThreadPool(threadPool),
         mLogToConsole(logToConsole),
         mLogToFile(logToFile),
         mLocale(std::locale("C")),
         mRunnableLog([this]() { writer(); }, true, logInterval)
      {
         // init logfile stream
         if (logToFile)
            mStream = ofstream(logFile, ofstream::out);

         // schedule the log timer
         threadPool.schedule(mRunnableLog, ClockHR::now() + logInterval);

         // log startup
         log("Created Logger", Channel::Log, Type::Info);
      }

      /// <summary>
      /// Destructor
      /// </summary>
      INLINE ~Logger()
      {
         if (mStream.is_open())
         {
            mStream.flush();
            mStream.close();
         }
      }

      /// <summary>
      /// Create a log entry
      /// </summary>
      INLINE bool log(const string& message, const size_t channel = 0, const Type type = Type::Info)
      {
         // logging fully disabled
         if (!mLogToFile && !mLogToConsole)
            return true;

         LogEntry* entry;

         // try get free log entry
         if (mPool.popBack(entry))
         {
            // set log values
            entry->Message = message;
            entry->Channel = channel;
            entry->Type = type;
            entry->Time = ::std::time(0);
            entry->ThreadId = ::std::this_thread::get_id();

            // try enqueue it for logging
            if (mQueue.pushBack(entry))
               return true;

            // push back to free ones if failed
            else
               mPool.pushBack(entry);
         }

         // failed
         return false;
      }
   };
}
