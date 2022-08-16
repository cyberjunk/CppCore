
#include "Client.h"

// init sockets on Windows (does nothing on others)
int init = CppCore::Socket::Op::initSockets();

// init example client
CppCore::Example::Client app;

void stop(int signal)
{
   app.stop(signal);
}

int main(int argc, char* argv[])
{
#if defined(CPPCORE_OS_WINDOWS)
   signal(SIGINT,   &stop);
   signal(SIGBREAK, &stop);
#else
   signal(SIGINT,  &stop);
   signal(SIGSTOP, &stop);
   signal(SIGTERM, &stop);
   signal(SIGKILL, &stop);
#endif
   app.start(argc, argv);
   CppCore::Socket::Op::shutdownSockets();
   return 0;
}
