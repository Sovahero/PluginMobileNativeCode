#include "ObjC_Convert.h"

//-- ObjC Convert

// NSMutableDictionary* to TArray<FString>
TArray<FString> ObjCconvert::NSMutableArrayToTArrayFString (NSMutableArray* mArray)
{
	TArray<FString> TmpArr;
	for (NSString* item in mArray) {
		TmpArr.Add( FString(item) );
	}
	return TmpArr;
}

// TArray<FString> to NSMutableDictionary* 
NSMutableArray* ObjCconvert::TArrayFStringToNSMutableArray(TArray<FString> mArray)
{
	NSMutableArray* mMutableArray = [NSMutableArray array];
	for (auto item : mArray) {
			[mMutableArray addObject: item.GetNSString() ];
	}
	return mMutableArray;
}

