# Gnuplot

set terminal gif animate delay 10
set output "../bin/data/fractal_p_3d.gif"
cd "../bin/data/matrix"
j=0

while (j<2000) {

set multiplot layout 1,2
set hidden3d
set ticslevel 0.1
set size square

set cbrange [0:0.09]
set xrange [0:85]
set yrange [0:85]
set zrange [0:0.09]
set title "The probability distribution"
set xlabel "X"
set ylabel "Y"
#set cblabel "P"
set xtics 20
set ytics 20
splot sprintf("%d.dat", j) notitle with pm3d

set autoscale
cd "../"

set xrange [0:2000]
set yrange [0:0.09]
set title "Time evolution of \nthe marked vertex probability"
set xlabel "t"
set ylabel ""
set xtics 500
set ytics 0.01
plot "fractal_mark_p.dat" every ::0:0:j:0 with line notitle
set autoscale

j = j+10
cd "./matrix"
unset multiplot

}