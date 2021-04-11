#import "IOS/ObjC/IosNativeUI.h"

@implementation IosNativeUI

- (instancetype)init
{
    self = [super init];    
    return self;
}

+ (IosNativeUI *)Singleton
{
    static IosNativeUI *staticIosNativeUI;
    static dispatch_once_t once;
    dispatch_once(&once, ^{
        staticIosNativeUI = [[self alloc] init];
    });
    return staticIosNativeUI;
}

-(void)showToast: (NSString*)message Duration: (int)duration
{
    dispatch_async(dispatch_get_main_queue(), ^{

        float time = 0;
        if(duration == 0){
            time = 2;
        }
        else if(duration == 1){
            time = 3.5;
        }
        else{
            return;
        }

        UIAlertController *alert = [UIAlertController alertControllerWithTitle:nil
                                                               message:message
                                                        preferredStyle:UIAlertControllerStyleAlert];

        UIViewController *top = [UIApplication sharedApplication].keyWindow.rootViewController;
        [top presentViewController:alert animated:YES completion: nil];        

        dispatch_after(
            dispatch_time(DISPATCH_TIME_NOW, time * NSEC_PER_SEC), dispatch_get_main_queue(), ^{
                [alert dismissViewControllerAnimated:YES completion:nil];
            }
        );
	});
}

@end
