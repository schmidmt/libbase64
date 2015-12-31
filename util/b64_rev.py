#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""Generate the reverse mapping for base64 encoding
"""

BASIS = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"

for i in xrange(256):
    if i % 16 == 0 and i != 0:
        print "\n",
    c = chr(i)
    if c == '=':
        print "{:2d},".format(0),
    elif c in BASIS:
        print "{:2d},".format(BASIS.index(c)),
    else:
        print "{:2d},".format(64),
