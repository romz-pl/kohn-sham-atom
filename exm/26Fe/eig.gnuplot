#
# Gnuplot script for ploting eigenfunction.
#
set terminal png size 800,600 enhanced font "arial,16"
set xlabel "Radius [bohr]"
set ylabel "Eigenfunction(r)"
set xtics 1 font "arial, 12"
set mxtics 

set output 'eig-Fe-1s2.png'
set title "Eigenfunction 1s2 for Fe atom"
set xrange[0:0.3]
set xtics 0.1
plot "eig.dat.1s2" using 1:2 with lines title 'State 1s2' lw 4 lc rgb "#00FF00", 

set output 'eig-Fe-2s2.png'
set title "Eigenfunction 2s2 for Fe atom"
set xrange[0:1]
set xtics 0.2
plot "eig.dat.2s2" using 1:2 with lines title 'State 2s2' lw 4 lc rgb "#00FF00",

set output 'eig-Fe-2p6.png'
set title "Eigenfunction 2p6 for Fe atom"
set xrange[0:1]
set xtics 0.2
plot "eig.dat.2p6" using 1:2 with lines title 'State 2p6' lw 4 lc rgb "#00FF00",

set output 'eig-Fe-3s2.png'
set title "Eigenfunction 3s2 for Fe atom"
set xrange[0:3]
set xtics 1
plot "eig.dat.3s2" using 1:2 with lines title 'State 3s2' lw 4 lc rgb "#00FF00",

set output 'eig-Fe-3p6.png'
set title "Eigenfunction 3p6 for Fe atom"
set xrange[0:3]
set xtics 1
plot "eig.dat.3p6" using 1:2 with lines title 'State 3p6' lw 4 lc rgb "#00FF00",

set output 'eig-Fe-4s2.png'
set title "Eigenfunction 4s2 for Fe atom"
set xrange[0:10]
set xtics 1
plot "eig.dat.4s2" using 1:2 with lines title 'State 4s2' lw 4 lc rgb "#00FF00",

set output 'eig-Fe-3d6.png'
set title "Eigenfunction 3d6 for Fe atom"
set xrange[0:8]
set xtics 1
plot "eig.dat.3d6" using 1:2 with lines title 'State 3d6' lw 4 lc rgb "#00FF00",

