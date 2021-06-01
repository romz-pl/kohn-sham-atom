#
# Gnuplot script for ploting eigenfunction.
#
set terminal png size 800,600 enhanced font "arial,16"
set xlabel "Radius [bohr]"
set ylabel "Eigenfunction(r)"
set xtics 1 font "arial, 12"
set mxtics 

set output 'eig-F-1s2.png'
set title "Eigenfunction 1s2 for F atom"
set xrange[0:2]
plot "eig.dat.1s2" using 1:2 with lines title 'State 1s2' lw 4 lc rgb "#00FF00", 

set output 'eig-F-2s2.png'
set title "Eigenfunction 2s2 for F atom"
set xrange[0:6]
plot "eig.dat.2s2" using 1:2 with lines title 'State 2s2' lw 4 lc rgb "#00FF00",

set output 'eig-F-2p5.png'
set title "Eigenfunction 2p5 for F atom"
set xrange[0:8]
plot "eig.dat.2p5" using 1:2 with lines title 'State 2p5' lw 4 lc rgb "#00FF00",
