#!/bin/sh

PROG=mkslack-`date +%d%m%y`
DIR=`pwd`

mkdir -p /tmp/tekk/$PROG
cp -rf * /tmp/tekk/$PROG/
cd /tmp/tekk
tar czf $DIR/$PROG.tar.gz $PROG
