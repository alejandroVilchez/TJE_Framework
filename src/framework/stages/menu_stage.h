#include "stage.h"

class MenuStage : public Stage{
public:
    using Stage::Stage;
    MenuStage();
    stage_ID getID();
    void render(Camera* camera);
    void update(float seconds_elapsed);
};