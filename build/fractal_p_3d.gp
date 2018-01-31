# Gnuplot

set terminal png transparent enhanced font ",30" size 1280,900
#set terminal postscript eps enhanced color
set output "../bin/data/iteration/3d/200_3d.png"
cd "../bin/data/matrix"
set hidden3d
set ticslevel 0
set size square

set cbrange [0:0.04]
set xrange [0:85]
set yrange [0:85]
set zrange [0:0.04]

set xlabel offset 0,-1.5
set ylabel offset 2,0
set xlabel "X"
set ylabel "Y"
set zlabel "P"
set xtics offset 0,-0.5
set ytics offset 0.5,0
set xtics 20
set ytics 20
set ztics 0.01
set cbtics 0.01

#set palette rgbformula 22,13,-31

#set title "t = 400" font ",55"
#set title 10,-1
splot "200.dat" notitle with pm3d