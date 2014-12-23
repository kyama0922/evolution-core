#include "../etc/evolution_assert.h"
#include "evolution_directory.h"
#include "evolution_file.h"

#include <iostream>
#include <string>
#include <vector>

#include <Windows.h>

using namespace EVOLUTION;
using namespace EVOLUTION::CORE;
using namespace EVOLUTION::CORE::FILE;

bool Directory::Delete(const char* directory_name){
	auto file_list = Directory::GetFileList(directory_name);
	for (auto item : file_list)
	{
		if (File::IsCheck(directory_name, item.c_str())){
			bool flg = File::Delete(directory_name, item.c_str());
			flg = true;
		}
		else{
			std::string dir;
			dir.reserve(strlen(directory_name) + item.size());
			dir += directory_name;
			s32 len = strlen(directory_name);
			if (strcmp(&directory_name[len - 1], "\\") && strcmp(&directory_name[len - 1], "/") ){
				dir += "\\";
			}
			dir += item;
			Directory::Delete(dir.c_str());
		}
	}
	return RemoveDirectoryA(directory_name) == TRUE;
}
bool Directory::Delete(const wchar_t* directory_name){
	auto file_list = Directory::GetFileList(directory_name);
	for (auto item : file_list)
	{
		if (File::IsCheck(directory_name, item.c_str())){
			File::Delete(directory_name, item.c_str());
		}
		else{
			std::wstring dir;
			dir.reserve(lstrlenW(directory_name) + item.size() + 1);
			dir += directory_name;
			s32 len = lstrlenW(directory_name);
			if (lstrcmpW(&directory_name[len - 1], L"\\")  && lstrcmpW(&directory_name[len - 1], L"/") ){
				dir += L"\\";
			}
			dir += item;
			Directory::Delete(dir.c_str());
		}
	}
	return RemoveDirectoryW(directory_name) == TRUE;
}

bool Directory::Create(const char* directory_name){
	if (Directory::IsCheck(directory_name)){
		return true;
	}
	u32 len = strlen(directory_name) -1;
	for (len; len > 0; len--)
	{
		if (IsDBCSLeadByte(directory_name[len])){
			continue;
		}
		if (directory_name[len - 1] == '\\' || directory_name[len - 1] == '/'){
			break;
		}
	}
	if (len != 0){
		char* d_name = new char[len + 1];
		memcpy(d_name, directory_name, len);
		d_name[len] = 0;
		Directory::Create(d_name);
		delete d_name;
	}
	return CreateDirectoryA(directory_name, nullptr) == TRUE;
}

bool Directory::Create(const wchar_t* directory_name){
	if (Directory::IsCheck(directory_name)){
		return true;
	}
	return CreateDirectoryW(directory_name, nullptr) == TRUE;
}

bool Directory::IsCheck(const char* directory_name){
	 EVOLUTION_ASSERT(directory_name);
	DWORD flg = GetFileAttributesA(directory_name);
    return flg != MAILSLOT_NO_MESSAGE && EVOLUTION_IS_STATE(flg, FILE_ATTRIBUTE_DIRECTORY);
}

bool Directory::IsCheck(const wchar_t* directory_name){
    EVOLUTION_ASSERT(directory_name);
	DWORD flg = GetFileAttributesW(directory_name);
    return flg != MAILSLOT_NO_MESSAGE && EVOLUTION_IS_STATE(flg, FILE_ATTRIBUTE_DIRECTORY);
}

bool Directory::SetDirectory(const char* directory_name){
	return SetCurrentDirectoryA(directory_name) == TRUE;
}

bool Directory::SetDirectory(const wchar_t* directory_name){
	return SetCurrentDirectoryW(directory_name) == TRUE;
}

std::string Directory::GetDirectory(){
	char dir[MAX_PATH];
	GetCurrentDirectoryA(MAX_PATH, dir);
	return dir;
}

std::vector<std::string> Directory::GetFileList(const char* directory_name){
	std::vector<std::string> tmp_data;
	WIN32_FIND_DATAA findfiledata;

	if (!Directory::IsCheck(directory_name)){
		return std::vector<std::string>();
	}
	std::string directory_work = directory_name;
	s32 len = strlen(directory_name);
	if (strcmp(&directory_name[len - 1], "\\") && strcmp(&directory_name[len - 1], "/") ){
		directory_work += "\\*.*";
	}
	else{
		directory_work += "*.*";
	}
	
	
	HANDLE handle = FindFirstFileA(directory_work.c_str(), &findfiledata);
	if (handle == INVALID_HANDLE_VALUE){
		return std::vector<std::string>();
	}

	do{
		if (strcmp(findfiledata.cFileName, "..") == 0 || strcmp(findfiledata.cFileName, ".")==0){
			continue;
		}
		tmp_data.push_back(findfiledata.cFileName);
	} while (FindNextFileA(handle, &findfiledata));
	FindClose(handle);
	return tmp_data;
}

std::vector<std::wstring> Directory::GetFileList(const wchar_t* directory_name){
	std::vector<std::wstring> tmp_data;
	WIN32_FIND_DATAW findfiledata;

	if (!Directory::IsCheck(directory_name)){
		return std::vector<std::wstring>();
	}
	std::wstring directory_work = directory_name;
	s32 len = lstrlenW(directory_name);
	if (lstrcmpW(&directory_name[len - 1], L"\\") && lstrcmpW(&directory_name[len - 1], L"/")){
		directory_work += L"\\*.*";
	}
	else{
		directory_work += L"*.*";
	}

	HANDLE handle = FindFirstFileW(directory_work.c_str(), &findfiledata);
	if (handle == INVALID_HANDLE_VALUE){
		return std::vector<std::wstring>();
	}

	do{
		if (lstrcmpW(findfiledata.cFileName, L"..") == 0 || lstrcmpW(findfiledata.cFileName, L".") == 0){
			continue;
		}
		tmp_data.push_back(findfiledata.cFileName);
	} while (FindNextFileW(handle, &findfiledata));
	FindClose(handle);
	return tmp_data;
}