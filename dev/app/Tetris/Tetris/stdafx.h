// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <vector>
#include <string>

// TODO: reference additional headers your program requires here
#define FgColor RGB(255,153,204) //粉红
#define BgColor RGB(0xF5,0xF5,0xDC) //米色
#define BlackgColor RGB(0x0,0x0,0x0) //黑色


#define W 14 //游戏区域宽度
#define H 20 //游戏区域高度
#define W1 6 //右边状态栏宽度
#define BSIZE 25 //游戏方格边长
#define Y1 6 //放置照片的纵坐标
#define Y2 12 //分数显示栏顶端纵坐标
#define Y3 15 //等级显示栏顶端纵坐标
#define Y4 21 //帮助栏顶端纵坐标
#define Cur_x W/2-1 //游戏方块初始状态左上角横坐标
#define Cur_y 1 //初始状态左上角纵坐标