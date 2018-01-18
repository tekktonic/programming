#ifndef T_LIST_H
#define T_LIST_H
struct t_list {
    void *cur;
    struct t_list *last;
    struct t_list *next;
};

t_list t_list_new(void *first, ...);
void t_list_enqueue(tlist *list, void *item);
void t_list_push(tlist *first, void *item);

void *t_list_pop(tlist *list);
void *t_list_dequeue(tlist *list);

#endif
