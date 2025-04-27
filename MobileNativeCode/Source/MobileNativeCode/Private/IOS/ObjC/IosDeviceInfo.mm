#import "IosDeviceInfo.h"

@implementation IosDeviceInfo

//-- Device information
+ (NSString*)getModel
{
    struct utsname systemInfo;
    uname(&systemInfo);
        
    NSString* Model = [NSString stringWithCString:systemInfo.machine encoding:NSUTF8StringEncoding];
	return Model;
}

//-- Path to "/var/mobile/Containers/Data/Application/%PROJECT_ID%/Library/Caches/"
+ (NSString *)getTmpFilePath
{
    NSString* path = [NSSearchPathForDirectoriesInDomains(NSCachesDirectory,  NSUserDomainMask, YES) lastObject];

	NSString* tmpStr = @"/";
    NSString* ReturnText = [path stringByAppendingString: tmpStr];

    return ReturnText;
}

@end
