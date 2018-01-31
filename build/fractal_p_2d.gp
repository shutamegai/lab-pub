# Gnuplot

set terminal postscript enhanced color font ",19"
set output "../bin/data/iteration/2d/400_2d.eps"
cd "../bin/data"
set size square
set pm3d map

#set cbrange [0:0.09]
#set xrange [0:85]
#set yrange [0:85]

set xlabel "X"
set ylabel "Y"
set cblabel "P"
#set xtics 20
#set ytics 20
set title "t = 400" font ",40"
splot "fractal_p.dat" notitle