#pragma once

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <UIKit/UIKit.h>
#import <sys/utsname.h>


@interface IosDeviceInfo : NSObject

+(NSString*)getModel;
+(NSString*)getTmpFilePath;

@end
