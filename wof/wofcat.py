#!/usr/bin/env python
"""Copyright (c) 2012, Daniel Wilkins
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the WOF nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 'AS IS' AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL Daniel Wilkins BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."""
import socket as sock
import sys
import hrsize

s = sock.socket(sock.AF_INET, sock.SOCK_STREAM)

s.setsockopt(sock.SOL_SOCKET, sock.SO_REUSEADDR, 1)

s.connect((sys.argv[1], 1337))

s.send("GET " + sys.argv[2])

out = ""

done = False
first = True
size = 0.0
while not done:
    data = s.recv(4096)
    size += len(data)
    if not data:
        done = True

    if first:
	sys.stderr.write("received: " + hrsize.hrsize(size) + "\n")
	first = False
    else:
	sys.stderr.write("\b\rreceived: " + hrsize.hrsize(size) + "kb\n")
    print(data)
