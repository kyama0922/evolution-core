#ifndef __EVOLUTION_CORE_H__
#define __EVOLUTION_CORE_H__

//----------------------------------------------------
//テンプレート関係
//----------------------------------------------------
#include "template/evolution_template.h"

//----------------------------------------------------
//非同期関係
//----------------------------------------------------
#include "thread/evolution_thread.h"

//----------------------------------------------------
//メモリ関係
//----------------------------------------------------
#include "memory/evolution_memory_interface.h"

//----------------------------------------------------
//ファイル関係
//----------------------------------------------------
#include "file\evolution_file_interface.h"

#include "file\evolution_file.h"

#include "file\evolution_directory.h"
//----------------------------------------------------
//ETC
//----------------------------------------------------
//アサーション
#include "etc/evolution_assert.h"

//Debug
#include "etc/evolution_debug.h"

//ハッシュ化クラス
#include "etc/evolution_crypto.h"

//関数
#include "function/evolution_function.h"

//時間関係のクラス
#include "time\evolution_timer_interface.h"
#endif //!__EVOLUTION_CORE_H__