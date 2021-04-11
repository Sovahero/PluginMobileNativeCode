#pragma once

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <UIKit/UIKit.h>
#import <sys/utsname.h>



@interface IosAsyncHelloWorld : NSObject

+(void)asyncHelloWorldOnIOS: (NSString*)text;

@end 
