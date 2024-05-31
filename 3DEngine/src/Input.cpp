#include "Input.h"

int Input::keyStates[KeyCode::LAST + 1] = { Input::KeyState::NONE };

bool Input::GetKeyHeld(KeyCode keyCode)
{
    return keyStates[keyCode] == KeyState::HELD;
}

bool Input::GetKeyDown(KeyCode keyCode)
{
    return keyStates[keyCode] == KeyState::DOWN;
}

bool Input::GetKeyUp(KeyCode keyCode)
{
    return keyStates[keyCode] == KeyState::RELEASED;
}

void Input::ClearReleasedKeys()
{
    for (int i = 0 ; i < KeyCode::LAST + 1; i++)
    {
        if (keyStates[i] == KeyState::RELEASED)
            keyStates[i] = KeyState::NONE;
    }
}

void Input::SetDownKeysToHeld()
{
    for (int i = 0; i < KeyCode::LAST + 1; i++)
    {
        if (keyStates[i] == KeyState::DOWN)
            keyStates[i] = KeyState::HELD;
    }
}
