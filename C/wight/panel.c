#include <X11/Xlib.h>
#include <X11/Xaw3d/XawInit.h>
#include <X11/Xaw3d/Label.h>
struct program {
	char *prgnam;
	char **args;
};

void launch(struct program p)
{
	printf("I'm running!\n\n");
	execvp(p.prgnam, p.args);
	printf("%s\n", strerror(errno));
}

int main(int argc, char **argv)
{
    XtAppContext appctx;
    Widget toplevel, hi;
    XInitThreads();
    toplevel = XtVaAppInitialize(&appctx, "NURxvt", NULL, 0, &argc, argv, NULL, 0);

    hi = XtVaCreateManagedWidget("I'm not urxvt!", labelWidgetClass, toplevel);
    launch((struct program){.prgnam = "xedit", .args = {"jess.txt", NULL}});
    XtRealizeWidget(toplevel);
    XtAppMainLoop(appctx);

    return 0;
    
}
