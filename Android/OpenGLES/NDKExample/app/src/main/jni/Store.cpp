//
// Created by Darrius Wright on 10/17/15.
//

#include "com_example_dawrig_ndkexample_Store.h"
#include "com_example_dawrig_ndkexample_Store.h"
#include "Store.h"

static Store store;

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM * vm, void * reserved)
{
    JNIEnv *env;
    if (vm-> GetEnv(( void**) &env, JNI_VERSION_1_6) != JNI_OK) { abort(); }
    return JNI_VERSION_1_6;
}

/*
 * Class:     com_example_dawrig_ndkexample_Store
 * Method:    getCount
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_example_dawrig_ndkexample_Store_getCount
        (JNIEnv *, jobject)
{
    return store.length;
}

/*
 * Class:     com_example_dawrig_ndkexample_Store
 * Method:    getString
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_example_dawrig_ndkexample_Store_getString
        (JNIEnv * env, jobject, jstring key)
{
    StoreEntry * entry = findEntry(env, &store,key);
    if(isValidEntry(env,entry,StoreType_String)) {
        return env->NewStringUTF(entry->value.storeString);
    }else{
        return NULL;
    }

}

/*
 * Class:     com_example_dawrig_ndkexample_Store
 * Method:    setString
 * Signature: (Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_example_dawrig_ndkexample_Store_setString
        (JNIEnv * env, jobject obj, jstring key, jstring value)
{
    StoreEntry * entry = allocateEntry(env,&store,key);
    if(entry != NULL){
        entry->type = StoreType_String;
        jsize stringLength = env->GetStringLength(value);
        entry->value.storeString = new char[stringLength +1];
        env->GetStringUTFRegion(value, 0, stringLength, entry->value.storeString);
        entry->value.storeString[stringLength] = '\0';
    }

}

bool isValidEntry(JNIEnv * env, StoreEntry * entry, StoreType type)
{
    return ((entry != NULL) && (entry->type == type));
}
StoreEntry * allocateEntry(JNIEnv * env, Store * store, jstring key) {
    StoreEntry * entry = findEntry(env, store,key);
    if(entry == NULL) {
        entry = store->entries + store->length;
        const char * tempKey = env->GetStringUTFChars(key, NULL);
        entry->key = new char[strlen(tempKey) +1];
        strcpy(entry->key,tempKey);
        env->ReleaseStringUTFChars(key,tempKey);
        ++store->length;
    }
    else {
        releaseEntryValue(env, entry);
    }

    return entry;
}
StoreEntry * findEntry(JNIEnv * env, Store  *store, jstring key)
{
    StoreEntry * entry = store->entries;
    StoreEntry * entryEnd = entry + store->length;
    const char * tempKey = env->GetStringUTFChars(key,NULL);
    while((entry < entryEnd) && (strcmp(entry->key, tempKey) != 0)){
        ++entry;
    }

    env->ReleaseStringUTFChars(key,tempKey);

    return (entry == entryEnd) ? NULL : entry;
}
void releaseEntryValue(JNIEnv * env, StoreEntry * entry)
{
    switch(entry->type){
        case StoreType_String:
            delete entry->value.storeString;
            break;
    }
}
