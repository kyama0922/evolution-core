#ifndef __EVOLUTION_THREAD_RESULT__
#define __EVOLUTION_THREAD_RESULT__

#include <evolution_type.h>

namespace EVOLUTION{
    namespace CORE{
        namespace THREAD{

            struct ThreadResult{
                enum _RESULT{
                    //----------------------------����----------------------------
                    RESULT_OK = 0x00000000,//����

                    //----------------------------���s----------------------------
                    UNKNOWN_FAILED = 0x80000000, //���s
                    WAIT_TIME_OUT_FAILED,        //Thread�ҋ@���^�C���A�E�g���܂���
                    RUNNING_FAILED,              //�X���b�h�����s���ł���
                    MUTEX_RELEASE_FAILED,        //MUTEX���J���ł��܂���ł����B
                    LOCK_FAILED,                 //�X���b�h�����b�N�ł��܂���ł����B
                    PARAMETER_INDEX_OVER_FAILED, //�w�肵���C���f�b�N�X���͈͂𒴂��܂����B
                    SET_SIZE_OVER_FAILED,        //�Z�b�g����l���m�ےl�͈̔͂𒴂��܂����B
                    SET_MEMORY_FAILED,           //MEMORY���m�ۂł��܂���ł���
                };
            };

            struct ThreadException{
                enum _EXCEPTION{
                    CREATE_THREAD_EXCEPTION,//Thread�N���X�̍쐬���s
                    CREATE_MUTEX_EXCEPTION, //Mutex�N���X�̍쐬���s
                    CREATE_THREAD_POOL_EXCEPTION, //�X���b�h�v�[���N���X�̍쐬���s
                    CREATE_PARAMETER_EXCEPTION, //�p�����[�^�[�N���X�̍쐬���s
                    CREATE_RESULT_EXCEPTION, //���U���g�N���X�̍쐬���s
                    THREAD_POOL_OVER_EXCEPTION, //�X���b�h�v�[�����ݒ�L���[���I�[�o�[���܂����B
                };
            };
        }
    }
}
#endif //__EVOLUTION_THREAD_RESULT__