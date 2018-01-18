#ifndef HEALTHC_H
#define HEALTHC_H
#include "../component.h"

typedef enum {
    HEAL,
    HARM
}HealthCEvents;

Component new_healthc(int health);
#endif
