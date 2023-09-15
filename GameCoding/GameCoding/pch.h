﻿#pragma once

#include "Types.h"
#include "Defines.h"
#include "Enums.h"
#include "Utils.h"
#include "Values.h"

#include <windows.h>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <string>
#include <algorithm>

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