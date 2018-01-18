#ifndef SAMPLE_ENTITY_H
#define SAMPLE_ENTITY_H
#include <jansson.h>
#include "resourcemanager.h"
#include "entity.h"
#include "sprite.h"
#define SAMPLE_NAME "Sample"

Entity new_Sample(json_t *args);
Sprite Sample_draw(Entity self);

#endif
