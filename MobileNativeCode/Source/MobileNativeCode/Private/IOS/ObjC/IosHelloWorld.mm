#import "IosHelloWorld.h"


@implementation IosHelloWorld

//-- Calling IOS code synchronously 
+ (NSString*) HelloWorldOnIOS:(NSString*)text
{
    NSString* tmpStr = @" on IOS";
    NSString* ReturnText = [text stringByAppendingString: tmpStr];
    return ReturnText;
}

@end
