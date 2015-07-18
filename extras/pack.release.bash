#!/bin/bash -ex

VERSION=`grep version= platform.txt | sed 's/version=//g'`

PWD=`pwd`
FOLDERNAME=`basename $PWD`
THIS_SCRIPT_NAME=`basename $0`

rm -f <core>-$VERSION.tar.bz2

cd ..
tar --transform "s|$FOLDERNAME|$FOLDERNAME-$VERSION|g"  --exclude=extras/** --exclude=.git* --exclude=.idea -cjf <core>-$VERSION.tar.bz2 $FOLDERNAME
cd -

mv ../<core>-$VERSION.tar.bz2 .

