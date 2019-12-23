#ifndef GAMEENGINE_H_INCLUDED
#define GAMEENGINE_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "../scene/GameIntro.h"

////////////////////////////////////////////////////////////
// PC version code
#if !defined(__ANDROID__)
#if !defined(LINUX_VERSION)
#include <direct.h>
#else
#include <sys/stat.h>
#endif // defined
#else
#if defined(ENABLE_ADMOB)
#include "../system/android/AdmobManager.h"
#endif
#endif // defined
////////////////////////////////////////////////////////////

namespace e_Enum
{
    enum e_Scene
    {
        INTRO
    };
}

class GameEngine
{
public:
    GameEngine();
    ~GameEngine();

    bool initEngine();
    bool play();

private:
    e_Enum::e_Scene* m_SceneName;
    bool m_launchAd;

    sf::RenderWindow m_Window;
    GameSystemExtended m_gameSysExt;

    GameIntro *m_gameIntroScreen;

    is::GameDisplay::DisplayOption m_launchOption;
};

#endif // GAMEENGINE_H_INCLUDED
