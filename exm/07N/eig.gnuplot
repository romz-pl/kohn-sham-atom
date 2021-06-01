#
# Gnuplot script for ploting eigenfunction.
#
set terminal png size 800,600 enhanced font "arial,16"
set xlabel "Radius [bohr]"
set ylabel "Eigenfunction(r)"
set xtics 1 font "arial, 12"
set mxtics 

set output 'eig-N-1s2.png'
set title "Eigenfunction 1s2 for N atom"
set xrange[0:2]
plot "eig.dat.1s2" using 1:2 with lines title 'State 1s2' lw 4 lc rgb "#00FF00", 

set output 'eig-N-2s2.png'
set title "Eigenfunction 2s2 for N atom"
set xrange[0:8]
plot "eig.dat.2s2" using 1:2 with lines title 'State 2s2' lw 4 lc rgb "#00FF00",

set output 'eig-N-2p3.png'
set title "Eigenfunction 2p3 for N atom"
set xrange[0:10]
plot "eig.dat.2p3" using 1:2 with lines title 'State 2p3' lw 4 lc rgb "#00FF00",
