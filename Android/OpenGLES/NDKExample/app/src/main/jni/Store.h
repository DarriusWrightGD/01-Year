//
// Created by Darrius Wright on 10/17/15.
//

#ifndef NDKEXAMPLE_STORE_H
#define NDKEXAMPLE_STORE_H

#define MAX_ENTRIES 16
#include "jni.h"
#include <cstddef>
#include <cstdlib>
#include <string.h>


typedef enum{
    StoreType_Integer,
    StoreType_String,
    StoreType_Color
}StoreType;

typedef union{
    int32_t storeInteger;
    char * storeString;
    jobject storeColor;
}StoreValue;

typedef struct {
    char * key;
    StoreType type;
    StoreValue value;
}StoreEntry;


typedef struct {
    StoreEntry entries[MAX_ENTRIES];
    int length;
}Store;

bool isValidEntry(JNIEnv * env, StoreEntry * entry, StoreType type);
StoreEntry * allocateEntry(JNIEnv * env, Store * store, jstring key);
StoreEntry * findEntry(JNIEnv * env, Store  *store, jstring key);
void releaseEntryValue(JNIEnv * env, StoreEntry * entry);

#endif //NDKEXAMPLE_STORE_H
