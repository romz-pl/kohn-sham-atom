#
# Gnuplot script for ploting eigenfunction.
#
set terminal png size 800,600 enhanced font "arial,16"
set xlabel "Radius [bohr]"
set ylabel "Eigenfunction(r)"
set xtics 1 font "arial, 12"
set mxtics 

set output 'eig-Nd-1s2.png'
set title "Eigenfunction 1s2 for Nd atom"
set xrange[0:0.3]
set xtics 0.1
plot "eig.dat.1s2" using 1:2 with lines title 'State 1s2' lw 4 lc rgb "#00FF00", 

set output 'eig-Nd-2s2.png'
set title "Eigenfunction 2s2 for Nd atom"
set xrange[0:0.6]
set xtics 0.2
plot "eig.dat.2s2" using 1:2 with lines title 'State 2s2' lw 4 lc rgb "#00FF00",

set output 'eig-Nd-2p6.png'
set title "Eigenfunction 2p6 for Nd atom"
set xrange[0:0.8]
set xtics 0.2
plot "eig.dat.2p6" using 1:2 with lines title 'State 2p6' lw 4 lc rgb "#00FF00",

set output 'eig-Nd-3s2.png'
set title "Eigenfunction 3s2 for Nd atom"
set xrange[0:1]
set xtics 0.2
plot "eig.dat.3s2" using 1:2 with lines title 'State 3s2' lw 4 lc rgb "#00FF00",

set output 'eig-Nd-3p6.png'
set title "Eigenfunction 3p6 for Nd atom"
set xrange[0:2]
set xtics 0.5
plot "eig.dat.3p6" using 1:2 with lines title 'State 3p6' lw 4 lc rgb "#00FF00",

set output 'eig-Nd-4s2.png'
set title "Eigenfunction 4s2 for Nd atom"
set xrange[0:2]
set xtics 1
plot "eig.dat.4s2" using 1:2 with lines title 'State 4s2' lw 4 lc rgb "#00FF00",

set output 'eig-Nd-3d10.png'
set title "Eigenfunction 3d10 for Nd atom"
set xrange[0:3]
set xtics 1
plot "eig.dat.3d10" using 1:2 with lines title 'State 3d10' lw 4 lc rgb "#00FF00",

set output 'eig-Nd-4p6.png'
set title "Eigenfunction 4p6 for Nd atom"
set xrange[0:3]
set xtics 1
plot "eig.dat.4p6" using 1:2 with lines title 'State 4p6' lw 4 lc rgb "#00FF00",

set output 'eig-Nd-4d10.png'
set title "Eigenfunction 4d10 for Nd atom"
set xrange[0:5]
set xtics 1
plot "eig.dat.4d10" using 1:2 with lines title 'State 4d10' lw 4 lc rgb "#00FF00",

set output 'eig-Nd-5s2.png'
set title "Eigenfunction 5s2 for Nd atom"
set xrange[0:4]
set xtics 1
plot "eig.dat.5s2" using 1:2 with lines title 'State 5s2' lw 4 lc rgb "#00FF00",

set output 'eig-Nd-5p6.png'
set title "Eigenfunction 5p6 for Nd atom"
set xrange[0:5]
set xtics 1
plot "eig.dat.5p6" using 1:2 with lines title 'State 5p6' lw 4 lc rgb "#00FF00",

set output 'eig-Nd-6s2.png'
set title "Eigenfunction 6s2 for Nd atom"
set xrange[0:12]
set xtics 1
plot "eig.dat.6s2" using 1:2 with lines title 'State 6s2' lw 4 lc rgb "#00FF00",

set output 'eig-Nd-4f4.png'
set title "Eigenfunction 4f4 for Nd atom"
set xrange[0:10]
set xtics 1
plot "eig.dat.4f4" using 1:2 with lines title 'State 4f4' lw 4 lc rgb "#00FF00",

