#pragma once
// =================================================================================================
// includes

#undef WINVER
#define WINVER       0x0601
#undef _WIN32_WINNT
#define _WIN32_WINNT 0x0601

// windows headers
#ifdef _MSC_VER
#  define WIN32_LEAN_AND_MEAN
#  include <windows.h>
#  include <commdlg.h>
#  include <mmsystem.h>
#  include <guiddef.h>
#  include <shlobj.h>
#  include <direct.h>
#  include <dsound.h>
#  include <dbghelp.h>
#  include <wrl.h>
#  include <shlwapi.h>
#  include <sys/utime.h>
#endif

#ifdef _WIN64
#  define GWL_USERDATA GWLP_USERDATA
#endif

// c headers
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cassert>

// c++ headers
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <ctime>
#include <deque>
#include <fstream>
#include <iomanip>
#include <ostream>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <initializer_list>
#include <functional>
#include <thread>
#include <mutex>

// pybind11
#include <pybind11/pybind11.h>
#include <pybind11/embed.h>
#include <pybind11/stl.h>
namespace py = pybind11;

// =================================================================================================
// typedef
typedef char               s8;
typedef short              s16;
typedef long               s32;
typedef long long          s64;
typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned long      u32;
typedef unsigned long long u64;
typedef float              f32;
typedef double             f64;

using intpair = std::pair<s32, s32>;

template<class T>          using uptr  = std::unique_ptr<T>;

template<class T>          using uniquep  = std::unique_ptr<T>;
template<class T>          using sharedp  = std::shared_ptr<T>;
template<class T>          using weakp    = std::weak_ptr<T>;
template<class T, class U> using hashmap  = std::unordered_map<T, U>;
