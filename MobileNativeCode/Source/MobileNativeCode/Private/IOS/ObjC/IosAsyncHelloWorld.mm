#import "IosAsyncHelloWorld.h"
#include "MobileNativeCodeBlueprint.h" // For Dispatcher UE4

@implementation IosAsyncHelloWorld

- (instancetype)init
{
    self = [super init];    
    return self;
}

//-- Calling IOS code asynchronously and returning the value back to C++
+ (void) asyncHelloWorldOnIOS:(NSString*)text
{
	dispatch_async(dispatch_get_main_queue(), ^{
		NSString* tmpStr = @" on IOS";
		NSString* ReturnText = [text stringByAppendingString: tmpStr];
		UMobileNativeCodeBlueprint::CallBackCppIOS(ReturnText);
	});
}


@end
