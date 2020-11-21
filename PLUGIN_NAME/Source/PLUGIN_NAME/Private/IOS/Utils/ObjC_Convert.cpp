#include "ObjC_Convert.h"

//==============ObjC Convert===================================

// NSString to FString
FString ObjConvert::ToFString(NSString* String)
{
	std::string TmpStr = std::string([String UTF8String]);
	return TmpStr.c_str();
}

// NSString to std::string
string ObjConvert::ToString(NSString* String)
{
	return std::string([String UTF8String]);	
}

// NSMutableDictionary* to TArray<FString>
TArray<FString> ObjConvert::NSMutableArrayToTArrayFString (NSMutableArray* mArray)
{
	TArray<FString> TmpArr;
	for (NSString* item in mArray) {
		TmpArr.Add( ObjConvert::ToFString(item) );
	}
	return TmpArr;
}

// NSMutableDictionary* to TArray<int>
TArray<int> ObjConvert::NSMutableArrayToTArrayInt(NSMutableArray* mArray)
{
	TArray<int> TmpArr;
	for (NSNumber* item in mArray) {
		TmpArr.Add([item intValue]);
	}
	return TmpArr;
}

// NSMutableDictionary* to TArray<float>
TArray<float> ObjConvert::NSMutableArrayToTArrayFloat(NSMutableArray* mArray)
{
	TArray<float> TmpArr;
	for (NSNumber* item in mArray) {
		TmpArr.Add([item floatValue]);
	}
	return TmpArr;
}

// TArray<FString> to NSMutableDictionary* 
NSMutableArray* ObjConvert::TArrayFStringToNSMutableArray(TArray<FString> mArray)
{
	NSMutableArray* mMutableArray = [NSMutableArray array];
	for (auto item : mArray) {
			[mMutableArray addObject: item.GetNSString() ];
	}
	return mMutableArray;
}

// TArray<anyTypeNumber> to NSMutableDictionary*
template<typename anyType>
NSMutableArray* ObjConvert::TArrayNumToNSMutableArray(TArray<anyType> mArray)
{
	NSMutableArray* mMutableArray = [NSMutableArray array];
	for (auto item : mArray) {
		NSNumber* num = [NSNumber numberWithFloat : (anyType)item];
		[mMutableArray addObject:num] ;
	}
	return mMutableArray;
}