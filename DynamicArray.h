//
//  DynamicArray.h
//  
//
//  Created by Richard Chien on 8/11/15.
//
//

#ifndef __DynamicArray__
#define __DynamicArray__

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    void *pData;
    int length;
    int itemSize;
} Array;

// Make Array
Array *ArrayInit(int itemSize);
Array *ArrayInitWithLength(int itemSize, int initLen);
Array *ArraySubArray(Array *pArr, int start, int length);
Array *ArrayCopyArray(Array *pArr);

// Manipulate Whole Array
void ArrayDestroy(Array *pArr);
void ArrayTraverse(Array *pArr, void (*pFunc)(const void *));

// Manipulate Single Item
bool ArrayGetItem(Array *pArr, int index, void *pOut);
bool ArraySetItem(Array *pArr, int index, void *pIn);
bool ArrayInsertItem(Array *pArr, int index, void *pIn);
bool ArrayAppendItem(Array *pArr, void *pIn);
bool ArrayMoveItem(Array *pArr, int oldIndex, int newIndex);
bool ArraySwapItems(Array *pArr, int aIndex, int bIndex);
bool ArrayReplaceItemAWithB(Array *pArr, int aIndex, int bIndex);
bool ArrayDeleteItem(Array *pArr, int index);

#endif
