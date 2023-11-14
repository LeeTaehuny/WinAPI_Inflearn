#pragma once

#include "Types.h"
#include "Defines.h"
#include "Enums.h"
#include "Utils.h"
#include "Values.h"

#include <windows.h>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <functional>
#include <assert.h>

using namespace std;

// C++ 20
#include <format>
#include <filesystem>
namespace fs = std::filesystem;

// C++ 메모리 릭 체크
#define _CRTDEBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

// 만약 디버그 상태라면?
#ifdef _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

// TransparentBlt()를 사용하기 위한 라이브러리 추가
#pragma comment(lib, "msimg32.lib")

// 사운드
#include <mmsystem.h>
#include <dsound.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")