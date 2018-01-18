#include "component.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

typedef struct ComponentNode {
    Component c;
    char *key;
    struct ComponentNode *next;
} ComponentNode;

#define BUCKET_SIZE 32

typedef struct ComponentHash {
    ComponentNode components[BUCKET_SIZE];
}ComponentHash;

static uint32_t hash(const char *string, uint32_t modvalue) {
    uint32_t star_prime = 3313;
    uint32_t h = 0;

    uint32_t len = strlen(string);

    for (int i = 0; string[i]; i++) {
        h += string[i] * (uint32_t)pow(star_prime, len - i);
    }

    return h % modvalue;
}

void ch_delete(ComponentHash *h, char *string) {
    uint32_t offset = hash(string, BUCKET_SIZE);

    ComponentNode *cur = &(h->components[offset]), *tail = NULL;

    while (cur) {
        if (cur->key && !strcmp(cur->key, string)) {
            if (tail) {
                tail->next = cur->next;
            }
            else {
                h->components[offset] = *cur->next;
                free(cur->next);
            }
            break;
        }
        tail = cur;
        cur = cur->next;
    }

    if (cur) {
        cur->c.cleanup(&(cur->c));
        free(cur->key);
        free(cur);
    }
}

Component *ch_get(ComponentHash *h, char *string) {
    uint32_t offset = hash(string, BUCKET_SIZE);
    ComponentNode *cur = &(h->components[offset]);
    while (cur) {
        if (cur->key && !strcmp(cur->key, string))
            return &cur->c;
        cur = cur->next;
    }

    return NULL;
}

void ch_insert(ComponentHash *h, const char *key, Component c) {
    uint32_t offset = hash(key, BUCKET_SIZE);

    ComponentNode *cur = h->components[offset].next, *tail = &(h->components[offset]);
    while (cur) {
        tail = cur;
        cur = cur->next;
    }

    tail->next = malloc(sizeof(ComponentNode));
    cur = tail->next;
    int keylen = strlen(key) + 1;
    cur->key = malloc(keylen);
    snprintf(cur->key, keylen, "%s", key);
    cur->c = c;
    cur->next = NULL;
}

void ch_iter(ComponentHash *h, ch_iterator i, void *data) {
    for (int c = 0; c < BUCKET_SIZE; c++) {
        ComponentNode *cur = h->components[c].next;
        while (cur) {
            i(&cur->c, data);
            cur = cur->next;
        }
    }
}

struct ComponentHash *new_component_hash(void) {
    ComponentHash *ret = malloc(sizeof(ComponentHash));
    // Could also memcpy
    for (int i = 0; i < BUCKET_SIZE; i++) {
        ret->components[i] = (ComponentNode){.key=0};
    }

    return ret;
}

bool c_send(Component *c, Event d) {
    if (c->receive) {
        c->receive(c, d);
        return true;
    }
    return false;
}
