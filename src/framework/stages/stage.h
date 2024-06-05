#include "framework/camera.h"
#include "framework/framework.h"
#include "framework/utils.h"
#include "game/game.h"
#include "entities/entity.h"


enum stage_ID {
    INTRO,
    MENU,
    PLAY,
    sEND
};

class Stage {
public:
    bool isEnd;
    Stage();
    void render(Camera* camera);
    virtual void update(float seconds_elapsed){};
};