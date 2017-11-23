#!/bin/sh

srcdir=`pwd`

TFN=fib.tmp$$
BFN=$srcdir/fib.data.ans

rm -f $FN

../src/sandbox -e $1 -d $srcdir/fib.data -o $TFN -p gmon.out
if [ $? -ne 0 ]; then
	exit 1
fi

cmp -s $TFN $BFN
RET=$?

echo
moxie-none-moxiebox-gprof -l $1

rm -f $TFN gmon.out

if [ $RET -ne 0 ]; then
	exit 1
fi

exit 0
