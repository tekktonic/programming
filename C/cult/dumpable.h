#ifndef DUMPABLE_H
#define DUMPABLE_H
struct dumpable {void (*dump)(struct dumpable *dump_self);};
#endif
