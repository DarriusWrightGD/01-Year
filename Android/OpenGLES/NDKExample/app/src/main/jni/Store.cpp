//
// Created by Darrius Wright on 10/17/15.
//

/*
 * Everything is local by default
 * To be able to use an object reference outside the method scope, or keep it for a long period of time then
 * the object must be made global NewGlobalRef (also for threading use) and DeleteGlobalRef
 *
 * IsSameObject to compare two references
 *
 * NewWeakGlobalRef and DeleteWeakGlobalRef
 * These  can be kept between jni calls and shared between threads, but don't prevent garbage collection.
 * As a result must be used with care. You must create a global or local reference from them before use
 * each time you need it and release right after.
 * */

#include "com_example_dawrig_ndkexample_Store.h"
#include "com_example_dawrig_ndkexample_Store.h"
#include "Store.h"

static Store store;

//called once before anything else
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
 * gets the length of the store array
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
 * get the string from the
 */
JNIEXPORT jstring JNICALL Java_com_example_dawrig_ndkexample_Store_getString
        (JNIEnv * env, jobject, jstring key)
{
    StoreEntry * entry = findEntry(env, &store,key);
    return isValidEntry(env,entry,StoreType_String) ? env->NewStringUTF(entry->value.storeString) : NULL;
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

/*
 * Class:     com_example_dawrig_ndkexample_Store
 * Method:    getInteger
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_com_example_dawrig_ndkexample_Store_getInteger
        (JNIEnv * env, jobject, jstring key)
{
    StoreEntry * entry = findEntry(env,&store,key);
    return isValidEntry(env, entry, StoreType_Integer) ? entry->value.storeInteger : 0 ;
}

/*
 * Class:     com_example_dawrig_ndkexample_Store
 * Method:    setInteger
 * Signature: (Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_example_dawrig_ndkexample_Store_setInteger
        (JNIEnv * env, jobject, jstring key, jint value)
{
    StoreEntry * entry = allocateEntry(env, &store, key);
    if(entry != NULL){
        entry->type = StoreType_Integer;
        entry->value.storeInteger = value;
    }
}

/*
 * Class:     com_example_dawrig_ndkexample_Store
 * Method:    getColor
 * Signature: (Ljava/lang/String;)Lcom/example/dawrig/ndkexample/Color;
 */
JNIEXPORT jobject JNICALL Java_com_example_dawrig_ndkexample_Store_getColor
        (JNIEnv * env, jobject, jstring key) {
    StoreEntry * entry = findEntry(env,&store,key);
    return isValidEntry(env,entry,StoreType_Color) ? entry->value.storeColor : NULL;
}

/*
 * Class:     com_example_dawrig_ndkexample_Store
 * Method:    setColor
 * Signature: (Ljava/lang/String;Lcom/example/dawrig/ndkexample/Color;)V
 */
JNIEXPORT void JNICALL Java_com_example_dawrig_ndkexample_Store_setColor
        (JNIEnv * env, jobject, jstring key, jobject color){
    StoreEntry * entry = allocateEntry(env,&store,key);
    if(entry != NULL){
        entry->type = StoreType_Color;
        entry->value.storeColor = env->NewGlobalRef(color);
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
        case StoreType_Color:
            delete env->DeleteGlobalRef(entry->value.storeColor);
            break;
    }
}
