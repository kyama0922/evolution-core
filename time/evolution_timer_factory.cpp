#include "evolution_timer_implement.h"
#include <Windows.h>

using namespace EVOLUTION;
using namespace EVOLUTION::CORE;
using namespace EVOLUTION::CORE::TIMER;

RESULT EVOLUTION::FUNCTION::CreateApplicationCounter(CORE::TIMER::IApplicationCounter** pp_application_counter){
    *pp_application_counter = nullptr;
    static struct _C{
        CORE::TIMER::ApplicationCounter* mp_application_counter;
        _C(){
            mp_application_counter = NEW CORE::TIMER::ApplicationCounter();
            mp_application_counter->Create();
        }
        ~_C(){
            EVOLUTION_RELEASE(mp_application_counter);
        }
    }_global_counter;
    return _global_counter.mp_application_counter->QueryInterface(EVOLUTION::EVOLUTION_GUID::IID_IApplicationCounter, (void**)pp_application_counter);
}

RESULT EVOLUTION::FUNCTION::CreateStopWatch(CORE::TIMER::IStopWatch** pp_stop_watch){
    *pp_stop_watch = nullptr;
    StopWatch* stop_watch = NEW StopWatch();
    if (EVOLUTION_FAILED(stop_watch->Create()))
    {
        EVOLUTION_RELEASE(stop_watch);
        return _RESULT::S_false;
    }
    *pp_stop_watch = stop_watch;
    return _RESULT::S_ok;
}

