#include "evolution_function.h"

using namespace EVOLUTION;
using namespace EVOLUTION::FUNCTION;

s32 EVOLUTION::FUNCTION::Base64encode(const u8* buffer, u32 buffer_size, u8* buf) {
    const char b64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";
    const s32 in_size = buffer_size;
    if (in_size == 0) return 0;

    s32 cnt = 0;
    for (s32 i = 0; i < (in_size - 1) / 3 + 1; i++) {
        const unsigned char* c = (const unsigned char*) (&buffer[i * 3]);
        for (s32 j = 0; j < 4; j++) {
            if (in_size >= i * 3 + j) {
                buf[cnt++] = b64[(c[j - 1] << (6 - j * 2) | c[j] >> (j * 2 + 2)) & 0x3f];
            } else {
                buf[cnt++] = '=';
            }
        }
    }
    buf[cnt] = '\0';

    return cnt;
}

s32 EVOLUTION::FUNCTION::Base64decode(const u8* p, u8* buf) {
    char b64[128] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";

    char c[4];
    s32 i = 0, j, k;
    while (*p && *p != '=') {
        for (j = 0; j < 4 && *p != '='; j++) {
            c[j] = b64[*p++];
        }
        for (k = 0; k < j - 1; k++) {
            buf[i++] = (c[k] << ((k << 1) + 2)) | (c[k + 1] >> ((2 - k) << 1));
        }
    }
    buf[i] = '\0';

    return i;
}
