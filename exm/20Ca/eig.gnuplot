#
# Gnuplot script for ploting eigenfunction.
#
set terminal png size 800,600 enhanced font "arial,16"
set xlabel "Radius [bohr]"
set ylabel "Eigenfunction(r)"
set xtics 1 font "arial, 12"
set mxtics 

set output 'eig-Ca-1s2.png'
set title "Eigenfunction 1s2 for Ca atom"
set xrange[0:0.6]
set xtics 0.1
plot "eig.dat.1s2" using 1:2 with lines title 'State 1s2' lw 4 lc rgb "#00FF00", 

set output 'eig-Ca-2s2.png'
set title "Eigenfunction 2s2 for Ca atom"
set xrange[0:1.5]
set xtics 0.5
plot "eig.dat.2s2" using 1:2 with lines title 'State 2s2' lw 4 lc rgb "#00FF00",

set output 'eig-Ca-2p6.png'
set title "Eigenfunction 2p6 for Ca atom"
set xrange[0:2]
set xtics 0.5
plot "eig.dat.2p6" using 1:2 with lines title 'State 2p6' lw 4 lc rgb "#00FF00",

set output 'eig-Ca-3s2.png'
set title "Eigenfunction 3s2 for Ca atom"
set xrange[0:5]
set xtics 1
plot "eig.dat.3s2" using 1:2 with lines title 'State 3s2' lw 4 lc rgb "#00FF00",

set output 'eig-Ca-3p6.png'
set title "Eigenfunction 3p6 for Ca atom"
set xrange[0:8]
set xtics 1
plot "eig.dat.3p6" using 1:2 with lines title 'State 3p6' lw 4 lc rgb "#00FF00",

set output 'eig-Ca-4s2.png'
set title "Eigenfunction 4s2 for Ca atom"
set xrange[0:14]
set xtics 1
plot "eig.dat.4s2" using 1:2 with lines title 'State 4s2' lw 4 lc rgb "#00FF00",
