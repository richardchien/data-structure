//
//  String.c
//  DataStructure
//
//  Created by Richard Chien on 8/14/15.
//  Copyright © 2015 Richard Chien. All rights reserved.
//

#include "String.h"

#pragma mark - Make String

String *StringInit() {
    return ArrayInit(sizeof(char));
}

String *StringInitWithCString(const char *pCStr) {
    String *pStr = StringInit();
    if (!pStr) {
        return NULL;
    }
    
    if (!StringAppendCString(pStr, pCStr)) {
        StringDestroy(pStr);
        return NULL;
    }
    
    return pStr;
}

String *StringSubString(const String *pStr, int start, int length) {
    return ArraySubArray((Array *)pStr, start, length);
}

String *StringCopy(const String *pStr) {
    return ArrayCopy((Array *)pStr);
}

String *StringConcat(const String *pStrA, const String *pStrB);
// Accept Array of String
String *StringJoin(const Array *pStrArr, char separator);
// Accept Array of C string
String *StringJoinC(const Array *pCStrArr, char separator);
// Accept Array of String
char   *CStringJoin(const Array *pStrArr, char separator);
// Return Array of String
Array *StringSplit(const String *pStr, char separator);
// Return Array of String
Array *StringSplitC(const char *pCStr, char separator);
// Return Array of C string
Array *CStringSplit(const String *pStr, char separator);

char *StringCString(const String *pStr);
char *StringSubCString(const String *pStr, int start, int length);

#pragma mark - Get Properties

int StringLength(const String *pStr);

#pragma mark - Manipulate Whole String

void StringTraverse(String *pStr, void (*pFunc)(void *));

#pragma mark ---Modify
void StringDestroy(String *pStr);
void StringClear(String *pStr);
// Probably mess up the original order if memory is not enough
bool StringReverse(String *pStr);

bool StringTrimCharacter(String *pStr, char ch);
// Trim blank characters
bool StringTrim(String *pStr);

#pragma mark ---Do Not Modify
void StringPrint(const String *pStr);
// Return -1 if no such character, return -2 if pStr == NULL
int  StringFindCharacter(const String *pStr, char ch);
// Return -1 if no such substring, return -2 if pStr == NULL
int  StringFindSubString(const String *pStr, const String *pSub);
// Return -1 if no such substring, return -2 if pStr == NULL
int  StringFindSubCString(const String *pStr, const char *pCSub);
int  StringCompare(const String *pStrA, const String *pStrB);

#pragma mark - Manipulate Single Character

#pragma mark ---Get
bool StringGetCharacter(const String *pStr, int index, char *pOut);
bool StringGetFirstCharacter(const String *pStr, char *pOut);
bool StringGetLastCharacter(const String *pStr, char *pOut);
char StringCharacter(const String *pStr, int index);
char StringFirstCharacter(const String *pStr);
char StringLastCharacter(const String *pStr);

#pragma mark ---Replace
bool StringReplaceCharacter(String *pStr, int index, char ch);
bool StringReplaceCharacterAWithB(String *pStr, int aIndex, int bIndex);
bool StringReplaceSubString(String *pStr, int index, const String *pNewSub);
bool StringReplaceSubCString(String *pStr, int index, const char *pNewCSub);
bool StringReplaceAllCharater(String *pStr, char oldCh, char newCh);
bool StringReplaceAllSubString(String *pStr, const String *pOldSub, const String *pNewSub);
bool StringReplaceAllSubCString(String *pStr, const char *pOldCSub, const char *pNewCSub);

#pragma mark ---Insert
// Accept index range from 0 to pStr->length
bool StringInsertCharacter(String *pStr, int index, char ch);
bool StringInsertString(String *pStr, int index, const String *pNewStr);
bool StringInsertCString(String *pStr, int index, const char *pNewCStr);

#pragma mark ---Append & Prepend
bool StringAppendCharacter(String *pStr, char ch);
bool StringAppendString(String *pStr, const String *pNewStr);
bool StringAppendCString(String *pStr, const char *pNewCStr);
bool StringPrependCharacter(String *pStr, char ch);
bool StringPrependString(String *pStr, const String *pNewStr);
bool StringPrependCString(String *pStr, const char *pNewCStr);

#pragma mark ---Move & Swap
bool StringMoveCharacter(String *pStr, int oldIndex, int newIndex);
bool StringSwapCharacters(String *pStr, int aIndex, int bIndex);

#pragma mark ---Delete
bool StringDeleteCharacter(String *pStr, int index);
bool StringDeleteSubString(String *pStr, int start, int length);
