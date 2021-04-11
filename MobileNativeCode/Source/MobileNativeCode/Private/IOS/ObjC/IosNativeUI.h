#pragma once
//==========================================
#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <UIKit/UIKit.h>
#import <sys/utsname.h>

using namespace std;

@interface IosNativeUI : NSObject

+(IosNativeUI*)Singleton;

/**
 * Calling a pop-up message on IOS
 */
-(void) showToast: (NSString*)message Duration: (int)duration; 

@end // IosNativeUI
