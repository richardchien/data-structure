//
//  LinkedList.c
//  DataStructure
//
//  Created by Richard Chien on 8/12/15.
//  Copyright © 2015 Richard Chien. All rights reserved.
//

#include "LinkedList.h"

#pragma mark - Inner Function

static SinglyLListNode *sllNodeAt(SinglyLList *pList, int index) {
    SinglyLListNode *pNode = pList->pHead;
    for (int i = 0; i < index; i++) {
        pNode = pNode->pNext;
    }
    return pNode;
}

#pragma mark - Singly Linked List Make List

SinglyLList *SinglyLListInit(int itemSize) {
    SinglyLList *pList = malloc(sizeof(SinglyLList));
    if (!pList) {
        return NULL;
    }
    
    pList->pHead = NULL;
    pList->pTail = NULL;
    pList->itemSize = itemSize;
    pList->length = 0;
    
    return pList;
}

SinglyLList *SinglyLListSubList(SinglyLList *pList, int start, int length) {
    if (!pList) {
        return NULL;
    }
    
    if (start < 0 || length < 0 || start + length > pList->length) {
        return NULL;
    }
    
    SinglyLList *pOut = SinglyLListInit(pList->itemSize);
    if (!pOut) {
        return NULL;
    }
    
    SinglyLListNode *pNode = sllNodeAt(pList, start);
    for (int i = 0; i < length; i++) {
        if (!SinglyLListAppendItem(pOut, pNode->pData)) {
            SinglyLListDestroy(pOut);
            return NULL;
        }
        pNode = pNode->pNext;
    }
    
    return pOut;
}

SinglyLList *SinglyLListCopyList(SinglyLList *pList) {
    return SinglyLListSubList(pList, 0, pList->length);
}

#pragma mark - Singly Linked List Get Properties

int SinglyLListLength(SinglyLList *pList) {
    return pList->length;
}

int SinglyLListItemSize(SinglyLList *pList) {
    return pList->itemSize;
}

#pragma mark - Singly Linked List Manipulate Whole List

void SinglyLListDestroy(SinglyLList *pList) {
    if (!pList) {
        return;
    }
    
    SinglyLListClear(pList);
    free(pList);
}

void SinglyLListClear(SinglyLList *pList) {
    if (!pList) {
        return;
    }
    
    while (pList->pHead) {
        SinglyLListDeleteItem(pList, 0);
    }
}

void SinglyLListTraverse(SinglyLList *pList, void (*pFunc)(const void *)) {
    if (!pList) {
        return;
    }
    
    SinglyLListNode *pNode = pList->pHead;
    while (pNode) {
        pFunc(pNode->pData);
        pNode = pNode->pNext;
    }
}

bool SinglyLListSort(SinglyLList *pList, int (*pCompareFunc)(const void *, const void *), bool ascend) {
    if (!pList) {
        return false;
    }
    
    if (pList->length < 2) {
        return true;
    }
    
    // Bubble sort
    SinglyLListNode *pCurrHead = pList->pHead;
    bool isInOrder = false;
    while (pCurrHead->pNext && !isInOrder) {
        SinglyLListNode *pNode = pCurrHead;
        isInOrder = true;
        while (pNode->pNext) {
            if ((ascend && 0 < pCompareFunc(pNode->pData, pNode->pNext->pData)) ||
                (!ascend && 0 > pCompareFunc(pNode->pData, pNode->pNext->pData))) {
                void *pT = pNode->pData;
                pNode->pData = pNode->pNext->pData;
                pNode->pNext->pData = pT;
                isInOrder = false;
            }
            pNode = pNode->pNext;
        }
        pCurrHead = pCurrHead->pNext;
    }
    
    return true;
}

bool SinglyLListReverse(SinglyLList *pList) {
    if (!pList) {
        return false;
    }
    
    for (int i = 0; i < pList->length / 2; i++) {
        if (!SinglyLListSwapItems(pList, i, pList->length - 1 - i)) {
            // Perhaps never happen
            return false;
        }
    }
    
    return true;
}

int SinglyLListFind(SinglyLList *pList, void *pVal, int (*pCompareFunc)(const void *, const void *)) {
    if (!pList) {
        return -2;
    }
    
    SinglyLListNode *pNode = pList->pHead;
    for (int i = 0; pNode; i++) {
        if (0 == pCompareFunc(pNode->pData, pVal)) {
            return i;
        }
        pNode = pNode->pNext;
    }
    
    return -1;
}

#pragma mark - Singly Linked List Manipulate Single Item

bool SinglyLListGetItem(SinglyLList *pList, int index, void *pOut) {
    if (!pList) {
        return false;
    }
    
    if (index < 0 || index >= pList->length) {
        return false;
    }
    
    memcpy(pOut, sllNodeAt(pList, index)->pData, pList->itemSize);
    
    return true;
}

bool SinglyLListGetHeadItem(SinglyLList *pList, void *pOut) {
    if (!pList) {
        return false;
    }
    
    if (!pList->pHead) {
        return false;
    }
    
    memcpy(pOut, pList->pHead->pData, pList->itemSize);
    
    return true;
}

bool SinglyLListGetTailItem(SinglyLList *pList, void *pOut) {
    if (!pList) {
        return false;
    }
    
    if (!pList->pTail) {
        return false;
    }
    
    memcpy(pOut, pList->pTail->pData, pList->itemSize);
    
    return true;
}

bool SinglyLListSetItem(SinglyLList *pList, int index, void *pIn) {
    if (!pList) {
        return false;
    }
    
    if (index < 0 || index >= pList->length) {
        return false;
    }
    
    memcpy(sllNodeAt(pList, index)->pData, pIn, pList->itemSize);
    
    return true;
}

