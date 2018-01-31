#!/bin/sh

{
LANG=C
date
who

echo '--------------------'

gnuplot << EOF
load "fractal_p_2d.gp"
EOF

gnuplot << EOF
load "fractal_p_3d.gp"
EOF
} 2> ../bin/debug/stderr.log


cat ../bin/debug/stderr.log
