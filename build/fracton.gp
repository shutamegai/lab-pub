# Gnuplot

#set terminal png transparent
set terminal postscript eps enhanced color
set output "../bin/data/fracton.eps"
cd "../bin/data"
set logscale xy

set size 1, 0.7

#set title "The linear fits are for the data from Stage=1 to Stage=8." font ",15"
set key font ",20" right bottom
set xlabel "N" font ",25"
set ylabel "Q" font ",25"
set xtics font ",20"
set ytics font ",20"

f(x)=a*x**b

fit f(x) "fracton.txt" using (8**$1):2 via a, b
plot f(x) lc 'blue' notitle, "fracton.txt" using (8**$1):2 lc 'red' pt 7 notitle
#plot f(x) lc 'blue' title sprintf("%fx^{%f}", a, b), \
#     "fracton.txt" using (8**$1):2 lc 'red' pt 7 title "data"