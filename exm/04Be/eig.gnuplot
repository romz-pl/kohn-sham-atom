#
# Gnuplot script for ploting eigenfunction.
#
set terminal png size 800,600 enhanced font "arial,16"
set output 'eig-Be-1s2.png'
set title "Eigenfunction 1s2 for Be atom"
set xlabel "Radius [bohr]"
set ylabel "Eigenfunction(r)"
#set logscale x 
set xrange[0:3]
set xtics 1 font "arial, 12"
set mxtics 
plot "eig.dat.1s2" using 1:2 with lines title 'State 1s2' lw 4 lc rgb "#00FF00", 

set output 'eig-Be-2s2.png'
set title "Eigenfunction 2s2 for Li atom"
set xrange[0:10]
plot "eig.dat.2s2" using 1:2 with lines title 'State 2s2' lw 4 lc rgb "#00FF00",
