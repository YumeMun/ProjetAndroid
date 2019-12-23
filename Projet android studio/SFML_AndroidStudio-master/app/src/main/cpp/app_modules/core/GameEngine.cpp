#include "GameEngine.h"

GameEngine::GameEngine()
{
    m_launchAd = false;
    m_launchOption = is::GameDisplay::DisplayOption::INTRO;
    m_gameIntroScreen = 0;
}

GameEngine::~GameEngine()
{
   // is::instanceDestroy(m_gameIntroScreen);
    #if defined(__ANDROID__)
    /// uncomment to active lock screen on Android
    // is::setScreenLock(false);
    #endif // defined
}

bool GameEngine::initEngine()
{
    m_gameSysExt.initSystemData();
    m_gameSysExt.initProgress();

    ////////////////////////////////////////////////////////////
    // code for PC / Android version
    #if defined(__ANDROID__)
    m_Window.create(sf::VideoMode::getDesktopMode(), "");
    /// uncomment to disable lock screen on Android
    // is::setScreenLock(true);
    #else
    m_app.create(sf::VideoMode(640, 480), "is::engine Demo", sf::Style::Close);

    // load application icon
    sf::Image iconTex;
    if (!iconTex.loadFromFile(is::GUI_DIR + "icon.png")) return false;
    m_app.setIcon(32, 32, iconTex.getPixelsPtr());

    // create saving directory
    if (!m_gameSysExt.fileExist(is::CONFIG_FILE))
    {
        #if !defined(LINUX_VERSION)
        mkdir("save");
        #else
        mkdir("save", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        #endif
        m_gameSysExt.saveConfig(is::CONFIG_FILE);
    }
    #endif // defined
    ////////////////////////////////////////////////////////////

    m_Window.setFramerateLimit(60);
    return true;
}

bool GameEngine::play()
{
//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                      GAME INTILISATION
//////////////////////////////////////////////////////////////////////////////////////////////////////
    if (!initEngine()) return false;

    #if defined(__ANDROID__)
    #if defined(ENABLE_ADMOB)
    ANativeActivity* activity = sf::getNativeActivity();
    JNIEnv* env = activity->env;
    JavaVM* vm = activity->vm;
    vm->AttachCurrentThread(&env, NULL);

    AdmobManager *admobManager = 0;
    admobManager = new AdmobManager(m_app, activity, env, vm);
    admobManager->checkAdObjInit();
    #endif // defined
    #endif // defined

//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                         GAME STAR-TUP
//////////////////////////////////////////////////////////////////////////////////////////////////////
    while (m_Window.isOpen())
    {
        switch (m_launchOption)
        {
            case is::GameDisplay::INTRO : // intro
                m_gameIntroScreen = new GameIntro(m_Window, m_launchOption, m_gameSysExt);
                if (!m_gameIntroScreen->loadResources()) return false;
                while (m_gameIntroScreen->isRunning())
                {
                    m_gameIntroScreen->step();
                    m_gameIntroScreen->drawScreen();
                }
                #if defined(__ANDROID__)
                #if defined(ENABLE_ADMOB)
                admobManager->loadBannerAd();
                admobManager->loadInterstitialAd();
                #endif // defined
                #endif // defined
                delete m_gameIntroScreen;
                m_gameIntroScreen = 0;
            break;
        }
    }

    #if defined(__ANDROID__)
    #if defined(ENABLE_ADMOB)
    if (is::instanceExist(admobManager))
    {
        delete admobManager;
        admobManager = 0;
    }
    #endif // defined
    #endif // defined
    return true;
}