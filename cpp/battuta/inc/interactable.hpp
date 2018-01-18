#ifndef INTERACTABLE_H
#define INTERACTABLE_H

#include "image.hpp"

class Interactable
{
public:
    virtual void interact(Interactable &other);
    virtual Image& image();
    virtual ~Interactable();

};
#endif
