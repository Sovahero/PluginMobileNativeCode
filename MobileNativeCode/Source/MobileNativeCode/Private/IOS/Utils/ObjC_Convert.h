#pragma once

#include <iostream>
#include <string>

using namespace std;

//creating an alias "let" for the autotype constant
#define let __auto_type const
//creating an alias " var " for the autotype
#define var __auto_type

class ObjCconvert
{
	//======= Functions for converting to ObjC types ================
public:
	// NSString to FString
	static FString ToFString(NSString* String);

	// NSString to std::string
	static string ToString(NSString* String);

	// NSMutableDictionary* to TArray<FString>
	static TArray<FString> NSMutableArrayToTArrayFString(NSMutableArray* mArray);

	// NSMutableDictionary* to TArray<int>
	static TArray<int> NSMutableArrayToTArrayInt(NSMutableArray* mArray);

	// NSMutableDictionary* to TArray<float>
	static TArray<float> NSMutableArrayToTArrayFloat(NSMutableArray* mArray);

	// TArray<FString> to NSMutableDictionary*
	static NSMutableArray* TArrayFStringToNSMutableArray(TArray<FString> mArray);

	// TArray<anyTypeNumber> to NSMutableDictionary*
	template<typename anyType>
	static NSMutableArray* TArrayNumToNSMutableArray(TArray<anyType> mArray);
};
