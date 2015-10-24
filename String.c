//
//  String.c
//  DataStructure
//
//  Created by Richard Chien on 8/14/15.
//  Copyright © 2015 Richard Chien. All rights reserved.
//

#include "String.h"

#pragma mark - Inner Function

static char *charAt(const Array *pArr, int index) {
	return (char *)(pArr->pData) + index * pArr->itemSize;
}

static int compareCh(const void *chA, const void *chB) {
    return *(const char *)chA - *(const char *)chB;
}

#pragma mark - Make String

String *StringInit() {
    return ArrayInit(sizeof(char));
}

String *StringInitWithCString(const char *pCStr) {
    if (!pCStr) {
        return NULL;
    }
    
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
    return ArraySubArray(pStr, start, length);
}

String *StringCopy(const String *pStr) {
    return ArrayCopy(pStr);
}

String *StringConcat(const String *pStrA, const String *pStrB) {
    return ArrayConcat(pStrA, pStrB);
}

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

char *StringCString(const String *pStr) {
    if (!pStr) {
        return NULL;
    }
    
    char *pCStr = calloc(pStr->length + 1, sizeof(char));
    if (!pCStr) {
        return NULL;
    }
    
    memcpy(pCStr, pStr->pData, pStr->length * pStr->itemSize);
    pCStr[pStr->length] = '\0';
    
    return pCStr;
}

char *StringSubCString(const String *pStr, int start, int length) {
    if (!pStr) {
        return NULL;
    }
    
    if (start < 0 || length < 0 || start + length > pStr->length) {
        return NULL;
    }
    
    char *pSubCStr = calloc(length + 1, sizeof(char));
    if (!pSubCStr) {
        return NULL;
    }
    
    memcpy(pSubCStr, charAt(pStr, start), length * pStr->itemSize);
    pSubCStr[length] = '\0';
    
    return pSubCStr;
}

#pragma mark - Get Properties

int StringLength(const String *pStr) {
    return pStr ? pStr->length : -1;
}

#pragma mark - Manipulate Whole String

void StringTraverse(String *pStr, void (*pFunc)(void *)) {
    ArrayTraverse(pStr, pFunc);
}

#pragma mark ---Modify
void StringDestroy(String *pStr) {
    ArrayDestroy(pStr);
}

void StringClear(String *pStr) {
    ArrayClear(pStr);
}

// Probably mess up the original order if memory is not enough
bool StringReverse(String *pStr) {
    return ArrayReverse(pStr);
}

bool StringTrimCharacter(String *pStr, char ch) {
    if (!pStr) {
        return false;
    }
    
    if (ch < 0) {
        return false;
    }
    
    char item = '\0';
    
    bool trimmingLeft = true;
    for (;;) {
        if (!pStr->length) {
            return true;
        }
        
        item = trimmingLeft ? StringFirstCharacter(pStr) : StringLastCharacter(pStr);
        
        if (item == ch) {
            if (!(trimmingLeft ? StringDeleteFirstCharacter(pStr) : StringDeleteLastCharacter(pStr))) {
                return false;
            }
        } else {
            if (trimmingLeft) {
                trimmingLeft = false;
            } else {
                break;
            }
        }
    }
    
    return true;
}

bool StringTrimCharacters(String *pStr, Array *pChsArr) {
    if (!pStr || !pChsArr) {
        return false;
    }
    
    for (int i = 0; i < pChsArr->length; i++) {
        if (!StringTrimCharacter(pStr, StringCharacter(pChsArr, i))) {
            return false;
        }
    }
    
    return true;
}

// Trim blank characters
bool StringTrim(String *pStr) {
    if (!pStr) {
        return false;
    }
    
    Array *pChsArr = ArrayInit(sizeof(char));
    char chs[6] = {' ', '\t', '\n', '\r', '\0', '\x0B'};
    for (int i = 0; i < 6; i++) {
        if (!ArrayAppendItem(pChsArr, &chs[i])) {
            ArrayDestroy(pChsArr);
            return false;
        }
    }
    
    bool result = StringTrimCharacters(pStr, pChsArr);
    
    ArrayDestroy(pChsArr);
    return result;
}

