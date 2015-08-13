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

#pragma mark - Make Array

Array *ArrayInit(int itemSize);
Array *ArrayInitWithLength(int itemSize, int initLen);
Array *ArraySubArray(Array *pArr, int start, int length);
Array *ArrayCopyArray(Array *pArr);

#pragma mark - Get Properties

int ArrayLength(Array *pArr);
int ArrayItemSize(Array *pArr);

#pragma mark - Manipulate Whole Array

void ArrayDestroy(Array *pArr);
void ArrayTraverse(Array *pArr, void (*pFunc)(const void *));
// Probably mess up the original order if memory is not enough
bool ArraySort(Array *pArr, int (*pCompareFunc)(const void *, const void *), bool ascend);
// Probably mess up the original order if memory is not enough
bool ArrayReverse(Array *pArr);
// Return -1 if no such item, return -2 if pArr == NULL
int  ArrayFind(Array *pArr, void *pVal, int (*pCompareFunc)(const void *, const void *));

#pragma mark - Manipulate Single Item

bool ArrayGetItem(Array *pArr, int index, void *pOut);
bool ArrayGetFirstItem(Array *pArr, void *pOut);
bool ArrayGetLastItem(Array *pArr, void *pOut);
bool ArraySetItem(Array *pArr, int index, void *pIn);
// Accept index range from 0 to pArr->length
bool ArrayInsertItem(Array *pArr, int index, void *pIn);
bool ArrayAppendItem(Array *pArr, void *pIn);
bool ArrayPrependItem(Array *pArr, void *pIn);
bool ArrayMoveItem(Array *pArr, int oldIndex, int newIndex);
bool ArraySwapItems(Array *pArr, int aIndex, int bIndex);
bool ArrayReplaceItemAWithB(Array *pArr, int aIndex, int bIndex);
bool ArrayDeleteItem(Array *pArr, int index);

#endif