bool SinglyLListInsertItem(SinglyLList *pList, int index, void *pIn) {
    if (!pList) {
        return false;
    }
    
    if (index < 0 || index > pList->length) {
        return false;
    }
    
    SinglyLListNode *pNode = malloc(sizeof(SinglyLListNode));
    if (!pNode) {
        return false;
    }
    
    pNode->pData = malloc(pList->itemSize);
    if (!pNode->pData) {
        free(pNode);
        return false;
    }
    
    memcpy(pNode->pData, pIn, pList->itemSize);
    pNode->pNext = NULL;
    
    if (index == 0) {
        pNode->pNext = pList->pHead;
        pList->pHead = pNode;
        if (pList->length == 0) {
            pList->pTail = pNode;
        }
    } else {
        SinglyLListNode *pPrev = sllNodeAt(pList, index - 1);
        pNode->pNext = pPrev->pNext;
        pPrev->pNext = pNode;
        if (index == pList->length) {
            pList->pTail = pNode;
        }
    }
    
    pList->length++;
    
    return true;
}

bool SinglyLListAppendItem(SinglyLList *pList, void *pIn) {
    return SinglyLListInsertItem(pList, pList->length, pIn);
}

bool SinglyLListPrependItem(SinglyLList *pList, void *pIn) {
    return SinglyLListInsertItem(pList, 0, pIn);
}

bool SinglyLListMoveItem(SinglyLList *pList, int oldIndex, int newIndex) {
    if (!pList) {
        return false;
    }
    
    if (oldIndex < 0 || oldIndex >= pList->length || newIndex < 0 || newIndex >= pList->length) {
        return false;
    }
    
    if (oldIndex == newIndex) {
        return true;
    }
    
    if (oldIndex == 0) {
        SinglyLListNode *pThis = pList->pHead;
        SinglyLListNode *pTemp = sllNodeAt(pList, newIndex);
        pList->pHead = pThis->pNext;
        pThis->pNext = pTemp->pNext;
        pTemp->pNext = pThis;
        if (newIndex == pList->length - 1) {
            pList->pTail = pThis;
        }
    } else if (oldIndex == pList->length - 1) {
        SinglyLListNode *pThis = pList->pTail;
        pList->pTail = sllNodeAt(pList, oldIndex - 1);
        pList->pTail->pNext = NULL;
        
        if (newIndex == 0) {
            pThis->pNext = pList->pHead;
            pList->pHead = pThis;
        } else {
            SinglyLListNode *pTempPrev = sllNodeAt(pList, newIndex - 1);
            SinglyLListNode *pTemp = pTempPrev->pNext;
            pTempPrev->pNext = pThis;
            pThis->pNext = pTemp;
        }
    } else {
        SinglyLListNode *pThisPrev = sllNodeAt(pList, oldIndex - 1);
        SinglyLListNode *pThis = pThisPrev->pNext;
        SinglyLListNode *pTemp = sllNodeAt(pList, newIndex);
        pThisPrev->pNext = pThis->pNext;
        
        if (newIndex == 0) {
            pThis->pNext = pList->pHead;
            pList->pHead = pThis;
        } else {
            if (oldIndex < newIndex) {
                pThis->pNext = pTemp->pNext;
                pTemp->pNext = pThis;
                if (newIndex == pList->length - 1) {
                    pList->pTail = pThis;
                }
            } else {
                sllNodeAt(pList, newIndex - 1)->pNext = pThis;
                pThis->pNext = pTemp;
            }
        }
    }
    
    return true;
}

bool SinglyLListSwapItems(SinglyLList *pList, int aIndex, int bIndex) {
    if (!pList) {
        return false;
    }
    
    if (aIndex < 0 || aIndex >= pList->length || bIndex < 0 || bIndex >= pList->length) {
        return false;
    }
    
    if (aIndex == bIndex) {
        return true;
    }
    
    SinglyLListNode *pNodeA = sllNodeAt(pList, aIndex);
    SinglyLListNode *pNodeB = sllNodeAt(pList, bIndex);
    void *pDataTemp = pNodeA->pData;
    pNodeA->pData = pNodeB->pData;
    pNodeB->pData = pDataTemp;
    
    return true;
}

bool SinglyLListReplaceItemAWithB(SinglyLList *pList, int aIndex, int bIndex) {
    if (!pList) {
        return false;
    }
    
    if (aIndex < 0 || aIndex >= pList->length || bIndex < 0 || bIndex >= pList->length) {
        return false;
    }
    
    if (aIndex == bIndex) {
        return true;
    }
    
    void *pData = sllNodeAt(pList, bIndex)->pData;
    SinglyLListSetItem(pList, aIndex, pData);
    
    return true;
}

bool SinglyLListDeleteItem(SinglyLList *pList, int index) {
    if (!pList) {
        return false;
    }
    
    if (index < 0 || index >= pList->length) {
        return false;
    }
    
    if (index > 0) {
        SinglyLListNode *pPrev = sllNodeAt(pList, index - 1);
        SinglyLListNode *pThis = pPrev->pNext;
        pPrev->pNext = pThis->pNext;
        free(pThis->pData);
        free(pThis);
        if (index == pList->length - 1) {
            pPrev->pNext = NULL;
            pList->pTail = pPrev;
        }
    } else {
        SinglyLListNode *pThis = pList->pHead;
        pList->pHead = pThis->pNext;
        free(pThis->pData);
        free(pThis);
        if (pList->length == 1) {
            pList->pHead = NULL;
            pList->pTail = NULL;
        }
    }
    pList->length--;
    
    return true;
}
