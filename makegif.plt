set term gif animate
set yrange [0:1]
set output 'O.gif'
do for [i=1:50]{
set title sprintf("%d",i)
plot 'kni_P.txt' u i w l lc 18 t 'kni','hb_P.txt' u i w l lc 7 t 'hb','kr_P.txt' u i w l lc 14 t 'kr','gt_P.txt' u i w l lc 20 t 'gt' 
}

set term png
set output 'fi.png'
set yrange [0:1]
plot 'final_P.txt' u 1 w l lc 18 t 'kni','' u 2 w l lc 7 t 'hb','' u 3 w l lc 14 t 'kr','' u 4 w l lc 20 t 'gt','../../../input/Bcd_P.txt' w l lt 0 lc -1 t 'Bcd','../../../input/Tll_P.txt' w l lt 0 lc -1 t 'Tll'

set term png
set output 'kni.png'
set yrange [0:1]
plot 'final_P.txt' u 1 w l lc 18 t 'kni\_model','../../../data_final/kni_target_P.txt' w p pt 12 lc 18 t 'kni'

set term png
set output 'hb.png'
set yrange [0:1]
plot 'final_P.txt' u 2 w l lc 7 t 'hb\_model','../../../data_final/hb_target_P.txt' w p pt 12 lc 7 t 'hb'

set term png
set output 'kr.png'
set yrange [0:1]
plot 'final_P.txt' u 3 w l lc 14 t 'kr\_model','../../../data_final/kr_target_P.txt' w p pt 12 lc 14 t 'kr'

set term png
set output 'gt.png'
set yrange [0:1]
plot 'final_P.txt' u 4 w l lc 20 t 'gt\_model','../../../data_final/gt_target_P.txt' w p pt 12 lc 20 t 'gt'




