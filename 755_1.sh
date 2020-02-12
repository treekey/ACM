#! /bin/bash

less <&0 |
tr [ABC] 2 |
tr [DEF] 3 |
tr [GHI] 4 |
tr [JKL] 5 |
tr [MNO] 6 |
tr [PRS] 7 |
tr [TUV] 8 |
tr [WXY] 9 |
tr -d "-" |
sort |
uniq -c -d |
awk '{print substr($2, 0, 3) "-" substr($2, 3) " " $1}'
