#ifndef __EVOLUTION_CRYPTO_HPP__
#define __EVOLUTION_CRYPTO_HPP__

#include <evolution_type.h>
#include "../template/evolution_singleton.h"

namespace EVOLUTION{
    namespace CORE{
        class Hash : public TEMPLATE::SingletonManager < Hash > {
            friend class TEMPLATE::SingletonManager < Hash >;
        private:
            Hash();
            Hash(const Hash& t);
            u8 Convert(u8 str[2]);

            u32* mp_crc32_table;
            u64* mp_crc64_table;
        protected:
            ~Hash();
        public:
            //--------------------------------
            //MD5�A���S���Y�����d�l
            //�������ɂ͍Œ�128bit(null�������܂߂�17�o�C�g)�m�ۂ��邱��
            //�������̕����񂩂�n�b�V���R�[�h���쐬
            //--------------------------------
            void MD5(u8 dest[17], u8* src, u32 src_len);

            //--------------------------------
            //MD5�A���S���Y�����d�l
            //�������ɂ͍Œ�128bit(null�������܂߂�17�o�C�g)�m�ۂ��邱��
            //�������̕����񂩂�n�b�V���R�[�h���쐬
            //--------------------------------
            void MD5Const(u8 dest[17], const u8* src, u32 src_len);

            //--------------------------------
            //SHA�A���S���Y�����d�l
            //�������ɂ͍Œ�160bit(null�������܂߂�21�o�C�g)�m�ۂ��邱��
            //�������̕����񂩂�n�b�V���R�[�h���쐬
            //--------------------------------
            void SHA1(u8 dest[21], u8* src, u32 src_len);

            //--------------------------------
            //SHA�A���S���Y�����d�l
            //�������ɂ͍Œ�160bit(null�������܂߂�21�o�C�g)�m�ۂ��邱��
            //�������̕����񂩂�n�b�V���R�[�h���쐬
            //--------------------------------
            void SHA1Const(u8 dest[21], const u8* src, u32 src_len);

            u32 Adler_32(const u8* data, u32 length);
            u32 CRC32(const u8* data, u32 length);
            u64 CRC64(const u8* data, u32 length);
        };
    }
}

#endif //!__EVOLUTION_CRYPTO_HPP__