#
# Gnuplot script for ploting total electron density.
#
set terminal png size 800,600 enhanced font "Helvetica,16"
set output 'eig.png'
set title "Eigenfunction 3s2 for Mg atom"
set xlabel "Radius [bohr]"
set ylabel "Eigenfunction(r)"
# set logscale x 
set xrange[0:10]
set xtics 1
set mxtics 
plot "eig.dat.3s2" using 1:2 with lines title 'State 3s2' lw 4 lc rgb "#00FF00", 


