#
# Gnuplot script for ploting eigenfunction.
#
set terminal png size 800,600 enhanced font "arial,16"
set output 'eig-He-1s2.png'
set title "Eigenfunction 1s2 for He atom"
set xlabel "Radius [bohr]"
set ylabel "Eigenfunction(r)"
#set logscale x 
set xrange[0:6]
set xtics 1 font "arial, 12"
set mxtics 
plot "eig.dat.1s2" using 1:2 with lines title 'State 1s2' lw 4 lc rgb "#00FF00", 


