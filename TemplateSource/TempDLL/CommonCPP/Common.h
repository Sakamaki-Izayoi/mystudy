#pragma once
//����ͷ
#include <tchar.h>

//STLͷ
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <set>
#include <map>
#include <bitset>
#include <stack>
#include <queue>
#include <array>
#include <tuple>

//STDͷ
#include <algorithm>
#include <functional>
#include <type_traits>
#include <utility>
#include <cmath>
#include <cstdint>
#include <atomic>

//ϵͳͷ
#include <thread>
#include <chrono>
#include <mutex>
#include <random>
#include <memory>
#include <filesystem>

//Windowsͷ
#include <windows.h>
#include <assert.h>
#include <tlhelp32.h>
#include <Psapi.h>
#include <Shlwapi.h>
#include <winioctl.h>
#include <strsafe.h>
#include <intrin.h>
#include <intsafe.h>
#include <Sfc.h>
#include <winsvc.h>



//WDKʹ�õ�ͷ,namespace����г
namespace wdk::flt
{
#include <fltUser.h>
};

//lib��
#pragma comment(lib,"psapi.lib")
#pragma comment(lib,"shlwapi.lib")
#pragma comment(lib,"iphlpapi.lib")
#pragma comment(lib,"Wbemuuid.lib")
#pragma comment(lib,"Mpr.lib")
#pragma comment(lib,"ntdll.lib")
#pragma comment(lib,"FltLib.lib")
#pragma comment(lib,"Sfc.lib")

//N4189��ͷ
#include "scope_exit.h"
#include "unique_resource.h"
//���ģʽ��ͷ
#include "SingleTon.h"

//NTDLL��ͷ
namespace ntdll
{
//NTAPIͷ
#include "NativeLib.h"
//Workstation��ͷ
#include "WinStationLib.h"
};