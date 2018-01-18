#include <math.h>
int distance(int x1, int y1, int x2, int y2)
{
    return (int)sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}
