#import "IosExampleArray.h"


@implementation IosExampleArray

+(NSMutableArray*) TestArray:(NSMutableArray*)text b:(NSMutableArray*)b i:(NSMutableArray*)i f:(NSMutableArray*)f l:(NSMutableArray*)l
{
	/*
	Some clever manipulations with arrays
	*/

	NSMutableArray* ArrStr = [NSMutableArray array];
	[ArrStr addObject:@"string"];
	[ArrStr addObject:@"Array"];
	return ArrStr;
}

@end
