#ifndef DSH_UTIL_H
#define DSH_UTIL_H
#define DUMMY_PATH "/bin:/usr/bin:/usr/local/bin"

#include <string.h>




Path SplitPath(void); // get the $PATH, create a Path
const char *GetExe(const char *name); // get the name of an executable from the path
    
