#include "evolution_thread_implement.h"

using namespace EVOLUTION;
using namespace EVOLUTION::CORE;
using namespace EVOLUTION::CORE::THREAD;

EVOLUTION::RESULT EVOLUTION::FUNCTION::CreateThread(CORE::THREAD::IThread** pp_thread, u32 stack_size){
    Thread* thread = NEW Thread(stack_size);
    if (thread == nullptr)
    {
        throw ThreadException::CREATE_THREAD_EXCEPTION;
    }
    *pp_thread = thread;
    return EVOLUTION::_RESULT::S_ok;
}


EVOLUTION::RESULT EVOLUTION::FUNCTION::CreateThreadMutex(CORE::THREAD::IMutex** pp_mutex){
    Mutex* mutex = NEW Mutex();
    if (mutex == nullptr)
    {
        throw ThreadException::CREATE_MUTEX_EXCEPTION;
    }
    *pp_mutex = mutex;
    return EVOLUTION::_RESULT::S_ok;
}


EVOLUTION::RESULT EVOLUTION::FUNCTION::CreateThreadPool(CORE::THREAD::IThreadPool** pp_thread_pool, u32 stack_size, u32 pool_count, u32 queue_size){
    ThreadPool* thread_pool = NEW ThreadPool(stack_size, pool_count, queue_size);
    if (thread_pool == nullptr)
    {
        throw ThreadException::CREATE_THREAD_POOL_EXCEPTION;
    }
    *pp_thread_pool = thread_pool;
    return EVOLUTION::_RESULT::S_ok;
}


EVOLUTION::RESULT EVOLUTION::FUNCTION::CreateParameter(CORE::THREAD::IParameter** pp_parameter){
    Parameter* parameter = NEW Parameter();
    if (parameter == nullptr)
    {
        throw ThreadException::CREATE_THREAD_POOL_EXCEPTION;
    }
    *pp_parameter = parameter;
    return EVOLUTION::_RESULT::S_ok;
}


EVOLUTION::RESULT EVOLUTION::FUNCTION::CreateResult(CORE::THREAD::IResult** pp_result){
    Result* result = NEW Result();
    if (result == nullptr)
    {
        throw ThreadException::CREATE_THREAD_POOL_EXCEPTION;
    }
    *pp_result = result;
    return EVOLUTION::_RESULT::S_ok;
}