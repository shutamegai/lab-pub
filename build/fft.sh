#!/bin/sh

cd ../

test -f bin/fft.out && \
    mv bin/fft.out bin/_fft.out


echo '--------------------' > bin/debug/stderr.log

cd test/
gcc -o ../bin/fft.out fft.c -lfftw3 -lm 2>> ../bin/debug/stderr.log
cd ../

echo '--------------------' >> bin/debug/stderr.log

test -f bin/fft.out && \
    bin/fft.out > bin/data/fft.dat 2>> bin/debug/stderr.log

echo '--------------------' >> bin/debug/stderr.log

test -f bin/fft.out && \
    cat bin/data/fft.dat >> bin/debug/stderr.log

echo '--------------------' >> bin/debug/stderr.log

cat bin/debug/time.log >> bin/debug/stderr.log

cat bin/debug/stderr.log
