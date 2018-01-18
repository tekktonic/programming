#include <X11/Xlib.h>

#include <X11/Xatom.h>
#include <X11/Intrinsic.h>
#include <X11/StringDefs.h>
#include <X11/Shell.h>


#include <X11/Xaw/Form.h>
#include <X11/Xaw/Command.h>
#include <X11/Xaw/Paned.h>

int main(int argc, char **argv)
{

    XtAppContext ctx;

    Widget toplevel, container, term, quit;

    Arg containerargs[10];
    Arg quitarg;
    Display *dsp;


    toplevel = XtOpenApplication (&ctx, "XFirst", NULL, 0, &argc,
				  argv, NULL, applicationShellWidgetClass, NULL,
				  0);
    dsp = XtDisplay(toplevel);

    XtSetArg(dsp, Xt
    quit = XtVaCreateManagedWidget("Quit", commandWidgetClass, toplevel);


    XtRealizeWidget(toplevel);
    XtAppMainLoop(ctx);

    return 0;

}

