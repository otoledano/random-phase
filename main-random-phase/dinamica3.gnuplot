#set term x11
set xlabel "x (Angstrom)"
set ylabel "y (Angstrom)"
set size square


set key autotitle columnhead
unset key
stats dir.'dynamic.txt' nooutput
set xrange [0:STATS_max_x]
set yrange [0:STATS_max_y]
M=(150/STATS_max_x)


set palette defined ( 0 "blue", 1 "yellow", 2 "red" )
set cbrange [0.5:0.8]



N=ARG2
i=0
set key at STATS_max_x*(0.1),STATS_max_y*(-0.05)
while (i<=N) {i=i+1;plot dir.'dynamic.txt' u 1:2:($2*0+ARG3/2.0):3 every ::(i-1)*ARG1::i*ARG1-1 w circles lc palette fs transparent solid 0.8 t sprintf("%.3f\%",i*100.0/N); pause mouse key; if (MOUSE_KEY == 97) {i=i-2}} 

pause -1
