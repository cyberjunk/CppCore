
#include "Application.h"

CppCore::Example::Application app;

#if defined(CPPCORE_OS_OSX) && defined(__OBJC__)
@interface AppDelegate : NSObject <NSApplicationDelegate>
@property(assign) NSWindow* window;
@end

@implementation AppDelegate
@synthesize window;
- (void)dealloc
{
   [super dealloc];
}
- (void)applicationDidFinishLaunching:(NSNotification*)aNotification
{
}
@end
#endif

int main(int argc, char* argv[])
{
#if defined(CPPCORE_OS_OSX) && defined(__OBJC__)
   // set the custom delegate from above before start
   AppDelegate* appDelegate = [[AppDelegate alloc]init];
   [NSApp setDelegate : appDelegate];
#endif

   // start the app
   app.start(argc, argv);

   return 0;
}

// include the Window code
#include <CppCore/UI/Window.cpp>
