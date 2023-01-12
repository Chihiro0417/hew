//コントローラーcpp追加

#include "Controller.h"

XINPUT_STATE g_PadState;
DWORD g_NowState;
DWORD g_OldState;

bool STUPTrigger;
bool STDOWNTrigger;
bool STLEFTTrigger;
bool STRIGHTTrigger;

void InitController()
{
	XInputGetState(0, &g_PadState);
	g_NowState = 0;
	g_OldState = 0;
	STUPTrigger = false;
	STDOWNTrigger = false;
	STLEFTTrigger = false;
	STRIGHTTrigger = false;
}

void UninitController()
{
}

void UpdateController()
{
	g_OldState = g_NowState;
	XInputGetState(0, &g_PadState);
	g_NowState = g_PadState.Gamepad.wButtons;

	if (g_PadState.Gamepad.sThumbLY <= GAMEPAD_UP_THUMB_DEADZONE && STUPTrigger == true)
	{
		STUPTrigger = false;
	}
	if (g_PadState.Gamepad.sThumbLY >= GAMEPAD_DOWN_THUMB_DEADZONE && STDOWNTrigger == true)
	{
		STDOWNTrigger = false;
	}
	if (g_PadState.Gamepad.sThumbLX >= GAMEPAD_LEFT_THUMB_DEADZONE && STLEFTTrigger == true)
	{
		STLEFTTrigger = false;
	}
	if (g_PadState.Gamepad.sThumbLX <= GAMEPAD_RIGHT_THUMB_DEADZONE && STRIGHTTrigger == true)
	{
		STRIGHTTrigger = false;
	}

	if (g_PadState.Gamepad.sThumbRY <= GAMEPAD_UP_THUMB_DEADZONE && STUPTrigger == true)
	{
		STUPTrigger = false;
	}
	if (g_PadState.Gamepad.sThumbRY >= GAMEPAD_DOWN_THUMB_DEADZONE && STDOWNTrigger == true)
	{
		STDOWNTrigger = false;
	}
	if (g_PadState.Gamepad.sThumbRX >= GAMEPAD_LEFT_THUMB_DEADZONE && STLEFTTrigger == true)
	{
		STLEFTTrigger = false;
	}
	if (g_PadState.Gamepad.sThumbRX <= GAMEPAD_RIGHT_THUMB_DEADZONE && STRIGHTTrigger == true)
	{
		STRIGHTTrigger = false;
	}
}

 bool GetLStickUP()
{
	if (g_PadState.Gamepad.sThumbLY >= GAMEPAD_UP_THUMB_DEADZONE)
	{
		return true;
	}
	return false;
}

 bool GetLStickUPTrigger()
 {
	 if (g_PadState.Gamepad.sThumbLY >= GAMEPAD_UP_THUMB_DEADZONE && STUPTrigger == false)
	 {
		 STUPTrigger = true;
		 return true;
	 }
	 return false;
 }

bool GetLStickDOWN()
{
	if (g_PadState.Gamepad.sThumbLY <= GAMEPAD_DOWN_THUMB_DEADZONE)
	{
		return true;
	}
	return false;
}

bool GetLStickDOWNTrigger()
{
	if (g_PadState.Gamepad.sThumbLY <= GAMEPAD_DOWN_THUMB_DEADZONE && STDOWNTrigger == false)
	{
		STDOWNTrigger = true;
		return true;
	}
	return false;
}

bool GetLStickLEFT()
{
	if (g_PadState.Gamepad.sThumbLX <= GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		return true;
	}
	return false;
}

bool GetLStickLEFTTrigger()
{
	if (g_PadState.Gamepad.sThumbLX <= GAMEPAD_LEFT_THUMB_DEADZONE && STLEFTTrigger == false)
	{
		STLEFTTrigger = true;
		return true;
	}
	return false;
}

bool GetLStickRIGHT()
{
	if (g_PadState.Gamepad.sThumbLX >= GAMEPAD_RIGHT_THUMB_DEADZONE)
	{
		return true;
	}
	return false;
}

bool GetLStickRIGHTTrigger()
{
	if (g_PadState.Gamepad.sThumbLX >= GAMEPAD_RIGHT_THUMB_DEADZONE && STRIGHTTrigger == false)
	{
		STRIGHTTrigger = true;
		return true;
	}
	return false;
}

bool GetControllerPress(int Button)
{
	if (g_PadState.Gamepad.wButtons == Button)
	{
		return true;
	}
	return false;
}

bool GetControllerTrigger(int Button)
{
	if (!(g_NowState == g_OldState) && g_PadState.Gamepad.wButtons == Button)
	{
		return true;
	}
	return false;
}

bool GetRStickUP()
{
	if (g_PadState.Gamepad.sThumbRY >= GAMEPAD_UP_THUMB_DEADZONE)
	{
		return true;
	}
	return false;
}

bool GetRStickDOWN()
{
	if (g_PadState.Gamepad.sThumbRY <= GAMEPAD_DOWN_THUMB_DEADZONE)
	{
		return true;
	}
	return false;
}

bool GetRStickLEFT()
{
	if (g_PadState.Gamepad.sThumbRX <= GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		return true;
	}
	return false;
}

bool GetRStickRIGHT()
{
	if (g_PadState.Gamepad.sThumbRX >= GAMEPAD_RIGHT_THUMB_DEADZONE)
	{
		return true;
	}
	return false;
}