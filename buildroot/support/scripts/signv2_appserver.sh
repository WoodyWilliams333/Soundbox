#!/bin/bash

SIGNTOOL=$1
HOSTPORT=$2
ASKEY=$3
TARGET=$4
CID=$5

CUR_YEAR=`date +'%Y'`
EXP_YEAR=`expr $CUR_YEAR + 19`
MONTH=`date +'%m'`
DAY=`date +'%d'`
CURRENT_TIME=$CUR_YEAR$MONTH$DAY
EXPIRED_TIME=$EXP_YEAR$MONTH$DAY

touch $ASKEY.puk
$SIGNTOOL -k $ASKEY -x "" -S 1024 -c $HOSTPORT -o $ASKEY.puk
cat $TARGET $ASKEY.puk > $TARGET.tmp
touch $TARGET-$CID
$SIGNTOOL  -g -m "SIG:0002" -i $CID -k $ASKEY -t app -d $CURRENT_TIME -e $EXPIRED_TIME -c $HOSTPORT -f $TARGET.tmp -o $TARGET-$CID
if [ "$?" -eq "0" ]; then
    mv $TARGET-$CID $TARGET
fi
rm $ASKEY.puk $TARGET.tmp
