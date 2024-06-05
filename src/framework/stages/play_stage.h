#include "stage.h"

class PlayStage : public Stage{
public:
    using Stage::Stage;
    PlayStage();
    stage_ID getID();
    void render(Camera* camera);
    void renderMinimap();
    void update(float seconds_elapsed);   
};