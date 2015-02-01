#ifndef __EVOLUTION_THREAD_RESULT__
#define __EVOLUTION_THREAD_RESULT__

#include <evolution_type.h>

namespace EVOLUTION{
    namespace CORE{
        namespace THREAD{

            struct ThreadResult{
                enum _RESULT{
                    //----------------------------成功----------------------------
                    RESULT_OK = 0x00000000,//成功

                    //----------------------------失敗----------------------------
                    UNKNOWN_FAILED = 0x80000000, //失敗
                    WAIT_TIME_OUT_FAILED,        //Thread待機がタイムアウトしました
                    RUNNING_FAILED,              //スレッドが実行中でした
                    MUTEX_RELEASE_FAILED,        //MUTEXを開放できませんでした。
                    LOCK_FAILED,                 //スレッドをロックできませんでした。
                    PARAMETER_INDEX_OVER_FAILED, //指定したインデックスが範囲を超えました。
                    SET_SIZE_OVER_FAILED,        //セットする値が確保値の範囲を超えました。
                    SET_MEMORY_FAILED,           //MEMORYを確保できませんでした
                };
            };

            struct ThreadException{
                enum _EXCEPTION{
                    CREATE_THREAD_EXCEPTION,//Threadクラスの作成失敗
                    CREATE_MUTEX_EXCEPTION, //Mutexクラスの作成失敗
                    CREATE_THREAD_POOL_EXCEPTION, //スレッドプールクラスの作成失敗
                    CREATE_PARAMETER_EXCEPTION, //パラメータークラスの作成失敗
                    CREATE_RESULT_EXCEPTION, //リザルトクラスの作成失敗
                    THREAD_POOL_OVER_EXCEPTION, //スレッドプールが設定キューをオーバーしました。
                };
            };
        }
    }
}
#endif //__EVOLUTION_THREAD_RESULT__