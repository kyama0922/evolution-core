#include "../evolution_core.h"
#include "evolution_file.h"
#include <Windows.h>


using namespace EVOLUTION;
using namespace EVOLUTION::CORE;
using namespace EVOLUTION::CORE::FILE;

std::string File::GetExtension(const char* file_name){
	for (u32 i = strlen(file_name); i != 0; i--)
	{
		if (file_name[i] == '.'){
			return &file_name[i];
		}
	}
	return file_name;
}
std::wstring File::GetExtension(const wchar_t* file_name){
	for (s32 i = lstrlenW(file_name); i != 0; i--)
	{
		if (file_name[i] == L'.'){
			return &file_name[i];
		}
	}
	return file_name;
}

std::string File::GetFilePath(const char* file_name){
	char workpath[1024];
	memcpy(workpath, file_name, strlen(file_name) + 1);
	for (s32 i = strlen(file_name); i>0; i--){
		if (IsDBCSLeadByte(workpath[i - 2])){
			continue;
		}
		if (workpath[i - 1] == '\\' || workpath[i - 1] == '/'){
			workpath[i] = '\0';
			break;
		}
	}
	return workpath;
}

std::wstring File::GetFilePath(const wchar_t* file_name){
	wchar_t workpath[1024];
	memcpy(workpath, file_name, lstrlenW(file_name) + 1);
	for (s32 i = lstrlenW(file_name); i>0; i--){
		if (workpath[i - 1] == '\\' || workpath[i - 1] == '/'){
			workpath[i] = '\0';
			break;
		}
	}
	return workpath;
}

bool File::Delete(const wchar_t* file_name){
	return DeleteFileW(file_name) == TRUE;
}
bool File::Delete(const char* file_name){
	return DeleteFileA(file_name) == TRUE;
}

bool File::Delete(const char* directory_name, const char* file_name){
	std::string str;
	str.reserve(strlen(directory_name) + strlen(file_name) + 1);
	str += directory_name;
	s32 len = strlen(directory_name);
	if (strcmp(&directory_name[len - 1], "\\")  && strcmp(&directory_name[len - 1], "/") ){
		str += "\\";
	}
	str += file_name;
	return DeleteFileA(str.c_str()) == TRUE;
}
bool File::Delete(const wchar_t* directory_name, const wchar_t* file_name){
	std::wstring str;
	str.reserve(lstrlenW(directory_name) + lstrlenW(file_name) + 1);
	str += directory_name;
	s32 len = lstrlenW(directory_name);
	if (lstrcmpW(&directory_name[len - 1], L"\\")  && lstrcmpW(&directory_name[len - 1], L"/") ){
		str += L"\\";
	}
	str += file_name;
	return DeleteFileW(str.c_str()) == TRUE;
}

bool File::IsCheck(const char* file_name){
    EVOLUTION_ASSERT(file_name);
	DWORD flg = GetFileAttributesA(file_name);
    return flg != MAILSLOT_NO_MESSAGE && EVOLUTION_IS_STATE(flg, FILE_ATTRIBUTE_ARCHIVE);
}

bool File::IsCheck(const wchar_t* file_name){
    EVOLUTION_ASSERT(file_name);
	DWORD flg = GetFileAttributesW(file_name);
    return flg != MAILSLOT_NO_MESSAGE && EVOLUTION_IS_STATE(flg, FILE_ATTRIBUTE_ARCHIVE);
}


bool File::IsCheck(const char* directory_name, const char* file_name){
	std::string str;
	str.reserve(strlen(directory_name) + strlen(file_name) + 1);
	str += directory_name;
	s32 len = strlen(directory_name);
	if (strcmp(&directory_name[len - 1], "\\")  && strcmp(&directory_name[len - 1], "/") ){
		str += "\\";
	}
	str += file_name;
    EVOLUTION_ASSERT(str.c_str());
	DWORD flg = GetFileAttributesA(str.c_str());
    return flg != MAILSLOT_NO_MESSAGE && EVOLUTION_IS_STATE(flg, FILE_ATTRIBUTE_ARCHIVE);
}
bool File::IsCheck(const wchar_t* directory_name, const wchar_t* file_name){
	std::wstring str;
	str.reserve(lstrlenW(directory_name) + lstrlenW(file_name) + 1);
	str += directory_name;
	s32 len = lstrlenW(directory_name);
	if (lstrcmpW(&directory_name[len - 1], L"\\") && lstrcmpW(&directory_name[len - 1], L"/") ){
		str += L"\\";
	}
	str += file_name;
    EVOLUTION_ASSERT(str.c_str());
	DWORD flg = GetFileAttributesW(str.c_str());
    return flg != MAILSLOT_NO_MESSAGE && EVOLUTION_IS_STATE(flg, FILE_ATTRIBUTE_ARCHIVE);
}