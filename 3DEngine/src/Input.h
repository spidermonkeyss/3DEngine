#pragma once

class Input
{
public:
	enum KeyCode { Q,W,E,R,T,Y,U,I,O,P,A,S,D,F,G,H,J,K,L,Z,X,C,V,B,N,M,LAST };

	static bool GetKeyHeld(KeyCode keyCode);
	static bool GetKeyDown(KeyCode keyCode);
	static bool GetKeyUp(KeyCode keyCode);
private:
	enum KeyState { NONE, DOWN, HELD, RELEASED };
	static int keyStates[KeyCode::LAST + 1];

	static void ClearReleasedKeys();
	static void SetDownKeysToHeld();

	friend class Window;
	friend class Engine;
};