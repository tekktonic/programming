MEMORY {
    RAM: start = $0FFF, size=$0E01, define = yes;
}

SEGMENTS {
    CODE: load = RAM, type = rw;
    DATA: load = RAM, type = rw;    
}

SYMBOLS {
        __STACKSIZE__ = $400;
}
