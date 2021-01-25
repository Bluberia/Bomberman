/*
** EPITECH PROJECT, 2019
** Indie
** File description:
** Menu file
*/

#ifndef __MENU_HPP_
#define __MENU_HPP_

#include "IrrlichtDevice.hpp"
#include "Bomberman.hpp"
#include "SplashScreen.hpp"

class Menu {

public:
    enum MenuType {
            MAIN,
            LOAD,
    };

private:
    irr::IrrlichtDevice *_device;
    irr::video::IVideoDriver* _driver;
    irr::gui::IGUIEnvironment* _env;
    irr::video::ITexture* _images;
    bool _isRenderingParameters;
    bool _hasTwoPlayer;
    bool _isPlaying;
    irr::gui::IGUIButton *_startNewGameButton;
    irr::gui::IGUIButton *_loadMenuButton;
    irr::gui::IGUIButton *_quitButton;
    irr::gui::IGUIButton *_parametersButton;
    irr::gui::IGUIButton *_loadSaveAButton;
    irr::gui::IGUIButton *_loadSaveBButton;
    irr::gui::IGUIButton *_backButton;

public:
    Menu();
    ~Menu();
    void eventChecker();
    void render();
    void quit();
    void loadSaveScreen();
    bool getHasTwoPlayer();

private:
    SplashScreen splashScreen;
    Bomberman bomberman;
    void addMainMenuButtons();
    void addLoadMenuButtons();
    void loadAllTextures();
};

#else

class Menu;

#endif