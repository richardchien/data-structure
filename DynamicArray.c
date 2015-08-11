//
//  DynamicArray.c
//
//
//  Created by Richard Chien on 8/11/15.
//
//

#include "DynamicArray.h"

#pragma mark - Inner Function

static void *itemAt(Array *pArr, int index) {
    return pArr->pData + index * pArr->itemSize;
}

#pragma mark - Make Array

Array *ArrayInit(int itemSize) {
    Array *pArr = (Array *)malloc(sizeof(Array));
    if (!pArr) {
        return NULL;
    }
    
    pArr->pData = NULL;
    pArr->itemSize = itemSize;
    pArr->length = 0;
    
    return pArr;
}

Array *ArrayInitWithLength(int itemSize, int initLen) {
    Array *pArr = ArrayInit(itemSize);
    if (!pArr) {
        return NULL;
    }
    
    pArr->pData = calloc(initLen, itemSize);
    if (!pArr->pData) {
        free(pArr);
        return NULL;
    }
    
    pArr->length = initLen;
    
    return pArr;
}

Array *ArraySubArray(Array *pArr, int start, int length) {
    if (!pArr) {
        return NULL;
    }
    
    if (start < 0 || length < 0 || start + length > pArr->length) {
        return NULL;
    }
    
    Array *pOut = ArrayInitWithLength(pArr->itemSize, length);
    if (!pOut) {
        return NULL;
    }
    
    for (int i = 0; i < length; i++) {
        ArraySetItem(pOut, i, itemAt(pArr, start + i));
    }
    
    return pOut;
}

Array *ArrayCopyArray(Array *pArr) {
    return ArraySubArray(pArr, 0, pArr->length);
}

#pragma mark - Manipulate Whole Array

void ArrayDestroy(Array *pArr) {
    if (pArr) {
        if (pArr->pData) {
            free(pArr->pData);
            pArr->pData = NULL;
        }
        free(pArr);
    }
}

void ArrayTraverse(Array *pArr, void (*pFunc)(const void *)) {
    for (int i = 0; i < pArr->length; i++) {
        pFunc(itemAt(pArr, i));
    }
}

#pragma mark - Manipulate Single Item

bool ArrayGetItem(Array *pArr, int index, void *pOut) {
    if (!pArr) {
        return false;
    }
    
    if (index < 0 || index >= pArr->length) {
        return false;
    }
    
    memcpy(pOut, itemAt(pArr, index), pArr->itemSize);
    
    return true;
}

bool ArraySetItem(Array *pArr, int index, void *pIn) {
    if (!pArr) {
        return false;
    }
    
    if (index < 0 || index >= pArr->length) {
        return false;
    }
    
    memcpy(itemAt(pArr, index), pIn, pArr->itemSize);
    
    return true;
}

bool ArrayInsertItem(Array *pArr, int index, void *pIn) {
    if (!pArr) {
        return false;
    }
    
    if (!ArrayAppendItem(pArr, pIn)) {
        return false;
    }
    
    if (!ArrayMoveItem(pArr, pArr->length - 1, index)) {
        ArrayDeleteItem(pArr, pArr->length - 1);
        return false;
    }
    
    return true;
}

bool ArrayAppendItem(Array *pArr, void *pIn) {
    if (!pArr) {
        return false;
    }
    
    void *pData = realloc(pArr->pData, (pArr->length + 1) * pArr->itemSize);
    if (!pData) {
        return false;
    }
    
    pArr->pData = pData;
    pArr->length++;
    ArraySetItem(pArr, pArr->length - 1, pIn);
    
    return true;
}

bool ArrayMoveItem(Array *pArr, int oldIndex, int newIndex) { // TODO
    if (!pArr) {
        return false;
    }
    
    if (oldIndex < 0 || oldIndex >= pArr->length || newIndex < 0 || newIndex >= pArr->length) {
        return false;
    }
    
    if (oldIndex != newIndex) {
        void *pTemp = malloc(pArr->itemSize);
        if (!pTemp) {
            return false;
        }
        
        memcpy(pTemp, itemAt(pArr, oldIndex), pArr->itemSize);
        
        if (oldIndex > newIndex) {
            for (int i = oldIndex; i > newIndex; i--) {
                ArrayReplaceItemAWithB(pArr, i, i - 1);
            }
        } else {
            for (int i = oldIndex; i < newIndex; i++) {
                ArrayReplaceItemAWithB(pArr, i, i + 1);
            }
        }
        
        ArraySetItem(pArr, newIndex, pTemp);
        
        free(pTemp);
    }
    
    return true;
}

bool ArraySwapItems(Array *pArr, int aIndex, int bIndex) {
    if (!pArr) {
        return false;
    }
    
    if (aIndex < 0 || aIndex >= pArr->length || bIndex < 0 || bIndex >= pArr->length) {
        return false;
    }
    
    if (aIndex != bIndex) {
        void *pA = itemAt(pArr, aIndex);
        void *pB = itemAt(pArr, bIndex);
        
        void *pTemp = malloc(pArr->itemSize);
        if (!pTemp) {
            return false;
        }
        
        memcpy(pTemp, pB, pArr->itemSize);
        
        ArraySetItem(pArr, bIndex, pA);
        ArraySetItem(pArr, aIndex, pTemp);
        
        free(pTemp);
    }
    
    return true;
}

bool ArrayReplaceItemAWithB(Array *pArr, int aIndex, int bIndex) {
    if (!pArr) {
        return false;
    }
    
    if (aIndex < 0 || aIndex >= pArr->length || bIndex < 0 || bIndex >= pArr->length) {
        return false;
    }
    
    if (aIndex != bIndex) {
        memcpy(itemAt(pArr, aIndex), itemAt(pArr, bIndex), pArr->itemSize);
    }
    
    return true;
}

bool ArrayDeleteItem(Array *pArr, int index) {
    if (!pArr) {
        return false;
    }
    
    if (index < 0 || index >= pArr->length) {
        return false;
    }
    
    for (int i = index + 1; i < pArr->length; i++) {
        ArrayReplaceItemAWithB(pArr, i - 1, i);
    }
    pArr->length--;
    pArr->pData = realloc(pArr->pData, pArr->length * pArr->itemSize);
    
    return true;
}
