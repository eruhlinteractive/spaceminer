#include "../../../include/astrocore/systems/input/input.h"

using namespace Astrocore;

bool Input::IsActionJustPressed(std::string actionName)
{
    if(bindings.find(actionName) != bindings.end())
    {
        std::vector<InputAction> actions = bindings.at(actionName);
        for(InputAction action : actions)
        {
            switch (action.type)
            {
            case KEYBOARD:
                return IsKeyPressed(action.id);
            case MOUSE_BUTTON:
                return IsMouseButtonPressed(action.id);
            case JOY_BUTTON:
                return IsGamepadButtonPressed(action.deviceID, action.id);
            default:
                break;
            }
        }
    }
    return false;
}

bool Input::IsActionHeld(std::string actionName)
{
    if(bindings.find(actionName) != bindings.end())
    {
        std::vector<InputAction> actions = bindings.at(actionName);
        for(InputAction action : actions)
        {
            switch (action.type)
            {
            case KEYBOARD:
                return IsKeyDown(action.id);
            case MOUSE_BUTTON:
                return IsMouseButtonDown(action.id);
            case JOY_BUTTON:
                return IsGamepadButtonDown(action.deviceID, action.id);
            default:
                break;
            }
        }
    }
    return false;
}

bool Input::IsActionJustReleased(std::string actionName)
{
    if(bindings.find(actionName) != bindings.end())
    {
        std::vector<InputAction> actions = bindings.at(actionName);
        for(InputAction action : actions)
        {
            switch (action.type)
            {
            case KEYBOARD:
                return IsKeyReleased(action.id);
            case MOUSE_BUTTON:
                return IsMouseButtonReleased(action.id);
            case JOY_BUTTON:
                return IsGamepadButtonReleased(action.deviceID, action.id);
            default:
                break;
            }
        }
    }
    return false;
}

float Input::GetActionStrength(std::string actionName)
{
    if(bindings.find(actionName) != bindings.end())
    {
        std::vector<InputAction> actions = bindings.at(actionName);
        for(InputAction action : actions)
        {
            switch (action.type)
            {
            case JOY_AXIS:
                return GetGamepadAxisMovement(action.deviceID, action.id);
            }
        }
    }

    // Couldn't find a gamepad axis input. Just return if the button is down
    return IsActionHeld(actionName) ? 1.0f : 0.0f;
}

void Input::AddBinding(std::string name, InputAction newAction)
{
    if(bindings.find(name) == bindings.end())
    {
        bindings.emplace(name, std::vector<InputAction>());
    }
    bindings.at(name).push_back(newAction);
}

void Input::ClearBinding(std::string name)
{
    bindings.erase(name);
}

std::vector<InputAction> Input::GetAllActions(std::string bindingName)
{
    return bindings.at(bindingName);
}