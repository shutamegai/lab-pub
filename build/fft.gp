# Gnuplot

set terminal png transparent
set output "../bin/data/fft.png"
cd "../bin/data"

set xrange[0:5000]

plot "fft.dat" with impulses lw 3