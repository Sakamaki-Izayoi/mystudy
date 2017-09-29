#pragma once
#include "stdafx.h"
#include "../hookengine/inlinehook.h"
namespace usr
{
	namespace ldr
	{
		void install_ldr_patch();
		void uninstall_ldr_patch();
		BOOL LdrLoadMemDll(PVOID DllMem, SIZE_T dllSize, LPCWSTR szDllName, HMODULE *pModule);
		class ldr_patch
		{
		public:
			ldr_patch() {
				//patch��ʼ��
				//������Ҫһ��hook���棬���ú�����Ӱ�Ķ���
				//��������hook�½ڻᵥ���һ�������Լ��õ�hookengine���ǳ��Ƚ���

				install_ldr_patch();
			};
			~ldr_patch() {
				uninstall_ldr_patch();
			};
			HMODULE mem_load(std::vector<BYTE> image, std::wstring &dll_name=std::wstring(L"")) {
				//�Ȱ�ȱ��dllloadһ��
				{
					using namespace LIEF::PE;
					std::unique_ptr<Binary> bin{ Parser::parse(image) };
					if (bin->has_imports())
					{
						for (const Import& import : bin->imports()) {
							auto dll = import.name();
							LoadLibraryA(dll.c_str());
						}
					}
				}
				wchar_t szDllName[MAX_PATH] = {};
				StringCbPrintfW(szDllName,
					sizeof(szDllName),
					L"C:\\%d-%x.dll", image.size(), usr::util::crc32(image.data(),image.size()));
				HMODULE pOut = nullptr;
				if (LdrLoadMemDll(image.data(), image.size(), szDllName, &pOut))
				{
					dll_name = std::wstring(szDllName);
					return pOut;
				}
				return nullptr;
			};
			HMODULE mem_load(PVOID _data, std::size_t _size, std::wstring &dll_name = std::wstring(L""))
			{
				std::vector<BYTE> code;
				code.resize(_size);
				std::memcpy(&code[0], _data, _size);

				return mem_load(code,dll_name);
			}
			
		private:
			
		};
	}
}