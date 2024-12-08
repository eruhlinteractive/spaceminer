#ifndef INPUT_H
#define INPUT_H

#include <raylib.h>
#include <map>
#include <string>
#include <vector>


namespace Astrocore
{
    // Types of input
    enum INPUT_TYPE {KEYBOARD, MOUSE_BUTTON, JOY_BUTTON, JOY_AXIS};

    struct InputAction
    {
        InputAction(INPUT_TYPE type, int id)
        {
            this->type = type;
            this->id = id;
        }
        InputAction(INPUT_TYPE type, int id, int deviceID)
        {
            this->type = type;
            this->id = id;
            this->deviceID = deviceID;
        }
        INPUT_TYPE type;
        int id;
        int deviceID = 0; // Only used for joypad inpus
    };
    
    class Input
    {
        private:
            static inline std::map<std::string, std::vector<InputAction>> bindings = std::map<std::string, std::vector<InputAction>>();

        public:
            static bool IsActionHeld(std::string actionName);
            static bool IsActionJustReleased(std::string actionName);
            static bool IsActionJustPressed(std::string actionName);

            static float GetActionStrength(std::string actionName);

            // Adds a new binding, or a new action if a binding already exists
            static void AddBinding(std::string name, InputAction newAction);
            static void RemoveBinding(std::string name, InputAction newAction);
            static void ClearBinding(std::string name);
            static std::vector<InputAction> GetAllActions(std::string bindingName);

            // TODO: Add ability to load from external file
    };
}

#endif