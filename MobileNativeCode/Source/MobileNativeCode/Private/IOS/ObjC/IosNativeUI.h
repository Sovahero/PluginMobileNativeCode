#pragma once

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <UIKit/UIKit.h>
#import <sys/utsname.h>
#import <StoreKit/StoreKit.h>

using namespace std;

@interface IosNativeUI : UIViewController

+(IosNativeUI*)Singleton;

/**
 * Calling a pop-up message on IOS
 */
-(void) showToast: (NSString*)message Duration: (int)duration; 

@end // IosNativeUI
