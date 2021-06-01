#
# Gnuplot script for ploting total electron density.
#
set terminal png size 800,600 enhanced font "Helvetica,16"
set output 'rho.png'
set title "Radial total electron distribution"
set xlabel "Radius [bohr]"
set ylabel "rho(r)"
# set logscale x 
set xrange[0:8]
set xtics 1
set mxtics 
plot "rho.dat" using 1:2 with lines title 'Rho' lw 4 lc rgb "#FF0000", 