#pragma mark ---Do Not Modify

void StringPrint(const String *pStr) {
    printf("%s\n", StringCString(pStr));
}

// Return -1 if no such character, return -2 if parameters invalid
int  StringFindCharacter(const String *pStr, char ch) {
    return ArrayFind(pStr, &ch, compareCh);
}

// Return -1 if no such character, return -2 if parameters invalid
int  StringFindSubString(const String *pStr, const String *pSub) {
    if (!pStr || !pSub) {
        return -2;
    }
    
    if (pStr->length < pSub->length) {
        return -1;
    }
    
    int index = -1;
    for (int i = 0; i < pStr->length; i++) {
        if (pStr->length - i < pSub->length) {
            break;
        }
        
        if (StringCharacter(pStr, i) == StringFirstCharacter(pSub)) {
            for (int j = 0; j < pSub->length; j++) {
                if (StringCharacter(pStr, i + j) != StringCharacter(pSub, j)) {
                    break;
                }
                
                if (j == pSub->length - 1) {
                    index = i;
                }
            }
        }
        
        if (index >= 0) {
            break; // Found
        }
    }
    
    return index;
}

// Return -1 if no such character, return -2 if parameters invalid
int  StringFindSubCString(const String *pStr, const char *pCSub) {
    if (!pStr || !pCSub) {
        return -2;
    }
    
    if (pStr->length < strlen(pCSub)) {
        return -1;
    }
    
    int index = -1;
    for (int i = 0; i < pStr->length; i++) {
        if (pStr->length - i < strlen(pCSub)) {
            break;
        }
        
        if (StringCharacter(pStr, i) == *pCSub) {
            for (int j = 0; j < strlen(pCSub); j++) {
                if (StringCharacter(pStr, i + j) != *(pCSub + j)) {
                    break;
                }
                
                if (j == strlen(pCSub) - 1) {
                    index = i;
                }
            }
        }
        
        if (index >= 0) {
            break; // Found
        }
    }
    
    return index;
}

// Accept only non-NULL parameters (Return 0 if any parameter is invalid)
int  StringCompare(const String *pStrA, const String *pStrB) {
    if (!pStrA || !pStrB) {
        return 0;
    }
    
    for (int i = 0; i < pStrA->length; i++) {
        char chA = StringCharacter(pStrA, i);
        char chB = StringCharacter(pStrB, i);
        
        if (chA != chB) {
            return compareCh(&chA, &chB) > 0 ? 1 : -1;
        }
    }
    
    return 0;
}

#pragma mark - Manipulate Single Character

#pragma mark ---Get

bool StringGetCharacter(const String *pStr, int index, char *pOut) {
    return ArrayGetItem(pStr, index, pOut);
}

bool StringGetFirstCharacter(const String *pStr, char *pOut) {
    return ArrayGetFirstItem(pStr, pOut);
}

bool StringGetLastCharacter(const String *pStr, char *pOut) {
    return ArrayGetLastItem(pStr, pOut);
}

char StringCharacter(const String *pStr, int index) {
    char ch = '\0';
    StringGetCharacter(pStr, index, &ch);
    return ch;
}

char StringFirstCharacter(const String *pStr) {
    return StringCharacter(pStr, 0);
}

char StringLastCharacter(const String *pStr) {
    return StringCharacter(pStr, pStr->length - 1);
}

#pragma mark ---Replace

bool StringReplaceCharacter(String *pStr, int index, char ch) {
    return ArraySetItem(pStr, index, &ch);
}

bool StringReplaceCharacterAWithB(String *pStr, int aIndex, int bIndex) {
    return ArrayReplaceItemAWithB(pStr, aIndex, bIndex);
}

