def think(f):
    f()


@think
def foo():
    print "bar"

while True:
    think()
