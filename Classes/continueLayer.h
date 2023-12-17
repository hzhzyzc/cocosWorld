#if defined(_MSC_VER) && (_MSC_VER >= 1900)
#pragma execution_character_set("utf-8")
#endif
#include"cocos2d.h"
#include"ui/CocosGUI.h"
#include "AudioEngine.h"
USING_NS_CC; 
class continueLayer : public Layer {
public:
    CREATE_FUNC(continueLayer);
    virtual bool init();
    bool onTouchBegan(Touch* touch, Event* event);
    void showLayer();
    bool getStatus();
private:
    bool status;
};
