#pragma once
#ifndef __DEFINE_H__
#define __DEFINE_H__

#define WINCX 600
#define WINCY 800

#define SAFE_DELETE(p) if(p) {delete p; p = nullptr;}

#define OBJ_NOEVENT		0
#define OBJ_DEAD		1

#endif