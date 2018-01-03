set term png
set output 'output/fi.png'
set yrange [0:1]
plot 'output/final_P.txt' u 1 w l lc 18 t 'kni','' u 2 w l lc 7 t 'hb','' u 3 w l lc 14 t 'kr','' u 4 w l lc 21 t 'gt','input/Bcd_P.txt' w l lt 0 lc -1 t 'Bcd','input/Tll_P.txt' w l lt 0 lc -1 t 'Tll'

