#!/usr/bin/env python

import sys, subprocess

null = open("/dev/null", "w")

argc = sys.argv.__len__()
if argc < 3:
    print("you need at least 2 arguments: the program to look for and the command to be run")
    sys.exit(-1)
proc = sys.argv[1]

cmd = sys.argv[2]

args = ""

if sys.argv[3]:
    i = 3

    while i < argc:
        args += sys.argv[i]
        i += 1

wasrunning = False

if not subprocess.call(["pgrep", proc], stdout = null, stderr = null): # pgrep returns 0 if it finds the process
    wasrunning = True

while not subprocess.call(["pgrep", proc], stdout = null, stderr = null):
    pass

if wasrunning:
    subprocess.call([cmd, args])
    
