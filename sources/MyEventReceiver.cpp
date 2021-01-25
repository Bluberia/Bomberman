#include "MyEventReceiver.hpp"
#include "IrrlichtDevice.hpp"

bool MyEventReceiver::OnEvent(const irr::SEvent &event) {
    if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
        KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
    }
    if (checkMenuEvents(event))
        return true;
    return false;
}

bool MyEventReceiver::IsKeyDown(irr::EKEY_CODE keyCode) const {
    return KeyIsDown[keyCode];
}

MyEventReceiver::MyEventReceiver() :
    KeyIsDown(), _isButtonClicked()
{
    for (bool &i : KeyIsDown) {
        i = false;
    }
    for (int i = 0; i < BUTTONSNUMBER; i++) {
        _isButtonClicked[i] = false;
    }
    _isButtonClicked[BUTTONSNUMBER] = NULL;
}

bool MyEventReceiver::checkMenuEvents(const irr::SEvent &event) {
    if (event.EventType == irr::EET_GUI_EVENT) {
        irr::s32 id = event.GUIEvent.Caller->getID();
        switch(event.GUIEvent.EventType) {
            case irr::gui::EGET_BUTTON_CLICKED:
                switch(id) {
                    case MyEventReceiver::GUI_ID_QUIT_BUTTON:
                        _isButtonClicked[0] = true;
                        return true;
                    case MyEventReceiver::GUI_ID_START_GAME:
                        _isButtonClicked[1] = true;
                        return true;
                    case MyEventReceiver::GUI_ID_LOAD_GAME:
                        _isButtonClicked[2] = true;
                        return true;
                    case MyEventReceiver::GUI_ID_PARAMETERS:
                        _isButtonClicked[3] = true;
                        return true;
                    case MyEventReceiver::GUI_ID_LOAD_SAVE_A:
                        _isButtonClicked[4] = true;
                        return true;
                    case MyEventReceiver::GUI_ID_LOAD_SAVE_B:
                        _isButtonClicked[5] = true;
                        return true;
                    case MyEventReceiver::GUI_ID_BACK:
                        _isButtonClicked[6] = true;
                        return true;
                    default:
                        return false;
                }
                break;
            default:
                break;
        }
    }
    return false;
}

bool MyEventReceiver::isButtonClicked(MyEventReceiver::GuiControls buttonType)
{
    if (buttonType >= 101 && buttonType <= (101 + BUTTONSNUMBER)) {
        if (_isButtonClicked[buttonType - 101]) {
            _isButtonClicked[buttonType - 101] = false;
            return true;
        }
    }
    return false;
}
