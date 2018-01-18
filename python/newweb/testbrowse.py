import pygtk
import gtk
import wof
import sys

conn = wof.WOFConnection("localhost")

w = gtk.Window()

tv = gtk.TextView()
b = tv.get_buffer()
scroll = gtk.ScrolledWindow()
page = conn.GetToText(sys.argv[1]).split("\n", 1)
w.set_title(page[0])

b.set_text(page[1])
tv.set_wrap_mode(gtk.WRAP_WORD)
w.set_default_size(300, 300)
scroll.add(tv)
w.add(scroll)
w.connect("destroy", lambda w: gtk.main_quit())
w.show_all()

gtk.main()
