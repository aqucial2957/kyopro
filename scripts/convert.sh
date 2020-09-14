#!/bin/bash

# hogehoge -> "hogehoge",とする
# 改行コードがLFの前提
sed -e 's/^/"/' ./library/$1.h \
| sed -e 's/$/",/' \
> $1.template