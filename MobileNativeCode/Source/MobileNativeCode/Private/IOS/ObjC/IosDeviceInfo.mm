#import "IosDeviceInfo.h"

@implementation IosDeviceInfo

//-- Device information
+ (NSString*) getModel
{
    struct utsname systemInfo;
    uname(&systemInfo);
        
    NSString* Model = [NSString stringWithCString:systemInfo.machine
                                  encoding:NSUTF8StringEncoding];

    if ([Model isEqualToString : @"i386"]) { return @"32-bit Simulator"; }
	else if ([Model isEqualToString : @"x86_64"]) { return @"64-bit Simulator"; }

	else if ([Model isEqualToString : @"iPhone1,1"]) { return @"iPhone	"; }
	else if ([Model isEqualToString : @"iPhone1,2"]) { return @"iPhone 3G"; }
	else if ([Model isEqualToString : @"iPhone2,1"]) { return @"iPhone 3GS"; }
	else if ([Model isEqualToString : @"iPhone3,1"]) { return @"iPhone 4 (GSM)"; }
	else if ([Model isEqualToString : @"iPhone3,2"]) { return @"iPhone 4 (GSM Rev A)"; }
	else if ([Model isEqualToString : @"iPhone3,3"]) { return @"iPhone 4 (CDMA/Verizon/Sprint)"; }
	else if ([Model isEqualToString : @"iPhone4,1"]) { return @"iPhone 4S"; }
	else if ([Model isEqualToString : @"iPhone5,1"]) { return @"iPhone 5 (model A1428, AT&T/Canada)"; }
	else if ([Model isEqualToString : @"iPhone5,2"]) { return @"iPhone 5 (model A1429, everything else)"; }
	else if ([Model isEqualToString : @"iPhone5,3"]) { return @"iPhone 5c (model A1456, A1532 | GSM)"; }
	else if ([Model isEqualToString : @"iPhone5,4"]) { return @"iPhone 5c (model A1507, A1516, A1526 (China), A1529 | Global)"; }
	else if ([Model isEqualToString : @"iPhone6,1"]) { return @"iPhone 5s (model A1433, A1533 | GSM)"; }
	else if ([Model isEqualToString : @"iPhone6,2"]) { return @"iPhone 5s (model A1457, A1518, A1528 (China), A1530 | Global)"; }
	else if ([Model isEqualToString : @"iPhone7,1"]) { return @"iPhone 6 Plus"; }
	else if ([Model isEqualToString : @"iPhone7,2"]) { return @"iPhone 6"; }
	else if ([Model isEqualToString : @"iPhone8,1"]) { return @"iPhone 6S"; }
	else if ([Model isEqualToString : @"iPhone8,2"]) { return @"iPhone 6S Plus"; }
	else if ([Model isEqualToString : @"iPhone8,4"]) { return @"iPhone SE"; }
	else if ([Model isEqualToString : @"iPhone9,1"]) { return @"iPhone 7 (CDMA)"; }
	else if ([Model isEqualToString : @"iPhone9,3"]) { return @"iPhone 7 (GSM)"; }
	else if ([Model isEqualToString : @"iPhone9,2"]) { return @"iPhone 7 Plus (CDMA)"; }
	else if ([Model isEqualToString : @"iPhone9,4"]) { return @"iPhone 7 Plus (GSM)"; }
	else if ([Model isEqualToString : @"iPhone10,1"]) { return @"iPhone 8 (CDMA)"; }
	else if ([Model isEqualToString : @"iPhone10,4"]) { return @"iPhone 8 (GSM)"; }
	else if ([Model isEqualToString : @"iPhone10,2"]) { return @"iPhone 8 Plus (CDMA)"; }
	else if ([Model isEqualToString : @"iPhone10,5"]) { return @"iPhone 8 Plus (GSM)"; }
	else if ([Model isEqualToString : @"iPhone10,3"]) { return @"iPhone X (CDMA)"; }
	else if ([Model isEqualToString : @"iPhone10,6"]) { return @"iPhone X (GSM)"; }
	else if ([Model isEqualToString : @"iPhone11,2"]) { return @"iPhone XS"; }
	else if ([Model isEqualToString : @"iPhone11,4"]) { return @"iPhone XS Max"; }
	else if ([Model isEqualToString : @"iPhone11,6"]) { return @"iPhone XS Max China"; }
	else if ([Model isEqualToString : @"iPhone11,8"]) { return @"iPhone XR	"; }
	else if ([Model isEqualToString : @"iPhone12,1"]) { return @"iPhone 11"; }
	else if ([Model isEqualToString : @"iPhone12,3"]) { return @"iPhone 11 Pro"; }
	else if ([Model isEqualToString : @"iPhone12,5"]) { return @"iPhone 11 Pro Max"; }
	else if ([Model isEqualToString : @"iPhone12,8"]) { return @"iPhone SE (2nd Gen)"; }
	else if ([Model isEqualToString : @"iPhone13,1"]) { return @"iPhone 12 Mini"; }
	else if ([Model isEqualToString : @"iPhone13,2"]) { return @"iPhone 12"; }
	else if ([Model isEqualToString : @"iPhone13,3"]) { return @"iPhone 12 Pro"; }
	else if ([Model isEqualToString : @"iPhone13,4"]) { return @"iPhone 12 Pro Max"; }

	else if ([Model isEqualToString : @"iPad1,1"]) { return @"iPad1 - Wifi(model A1219)"; }
	else if ([Model isEqualToString : @"iPad1,2"]) { return @"iPad1 - Wifi + Cellular(model A1337)"; }

	else if ([Model isEqualToString : @"iPad2,1"]) { return @"iPad2 - Wifi (model A1395)"; }
	else if ([Model isEqualToString : @"iPad2,2"]) { return @"iPad2 - GSM (model A1396)"; }
	else if ([Model isEqualToString : @"iPad2,3"]) { return @"iPad2 - 3G (model A1397)"; }
	else if ([Model isEqualToString : @"iPad2,4"]) { return @"iPad2 - Wifi (model A1395)"; }


	else if ([Model isEqualToString : @"iPad2,5"]) { return @"iPad Mini - Wifi (model A1432)"; }
	else if ([Model isEqualToString : @"iPad2,6"]) { return @"iPad Mini - Wifi + Cellular (model  A1454)"; }
	else if ([Model isEqualToString : @"iPad2,7"]) { return @"iPad Mini - Wifi + Cellular (model  A1455)"; }


	else if ([Model isEqualToString : @"iPad3,1"]) { return @"iPad 3 - Wifi (model A1416)"; }
	else if ([Model isEqualToString : @"iPad3,2"]) { return @"iPad 3 - Wifi + Cellular (model  A1403)"; }
	else if ([Model isEqualToString : @"iPad3,3"]) { return @"iPad 3 - Wifi + Cellular (model  A1430)"; }


	else if ([Model isEqualToString : @"iPad3,4"]) { return @"iPad 4 - Wifi (model A1458)"; }
	else if ([Model isEqualToString : @"iPad3,5"]) { return @"iPad 4 - Wifi + Cellular (model  A1459)"; }
	else if ([Model isEqualToString : @"iPad3,6"]) { return @"iPad 4 - Wifi + Cellular (model  A1460)"; }


	else if ([Model isEqualToString : @"iPad4,1"]) { return @"iPad AIR - Wifi (model A1474)"; }
	else if ([Model isEqualToString : @"iPad4,2"]) { return @"iPad AIR - Wifi + Cellular (model A1475)"; }
	else if ([Model isEqualToString : @"iPad4,3"]) { return @"iPad AIR - Wifi + Cellular (model A1476)"; }


	else if ([Model isEqualToString : @"iPad4,4"]) { return @"iPad Mini 2 - Wifi (model A1489)"; }
	else if ([Model isEqualToString : @"iPad4,5"]) { return @"iPad Mini 2 - Wifi + Cellular (model A1490)"; }
	else if ([Model isEqualToString : @"iPad4,6"]) { return @"iPad Mini 2 - Wifi + Cellular (model A1491)"; }


	else if ([Model isEqualToString : @"iPad4,7"]) { return @"iPad Mini 3 - Wifi (model A1599)"; }
	else if ([Model isEqualToString : @"iPad4,8"]) { return @"iPad Mini 3 - Wifi + Cellular (model A1600)"; }
	else if ([Model isEqualToString : @"iPad4,9"]) { return @"iPad Mini 3 - Wifi + Cellular (model A1601)"; }


	else if ([Model isEqualToString : @"iPad5,1"]) { return @"iPad Mini 4 - Wifi (model A1538)"; }
	else if ([Model isEqualToString : @"iPad5,2"]) { return @"iPad Mini 4 - Wifi + Cellular (model A1550)"; }


	else if ([Model isEqualToString : @"iPad5,3"]) { return @"iPad AIR 2 - Wifi (model A1566)"; }
	else if ([Model isEqualToString : @"iPad5,4"]) { return @"iPad AIR 2 - Wifi + Cellular (model A1567)"; }


	else if ([Model isEqualToString : @"iPad6,3"]) { return @"iPad PRO 9.7 - Wifi (model A1673)"; }
	else if ([Model isEqualToString : @"iPad6,4"]) { return @"iPad PRO 9.7 - Wifi + Cellular (model A1674)"; }
	else if ([Model isEqualToString : @"iPad6,4"]) { return @"iPad PRO 9.7 - Wifi + Cellular (model A1675)"; }


	else if ([Model isEqualToString : @"iPad6,7"]) { return @"iPad PRO 12.9 - Wifi (model A1584)"; }
	else if ([Model isEqualToString : @"iPad6,8"]) { return @"iPad PRO 12.9 - Wifi + Cellular (model A1652)"; }


	else if ([Model isEqualToString : @"iPad6,11"]) { return @"iPad (5th Gen) - Wifi (model A1822)"; }
	else if ([Model isEqualToString : @"iPad6,12"]) { return @"iPad (5th Gen) - Wifi + Cellular (model A1823)	"; }


	else if ([Model isEqualToString : @"iPad7,1"]) { return @"iPad PRO 12.9 (2nd Gen) - Wifi (model A1670)"; }
	else if ([Model isEqualToString : @"iPad7,2"]) { return @"iPad PRO 12.9 (2nd Gen) - Wifi + Cellular (model A1671)"; }
	else if ([Model isEqualToString : @"iPad7,2"]) { return @"iPad PRO 12.9 (2nd Gen) - Wifi + Cellular (model A1821)"; }


	else if ([Model isEqualToString : @"iPad7,3"]) { return @"iPad PRO 10.5 - Wifi (model A1701)"; }
	else if ([Model isEqualToString : @"iPad7,4"]) { return @"iPad PRO 10.5 - Wifi + Cellular (model A1709)"; }


	else if ([Model isEqualToString : @"iPad7,5"]) { return @"iPad (6th Gen) - WiFi"; }
	else if ([Model isEqualToString : @"iPad7,6"]) { return @"iPad (6th Gen) - WiFi + Cellular"; }


	else if ([Model isEqualToString : @"iPad7,11"]) { return @"iPad (7th Gen) - WiFi"; }
	else if ([Model isEqualToString : @"iPad7,12"]) { return @"iPad (7th Gen) - WiFi + Cellular"; }


	else if ([Model isEqualToString : @"iPad8,1"]) { return @"iPad PRO 11 - WiFi"; }
	else if ([Model isEqualToString : @"iPad8,2"]) { return @"iPad PRO 11 - 1TB, WiFi"; }
	else if ([Model isEqualToString : @"iPad8,3"]) { return @"iPad PRO 11 - WiFi + Cellular"; }
	else if ([Model isEqualToString : @"iPad8,4"]) { return @"iPad PRO 11 - 1TB, WiFi + Cellular"; }


	else if ([Model isEqualToString : @"iPad8,5"]) { return @"iPad PRO 12.9 (3rd Gen) - WiFi"; }
	else if ([Model isEqualToString : @"iPad8,6"]) { return @"iPad PRO 12.9 (3rd Gen) - 1TB, WiFi"; }
	else if ([Model isEqualToString : @"iPad8,7"]) { return @"iPad PRO 12.9 (3rd Gen) - WiFi + Cellular"; }
	else if ([Model isEqualToString : @"iPad8,8"]) { return @"iPad PRO 12.9 (3rd Gen) - 1TB, WiFi + Cellular"; }


	else if ([Model isEqualToString : @"iPad8,9"]) {   return @"iPad PRO 11 (2nd Gen) - WiFi"; }
	else if ([Model isEqualToString : @"iPad8,10"]) { return @"iPad PRO 11 (2nd Gen) - 1TB, WiFi"; }


	else if ([Model isEqualToString : @"iPad8,11"]) { return @"iPad PRO 12.9 (4th Gen) - (WiFi)"; }
	else if ([Model isEqualToString : @"iPad8,12"]) { return @"iPad PRO 12.9 (4th Gen) - (WiFi+Cellular)"; }


	else if ([Model isEqualToString : @"iPad11,1"]) { return @"iPad Mini (5th Gen) - WiFi"; }
	else if ([Model isEqualToString : @"iPad11,2"]) { return @"iPad Mini (5th Gen) - Wifi  + Cellular"; }


	else if ([Model isEqualToString : @"iPad11,3"]) { return @"iPad 11.3 - Wifi"; }
	else if ([Model isEqualToString : @"iPad11,4"]) { return @"iPad 11.3 - Wifi  + Cellular"; }


	else if ([Model isEqualToString : @"iPod1,1"]) { return @"iPod Touch"; }
	else if ([Model isEqualToString : @"iPod2,1"]) { return @"iPod Touch Second Generation"; }
	else if ([Model isEqualToString : @"iPod3,1"]) { return @"iPod Touch Third Generation"; }
	else if ([Model isEqualToString : @"iPod4,1"]) { return @"iPod Touch Fourth Generation"; }
	else if ([Model isEqualToString : @"iPod5,1"]) { return @"iPod Touch 5th Generation"; }
	else if ([Model isEqualToString : @"iPod7,1"]) { return @"iPod Touch 6th Generation"; }
	else if ([Model isEqualToString : @"iPod9,1"]) { return @"iPod Touch 7th Generation"; }


	else if ([Model isEqualToString : @"Watch1,1"]) { return @"Apple Watch 38mm case"; }
	else if ([Model isEqualToString : @"Watch1,2"]) { return @"Apple Watch 38mm case"; }
	else if ([Model isEqualToString : @"Watch2,6"]) { return @"Apple Watch Series 1 38mm case"; }
	else if ([Model isEqualToString : @"Watch2,7"]) { return @"Apple Watch Series 1 42mm case"; }
	else if ([Model isEqualToString : @"Watch2,3"]) { return @"Apple Watch Series 2 38mm case"; }
	else if ([Model isEqualToString : @"Watch2,4"]) { return @"Apple Watch Series 2 42mm case"; }
	else if ([Model isEqualToString : @"Watch3,1"]) { return @"Apple Watch Series 3 38mm case (GPS+Cellular)"; }
	else if ([Model isEqualToString : @"Watch3,2"]) { return @"Apple Watch Series 3 42mm case (GPS+Cellular)"; }
	else if ([Model isEqualToString : @"Watch3,3"]) { return @"Apple Watch Series 3 38mm case (GPS)"; }
	else if ([Model isEqualToString : @"Watch3,4"]) { return @"Apple Watch Series 3 42mm case (GPS)"; }
	else if ([Model isEqualToString : @"Watch4,1"]) { return @"Apple Watch Series 4 40mm case (GPS)"; }
	else if ([Model isEqualToString : @"Watch4,2"]) { return @"Apple Watch Series 4 44mm case (GPS)"; }
	else if ([Model isEqualToString : @"Watch4,3"]) { return @"Apple Watch Series 4 40mm case (GPS+Cellular)"; }
	else if ([Model isEqualToString : @"Watch4,4"]) { return @"Apple Watch Series 4 44mm case (GPS+Cellular)"; }
	else if ([Model isEqualToString : @"Watch5,1"]) { return @"Apple Watch Series 5 40mm case (GPS)"; }
	else if ([Model isEqualToString : @"Watch5,2"]) { return @"Apple Watch Series 5 44mm case (GPS)"; }
	else if ([Model isEqualToString : @"Watch5,3"]) { return @"Apple Watch Series 5 40mm case (GPS+Cellular)"; }
	else if ([Model isEqualToString : @"Watch5,4"]) { return @"Apple Watch Series 5 44mm case (GPS+Cellular)"; }
	return @"ERR";
}

//-- Path to  "/var/mobile/Containers/Data/Application/%PROJECT_ID%/Library/Caches/"
+ (NSString *)getTmpFilePath
{
    NSString* path = [NSSearchPathForDirectoriesInDomains(NSCachesDirectory,  NSUserDomainMask, YES) lastObject];

	NSString* tmpStr = @"/";
    NSString* ReturnText = [path stringByAppendingString: tmpStr];

    return ReturnText;
}

@end
