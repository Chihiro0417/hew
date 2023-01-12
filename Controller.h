#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include <Windows.h>
#include <Xinput.h>
#pragma comment (lib, "xinput.lib")

#define GAMEPAD_UP_THUMB_DEADZONE	 ( 20000)
#define GAMEPAD_DOWN_THUMB_DEADZONE  (-20000)
#define GAMEPAD_LEFT_THUMB_DEADZONE  (-20000)
#define GAMEPAD_RIGHT_THUMB_DEADZONE ( 20000)



void InitController();
void UninitController();
void UpdateController();

bool GetLStickUP();
bool GetLStickUPTrigger();
bool GetLStickDOWN();
bool GetLStickDOWNTrigger();
bool GetLStickLEFT();
bool GetLStickLEFTTrigger();
bool GetLStickRIGHT();
bool GetLStickRIGHTTrigger();

bool GetRStickUP();
bool GetRStickDOWN();
bool GetRStickLEFT();
bool GetRStickRIGHT();


bool GetControllerPress(int Button);
bool GetControllerTrigger(int Button);




#endif // !__CONTROLLER_H__


