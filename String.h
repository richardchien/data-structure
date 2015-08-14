//
//  String.h
//  DataStructure
//
//  Created by Richard Chien on 8/14/15.
//  Copyright © 2015 Richard Chien. All rights reserved.
//

#ifndef __String__
#define __String__

#include <stdio.h>

#include "DynamicArray.h"

typedef Array String;

#pragma mark - Make String

String *StringInit(int itemSize);
String *StringSubString(const String *pStr, int start, int length);
String *StringCopy(const String *pStr);
String *StringConcat(const String *pStrA, const String *pStrB);

char *StringCString(const String *pStr);
char *StringSubCString(const String *pStr, int start, int length);

#pragma mark - Get Properties

int StringLength(const String *pStr);

#pragma mark - Manipulate Whole String

void StringDestroy(String *pStr);
void StringClear(String *pStr);
void StringTraverse(String *pStr, void (*pFunc)(void *));
void StringPrint(const String *pStr);
// Probably mess up the original order if memory is not enough
bool StringReverse(String *pStr);
// Return -1 if no such character, return -2 if pStr == NULL
int  StringFindCharacter(const String *pStr, char ch);
// Return -1 if no such substring, return -2 if pStr == NULL
int  StringFindSubString(const String *pStr, const String *pSub);
// Return -1 if no such substring, return -2 if pStr == NULL
int  StringFindSubCString(const String *pStr, const char *pCSub);
int  StringCompare(const String *pStrA, const String *pStrB);

#pragma mark - Manipulate Single Character

bool StringGetCharacter(const String *pStr, int index, char *pOut);
bool StringGetFirstCharacter(const String *pStr, char *pOut);
bool StringGetLastCharacter(const String *pStr, char *pOut);
char StringCharacter(const String *pStr, int index);
char StringFirstCharacter(const String *pStr);
char StringLastCharacter(const String *pStr);

bool StringReplaceCharacter(String *pStr, int index, char ch);
bool StringReplaceSubString(String *pStr, int index, String *pNewSub);
bool StringReplaceSubCString(String *pStr, int index, char *pNewCSub);

// Accept index range from 0 to pStr->length
bool StringInsertCharacter(String *pStr, int index, char ch);
bool StringInsertString(String *pStr, int index, String *pNewStr);
bool StringInsertCString(String *pStr, int index, char *pNewCStr);

bool StringAppendCharacter(String *pStr, char ch);
bool StringAppendString(String *pStr, String *pNewStr);
bool StringAppendCString(String *pStr, char *pNewCStr);

bool StringPrependCharacter(String *pStr, char ch);
bool StringPrependString(String *pStr, String *pNewStr);
bool StringPrependCString(String *pStr, char *pNewCStr);

bool StringMoveCharacter(String *pStr, int oldIndex, int newIndex);
bool StringSwapCharacters(String *pStr, int aIndex, int bIndex);
bool StringReplaceCharacterAWithB(String *pStr, int aIndex, int bIndex);

bool StringDeleteCharacter(String *pStr, int index);
bool StringDeleteSubString(String *pStr, int start, int length);

// Trim

#endif
