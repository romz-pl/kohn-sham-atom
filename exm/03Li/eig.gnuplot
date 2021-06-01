#
# Gnuplot script for ploting eigenfunction.
#
set terminal png size 800,600 enhanced font "arial,16"
set output 'eig-Li-1s2.png'
set title "Eigenfunction 1s2 for Li atom"
set xlabel "Radius [bohr]"
set ylabel "Eigenfunction(r)"
#set logscale x 
set xrange[0:6]
set xtics 1 font "arial, 12"
set mxtics 
plot "eig.dat.1s2" using 1:2 with lines title 'State 1s2' lw 4 lc rgb "#00FF00", 

set output 'eig-Li-2s1.png'
set title "Eigenfunction 2s1 for Li atom"
set xrange[0:16]
plot "eig.dat.2s1" using 1:2 with lines title 'State 2s1' lw 4 lc rgb "#00FF00",
