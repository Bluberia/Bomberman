/*
** EPITECH PROJECT, 2019
** Indie
** File description:
** Event Receiver
*/

#ifdef _WIN32
    #include <irrlicht.h>
    #include <driverChoice.h>
#else
    #include <irrlicht/irrlicht.h>
    #include <irrlicht/driverChoice.h>

#endif

#ifndef _MYEVENTRECEIVER_HPP_
#define _MYEVENTRECEIVER_HPP_

#define BUTTONSNUMBER 7

class MyEventReceiver : public irr::IEventReceiver {
public:

    typedef enum {
        GUI_ID_QUIT_BUTTON = 101,
        GUI_ID_START_GAME,
        GUI_ID_LOAD_GAME,
        GUI_ID_PARAMETERS,
        GUI_ID_LOAD_SAVE_A,
        GUI_ID_LOAD_SAVE_B,
        GUI_ID_BACK
    } GuiControls;

    MyEventReceiver();

    bool OnEvent(const irr::SEvent &event) override;
    virtual bool IsKeyDown(irr::EKEY_CODE keyCode) const;
    bool checkMenuEvents(const irr::SEvent &event);
    bool isButtonClicked(GuiControls buttonType);

private:
    bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];
    bool _isButtonClicked[BUTTONSNUMBER];
};

#else

class MyEventReceiver;

#endif