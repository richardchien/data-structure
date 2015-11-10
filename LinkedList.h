//
//  LinkedList.h
//  DataStructure
//
//  Created by Richard Chien on 8/12/15.
//  Copyright © 2015 Richard Chien. All rights reserved.
//

#ifndef __LinkedList__
#define __LinkedList__

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#pragma mark - Type Definition

typedef struct _singly_llist SinglyLList;

#pragma mark - Singly Linked List Make List

SinglyLList *SinglyLListInit(int itemSize);
SinglyLList *SinglyLListSubList(const SinglyLList *pList, int start, int length);
SinglyLList *SinglyLListCopy(const SinglyLList *pList);
SinglyLList *SinglyLListConcat(const SinglyLList *pListA, const SinglyLList *pListB);

#pragma mark - Singly Linked List Get Properties

int SinglyLListLength(const SinglyLList *pList);
int SinglyLListItemSize(const SinglyLList *pList);

#pragma mark - Singly Linked List Manipulate Whole List

void SinglyLListDestroy(SinglyLList *pList);
void SinglyLListClear(SinglyLList *pList);
void SinglyLListTraverse(SinglyLList *pList, void (*pFunc)(void *));
bool SinglyLListSort(SinglyLList *pList, int (*pCompareFunc)(const void *, const void *), bool ascend);
bool SinglyLListReverse(SinglyLList *pList);
// Return -1 if no such item, return -2 if parameters invalid
int  SinglyLListFind(const SinglyLList *pList, const void *pVal, int (*pCompareFunc)(const void *, const void *));

#pragma mark - Singly Linked List Manipulate Single Item

bool SinglyLListGetItem(const SinglyLList *pList, int index, void *pOut);
bool SinglyLListGetHeadItem(const SinglyLList *pList, void *pOut);
bool SinglyLListGetTailItem(const SinglyLList *pList, void *pOut);
bool SinglyLListSetItem(SinglyLList *pList, int index, const void *pIn);
// Accept index range from 0 to pList->length
bool SinglyLListInsertItem(SinglyLList *pList, int index, const void *pIn);
// Accept index range from 0 to pList->length
bool SinglyLListInsertLList(SinglyLList *pList, int index, const SinglyLList *pNewList);
bool SinglyLListAppendItem(SinglyLList *pList, const void *pIn);
bool SinglyLListAppendLList(SinglyLList *pList, const SinglyLList *pNewList);
bool SinglyLListPrependItem(SinglyLList *pList, const void *pIn);
bool SinglyLListPrependLList(SinglyLList *pList, const SinglyLList *pNewList);
bool SinglyLListMoveItem(SinglyLList *pList, int oldIndex, int newIndex);
bool SinglyLListSwapItems(SinglyLList *pList, int aIndex, int bIndex);
bool SinglyLListReplaceItemAWithB(SinglyLList *pList, int aIndex, int bIndex);
bool SinglyLListDeleteItem(SinglyLList *pList, int index);
bool SinglyLListDeleteHeadItem(SinglyLList *pList);
bool SinglyLListDeleteTailItem(SinglyLList *pList);

#endif
