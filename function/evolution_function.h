#ifndef __EVOLUTION_CORE_FUNCTION_H_
#define __EVOLUTION_CORE_FUNCTION_H_

#include <evolution_type.h>

namespace EVOLUTION{
    namespace FUNCTION{

        //8bit�̃r�b�g���𐔂���
        extern u8 BitCount8(u8 val);
        //16bit�̃r�b�g���𐔂���
        extern u16 BitCount16(u16 val);
        //32bit�̃r�b�g���𐔂���
        extern u32 BitCount32(u32 val);
        //64bit�̃r�b�g���𐔂���
        extern u64 BitCount64(u64 val);


        //16bit�̃r�b�g����ւ��郊�g���G�f�B�A��<==>�r�b�O�G���f�B�A��
        extern u16 BitSwap(u16 val);
        //32bit�̃r�b�g����ւ��郊�g���G�f�B�A��<==>�r�b�O�G���f�B�A��
        extern u32 BitSwap(u32 val);
        //64bit�̃r�b�g����ւ��郊�g���G�f�B�A��<==>�r�b�O�G���f�B�A��
        extern u64 BitSwap(u64 val);

        extern void BitToChar(char out_character[2], const u8 input_data);

        //Base64�ɃG���R�[�h����
        extern s32 Base64encode(const u8* buffer, u32 buffer_size, u8* buf);
        //Base64����f�R�[�h����
        extern s32 Base64decode(const u8* p, u8* buf);

        //char����Wchar�ɕϊ�����
        extern u32 CharToWChar(c16* dest, u32 dest_len, const c8* src);
        //char����Wchar�ɕϊ�����
        extern u32 CharToWChar(c16* dest, u32 dest_len, const c8* src, u32 src_len);

        //Wchar����char�ɕϊ�����
        extern u32 WcharToChar(c8* dest, u32 dest_len, const c16* src);
        //Wchar����char�ɕϊ�����
        extern u32 WcharToChar(c8* dest, u32 dest_len, const c16* src, u32 src_len);

        //�����̒������擾����
        extern u32 Strlen(const c8* src);
        //�����̒������擾����
        extern u32 Strlen(const c16* src);
    }
}
#endif