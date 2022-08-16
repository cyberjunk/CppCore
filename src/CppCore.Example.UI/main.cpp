
#include "Application.h"

CppCore::Example::Application app;

#if defined(CPPCORE_OS_OSX) && defined(__OBJC__)
@interface AppDelegate : NSObject <NSApplicationDelegate>
@property(assign) NSWindow* window;
@end

@implementation AppDelegate
@synthesize window;

-(void)dealloc
{
   [super dealloc];
}

- (void)applicationDidFinishLaunching:(NSNotification*)aNotification
{
   // TODO: Not needed?
   // This is only executed when message processing started
   printf("APP DID FINISH LAUNCH\n");
}
@end
#endif

int main(int argc, char* argv[])
{
#if defined(CPPCORE_OS_OSX) && defined(__OBJC__)
   [NSApplication sharedApplication];
   [NSApp setActivationPolicy : NSApplicationActivationPolicyRegular];
   [NSApp setPresentationOptions : NSApplicationPresentationDefault];
   [NSApp activateIgnoringOtherApps : YES];

   // set custom delegate from above
   AppDelegate* appDelegate = [[AppDelegate alloc]init];
   [NSApp setDelegate : appDelegate];

   // done init
   [NSApp finishLaunching];
#endif

   // start the app
   app.start(argc, argv);

   return 0;
}

// include the Window code
#include <CppCore/UI/Window.cpp>
