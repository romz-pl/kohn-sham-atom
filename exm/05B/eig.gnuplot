#
# Gnuplot script for ploting eigenfunction.
#
set terminal png size 800,600 enhanced font "arial,16"
set xlabel "Radius [bohr]"
set ylabel "Eigenfunction(r)"
set xtics 1 font "arial, 12"
set mxtics 

set output 'eig-B-1s2.png'
set title "Eigenfunction 1s2 for B atom"
set xrange[0:3]
plot "eig.dat.1s2" using 1:2 with lines title 'State 1s2' lw 4 lc rgb "#00FF00", 

set output 'eig-B-2s2.png'
set title "Eigenfunction 2s2 for B atom"
set xrange[0:10]
plot "eig.dat.2s2" using 1:2 with lines title 'State 2s2' lw 4 lc rgb "#00FF00",

set output 'eig-B-2p1.png'
set title "Eigenfunction 2p1 for B atom"
set xrange[0:10]
plot "eig.dat.2p1" using 1:2 with lines title 'State 2p1' lw 4 lc rgb "#00FF00",
