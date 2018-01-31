# Gnuplot

#set terminal png transparent
set terminal postscript eps enhanced color
set output "../bin/data/return.eps"
cd "../bin/data"
set logscale xy

set size 1, 0.7

#set title "Return probability" font ",15"
set key font ",20" left bottom
set xlabel "t" font ",25"
set ylabel "P" font ",25"
set xtics font ",20"
set ytics font ",20"

a=90
b=-0.9

f(x)=a*x**b

fit f(x) "return.txt" using 1:2 via a, b
plot f(x) lc 'blue' notitle, "return.txt" using 1:2 lc 'red' pt 7 notitle
#plot f(x) lc 'blue' title sprintf("%fx^{%f}", a, b), \
#     "return.txt" using 1:2 lc 'red' pt 7 title "data"