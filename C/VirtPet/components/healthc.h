#ifndef HEALTHC_H
#define HEALTHC_H
#include "../component.h"

typedef enum {
    HEALTHC_HEAL,
    HEALTHC_HARM
}HealthCEvents;

typedef enum {
    HEALTHC_HEALTH
} HealthCInspects;

Component new_healthc(int health);
#endif