// Perhaps increase the length of the string; Example: replace("I love you",7,"shit") will make "I love shit"
bool StringReplaceSubString(String *pStr, int index, const String *pNewSub) {
    if (!pStr || !pNewSub) {
        return false;
    }
    
    if (index < 0 || index >= pStr->length) {
        return false;
    }
    
    bool shouldDoAppend = false;
    for (int i = index, j = 0; j < pNewSub->length; i++, j++) {
        if (i >= pStr->length) {
            shouldDoAppend = true;
        }
        
        if (shouldDoAppend) {
            if (!StringAppendCharacter(pStr, StringCharacter(pNewSub, j))) {
                return false;
            }
        } else {
            if (!StringReplaceCharacter(pStr, i, StringCharacter(pNewSub, j))) {
                return false;
            }
        }
    }
    
    return true;
}

bool StringReplaceSubCString(String *pStr, int index, const char *pNewCSub) {
    if (!pStr || !pNewCSub) {
        return false;
    }
    
    if (index < 0 || index >= pStr->length) {
        return false;
    }
    
    bool shouldDoAppend = false;
    for (int i = index, j = 0; j < strlen(pNewCSub); i++, j++) {
        if (i >= pStr->length) {
            shouldDoAppend = true;
        }
        
        if (shouldDoAppend) {
            if (!StringAppendCharacter(pStr, *(pNewCSub + j))) {
                return false;
            }
        } else {
            if (!StringReplaceCharacter(pStr, i, *(pNewCSub + j))) {
                return false;
            }
        }
    }
    
    return true;
}

bool StringReplaceAllCharater(String *pStr, char oldCh, char newCh);
bool StringReplaceAllSubString(String *pStr, const String *pOldSub, const String *pNewSub);
bool StringReplaceAllSubCString(String *pStr, const char *pOldCSub, const char *pNewCSub);

#pragma mark ---Insert

// Accept index range from 0 to pStr->length
bool StringInsertCharacter(String *pStr, int index, char ch);
bool StringInsertString(String *pStr, int index, const String *pNewStr);
bool StringInsertCString(String *pStr, int index, const char *pNewCStr);

#pragma mark ---Append & Prepend

bool StringAppendCharacter(String *pStr, char ch) {
    return ArrayAppendItem(pStr, &ch);
}

bool StringAppendString(String *pStr, const String *pNewStr) {
    return ArrayAppendArray(pStr, pNewStr);
}

bool StringAppendCString(String *pStr, const char *pNewCStr) {
    if (!pStr || !pNewCStr) {
        return false;
    }
    
    for (int i = 0; *(pNewCStr + i) != '\0'; i++) {
        if (!StringAppendCharacter(pStr, *(pNewCStr + i))) {
            // Delete the characters appended before
            for (int j = 0; j < i; j++) {
                StringDeleteLastCharacter(pStr);
            }
            return false;
        }
    }
    
    return true;
}

bool StringPrependCharacter(String *pStr, char ch) {
    return ArrayPrependItem(pStr, &ch);
}

bool StringPrependString(String *pStr, const String *pNewStr) {
    return ArrayPrependArray(pStr, pNewStr);
}

bool StringPrependCString(String *pStr, const char *pNewCStr) {
    return true;
}

#pragma mark ---Move & Swap

bool StringMoveCharacter(String *pStr, int oldIndex, int newIndex);
bool StringSwapCharacters(String *pStr, int aIndex, int bIndex);

#pragma mark ---Delete

bool StringDeleteCharacter(String *pStr, int index) {
    return ArrayDeleteItem(pStr, index);
}
bool StringDeleteFirstCharacter(String *pStr) {
    return ArrayDeleteFirstItem(pStr);
}
bool StringDeleteLastCharacter(String *pStr) {
    return ArrayDeleteLastItem(pStr);
}
bool StringDeleteSubString(String *pStr, int start, int length) {
    if (!pStr) {
        return false;
    }
    
    if (start < 0 || length < 0 || start + length > pStr->length) {
        return false;
    }
    
    for (int i = 0; i < length; i++) {
        StringDeleteCharacter(pStr, start);
    }
    
    return true;
}
