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
	// NSMutableDictionary* to TArray<FString>
	static TArray<FString> NSMutableArrayToTArrayFString(NSMutableArray* mArray);

	// TArray<FString> to NSMutableDictionary*
	static NSMutableArray* TArrayFStringToNSMutableArray(TArray<FString> mArray);

  // TArray<anyTypeNumber> to NSMutableDictionary*
  template<typename anyType>
  static NSMutableArray* TArrayNumToNSMutableArray(TArray<anyType> mArray)
  {
    NSMutableArray* mMutableArray = [NSMutableArray array];
    for (auto item : mArray) {
      NSNumber* num = [NSNumber numberWithFloat : (anyType)item];
      [mMutableArray addObject : num] ;
    }
    return mMutableArray;
  }

};
