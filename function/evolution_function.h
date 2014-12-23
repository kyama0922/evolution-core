#ifndef __EVOLUTION_CORE_FUNCTION_H_
#define __EVOLUTION_CORE_FUNCTION_H_

#include <evolution_type.h>

namespace EVOLUTION{
    namespace FUNCTION{

        //8bitのビット数を数える
        extern u8 BitCount8(u8 val);
        //16bitのビット数を数える
        extern u16 BitCount16(u16 val);
        //32bitのビット数を数える
        extern u32 BitCount32(u32 val);
        //64bitのビット数を数える
        extern u64 BitCount64(u64 val);


        //16bitのビット入れ替えるリトルエディアン<==>ビッグエンディアン
        extern u16 BitSwap(u16 val);
        //32bitのビット入れ替えるリトルエディアン<==>ビッグエンディアン
        extern u32 BitSwap(u32 val);
        //64bitのビット入れ替えるリトルエディアン<==>ビッグエンディアン
        extern u64 BitSwap(u64 val);

        extern void BitToChar(char out_character[2], const u8 input_data);

        //Base64にエンコードする
        extern s32 Base64encode(const u8* buffer, u32 buffer_size, u8* buf);
        //Base64からデコードする
        extern s32 Base64decode(const u8* p, u8* buf);

        //charからWcharに変換する
        extern u32 CharToWChar(c16* dest, u32 dest_len, const c8* src);
        //charからWcharに変換する
        extern u32 CharToWChar(c16* dest, u32 dest_len, const c8* src, u32 src_len);

        //Wcharからcharに変換する
        extern u32 WcharToChar(c8* dest, u32 dest_len, const c16* src);
        //Wcharからcharに変換する
        extern u32 WcharToChar(c8* dest, u32 dest_len, const c16* src, u32 src_len);

        //文字の長さを取得する
        extern u32 Strlen(const c8* src);
        //文字の長さを取得する
        extern u32 Strlen(const c16* src);
    }
}
#endif