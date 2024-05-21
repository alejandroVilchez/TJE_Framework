#include "entity.h"
#include "entity_mesh.h"

class EntityPlayer : public EntityMesh {
public:
    EntityPlayer();
    ~EntityPlayer();
    void update(float seconds_elapsed) override;
};