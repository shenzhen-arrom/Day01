#include <jni.h>
#include <string>

extern  const char * arrom="";

int checkUtfString(const char* bytes)
{
    const char* origBytes = bytes;
    if (bytes == NULL) {
        return -1;
    }
    while (*bytes != '\0') {
        unsigned char utf8 = *(bytes++);
        // Switch on the high four bits.
        switch (utf8 >> 4) {
            case 0x00:
            case 0x01:
            case 0x02:
            case 0x03:
            case 0x04:
            case 0x05:
            case 0x06:
            case 0x07: {
                // Bit pattern 0xxx. No need for any extra bytes.
                break;
            }
            case 0x08:
            case 0x09:
            case 0x0a:
            case 0x0b:
            case 0x0f: {

                printf("****JNI WARNING: illegal start byte 0x%x\n", utf8);
                return -1;
            }
            case 0x0e: {
                // Bit pattern 1110, so there are two additional bytes.
                utf8 = *(bytes++);
                if ((utf8 & 0xc0) != 0x80) {
                    printf("****JNI WARNING: illegal continuation byte 0x%x\n", utf8);
                    return -1;
                }
                // Fall through to take care of the final byte.
            }
            case 0x0c:
            case 0x0d: {
                // Bit pattern 110x, so there is one additional byte.
                utf8 = *(bytes++);
                if ((utf8 & 0xc0) != 0x80) {
                    printf("****JNI WARNING: illegal continuation byte 0x%x\n", utf8);
                    return -1;
                }
                break;
            }
        }
    }
    return 0;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_langyi_day01_MainActivity_getAccount(JNIEnv *env, jobject instance) {

    // TODO
    printf("%s",arrom);
//    if(checkUtfString(arrom)!=1){
//        arrom="格式有问题";
//    }
    return env->NewStringUTF(arrom);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_langyi_day01_MainActivity_setAccount(JNIEnv *env, jobject instance, jbyteArray src_) {
    jbyte *src = env->GetByteArrayElements(src_, NULL);

    // TODO c++收到byte[]
    arrom= (const char *) src;

//    env->ReleaseByteArrayElements(src_, src, 0);
}
