#pragma once
//==========================================
#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <UIKit/UIKit.h>
#import <sys/utsname.h>
using namespace std;
//==========================================

// #~~~~~~~~~~~~~~~~~~~~~~~~~~~ begin 2 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "PLUGIN_NAMEBPLibrary.h" // For Dispatcher UE4
//~~~~~~~~~~~~~~~~~~~~~~~~~~~ end 2 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//==========================================

@interface TestIosClass : NSObject

+(TestIosClass*)Singleton;

+(NSString*) HelloWorldOnIOS: (NSString*)text; 
+(void) asyncHelloWorldOnIOS: (NSString*)text; 
+(NSString*) getModel; 
-(void) showToast: (NSString*)message Duration: (int)duration; 
+(NSMutableArray*) TestArray:(NSMutableArray*)text b:(NSMutableArray*)b i:(NSMutableArray*)i f:(NSMutableArray*)f l:(NSMutableArray*)l;
+(NSString*) getTmpFilePath;

@end // TestIosClass
