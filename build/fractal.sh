#!/bin/sh

cd ../

test -f bin/main.out && \
    mv bin/main.out bin/_main.out


echo '--------------------' > bin/debug/stderr.log

make main_gcc 2>> bin/debug/stderr.log

echo '--------------------' >> bin/debug/stderr.log

test -f bin/main.out && \
    bin/main.out > bin/data/fractal_p.dat 2>> bin/debug/stderr.log

echo '--------------------' >> bin/debug/stderr.log

test -f bin/main.out && \
    cat bin/data/fractal_p.dat >> bin/debug/stderr.log

echo '--------------------' >> bin/debug/stderr.log

cat bin/debug/time.log >> bin/debug/stderr.log

cat bin/debug/stderr.log
