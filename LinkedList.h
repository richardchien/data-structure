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

#pragma mark - Singly Linked List

typedef struct singly_llist_node {
    void *pData;
    struct singly_llist_node *pNext;
} SinglyLListNode;

typedef struct {
    SinglyLListNode *pHead;
    SinglyLListNode *pTail;
    int itemSize;
    int length;
} SinglyLList;

#pragma mark - Singly Linked List Make List

SinglyLList *SinglyLListInit(int itemSize);
SinglyLList *SinglyLListSubList(SinglyLList *pList, int start, int length);
SinglyLList *SinglyLListCopyList(SinglyLList *pList);

#pragma mark - Singly Linked List Get Properties

int SinglyLListLength(SinglyLList *pList);
int SinglyLListItemSize(SinglyLList *pList);

#pragma mark - Singly Linked List Manipulate Whole List

void SinglyLListDestroy(SinglyLList *pList);
void SinglyLListClear(SinglyLList *pList);
void SinglyLListTraverse(SinglyLList *pList, void (*pFunc)(const void *));
bool SinglyLListSort(SinglyLList *pList, int (*pCompareFunc)(const void *, const void *), bool ascend);
bool SinglyLListReverse(SinglyLList *pList);
int  SinglyLListFind(SinglyLList *pList, void *pVal, int (*pCompareFunc)(const void *, const void *));

#pragma mark - Singly Linked List Manipulate Single Item

bool SinglyLListGetItem(SinglyLList *pList, int index, void *pOut);
bool SinglyLListGetHeadItem(SinglyLList *pList, void *pOut);
bool SinglyLListGetTailItem(SinglyLList *pList, void *pOut);
bool SinglyLListSetItem(SinglyLList *pList, int index, void *pIn);
bool SinglyLListInsertItem(SinglyLList *pList, int index, void *pIn);
bool SinglyLListAppendItem(SinglyLList *pList, void *pIn);
bool SinglyLListPrependItem(SinglyLList *pList, void *pIn);
bool SinglyLListMoveItem(SinglyLList *pList, int oldIndex, int newIndex);
bool SinglyLListSwapItems(SinglyLList *pList, int aIndex, int bIndex);
bool SinglyLListReplaceItemAWithB(SinglyLList *pList, int aIndex, int bIndex);
bool SinglyLListDeleteItem(SinglyLList *pList, int index);

#endif
