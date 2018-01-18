#include <stdio.h>
#include <stdlib.h>

#include <gtk-2.0/gtk/gtk.h>

int gettemp(void)
{
    int temp;
    FILE *thermal = fopen("/sys/devices/virtual/thermal/thermal_zone0/temp", "r");
    fscanf(thermal, "%d", &temp);

    fclose(thermal);

    return temp / 1000;
}


int main(void)
{
    GtkStatusIcon *icon = gtk_status_icon_new();

    
    printf("%d\n", gettemp());

    return 0;
}
