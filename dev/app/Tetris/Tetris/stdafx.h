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
#define FgColor RGB(255,153,204) //�ۺ�
#define BgColor RGB(0xF5,0xF5,0xDC) //��ɫ
#define BlackgColor RGB(0x0,0x0,0x0) //��ɫ


#define W 14 //��Ϸ������
#define H 20 //��Ϸ����߶�
#define W1 6 //�ұ�״̬�����
#define BSIZE 25 //��Ϸ����߳�
#define Y1 6 //������Ƭ��������
#define Y2 12 //������ʾ������������
#define Y3 15 //�ȼ���ʾ������������
#define Y4 21 //����������������
#define Cur_x W/2-1 //��Ϸ�����ʼ״̬���ϽǺ�����
#define Cur_y 1 //��ʼ״̬���Ͻ�������