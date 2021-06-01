#
# Gnuplot script for ploting eigenfunction.
#
set terminal png size 800,600 enhanced font "arial,16"
set xlabel "Radius [bohr]"
set ylabel "Eigenfunction(r)"
set xtics 1 font "arial, 12"
set mxtics 

set output 'eig-O-1s2.png'
set title "Eigenfunction 1s2 for O atom"
set xrange[0:2]
plot "eig.dat.1s2" using 1:2 with lines title 'State 1s2' lw 4 lc rgb "#00FF00", 

set output 'eig-O-2s2.png'
set title "Eigenfunction 2s2 for O atom"
set xrange[0:8]
plot "eig.dat.2s2" using 1:2 with lines title 'State 2s2' lw 4 lc rgb "#00FF00",

set output 'eig-O-2p4.png'
set title "Eigenfunction 2p4 for O atom"
set xrange[0:10]
plot "eig.dat.2p4" using 1:2 with lines title 'State 2p4' lw 4 lc rgb "#00FF00",
