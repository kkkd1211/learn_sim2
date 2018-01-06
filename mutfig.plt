set term png
set output 'mut/OB+/kni.png'
set yrange [0:1]
set title 'Bcd+'
plot 'mut/OB+/final_P.txt' u 1 w l lc 18 t 'kni\_model','mut/tg_plot_data/B+/kni_tg_B+_P.txt' w p pt 12 lc 18 t 'kni'

set term png 
set output 'mut/OB+/hb.png'
set yrange [0:1]
set title 'Bcd+'
plot 'mut/OB+/final_P.txt' u 2 w l lc 7 t 'hb\_model','mut/tg_plot_data/B+/hb_tg_B+_P.txt' w p pt 12 lc 7 t 'hb' 

set term png 
set output 'mut/OB+/kr.png'
set yrange [0:1]
set title 'Bcd+'
plot 'mut/OB+/final_P.txt' u 3 w l lc 14 t 'kr\_model','mut/tg_plot_data/B+/kr_tg_B+_P.txt' w p pt 12 lc 14 t 'kr'

set term png 
set output 'mut/OB+/gt.png'
set yrange [0:1]
set title 'Bcd+'
plot 'mut/OB+/final_P.txt' u 4 w l lc 20 t 'gt\_model','mut/tg_plot_data/B+/gt_tg_B+_P.txt' w p pt 12 lc 20 t 'gt'



set term png 
set output 'mut/OB-/kni.png'
set yrange [0:1]
set title 'Bcd-'
plot 'mut/OB-/final_P.txt' u 1 w l lc 18 t 'kni\_model','mut/tg_plot_data/B-/kni_tg_B-_P.txt' w p pt 12 lc 18 t 'kni'

set term png
set output 'mut/OB-/hb.png'
set yrange [0:1]
set title 'Bcd-'
plot 'mut/OB-/final_P.txt' u 2 w l lc 7 t 'hb\_model','mut/tg_plot_data/B-/hb_tg_B-_P.txt' w p pt 12 lc 7 t 'hb'

set term png
set output 'mut/OB-/kr.png'
set yrange [0:1]
set title 'Bcd-'
plot 'mut/OB-/final_P.txt' u 3 w l lc 14 t 'kr\_model','mut/tg_plot_data/B-/kr_tg_B-_P.txt' w p pt 12 lc 14 t 'kr'

set term png
set output 'mut/OB-/gt.png'
set yrange [0:1]
set title 'Bcd-'
plot 'mut/OB-/final_P.txt' u 4 w l lc 20 t 'gt\_model','mut/tg_plot_data/B-/gt_tg_B-_P.txt' w p pt 12 lc 20 t 'gt'



set term png 
set output 'mut/ON+/kni.png'
set yrange [0:1]
set title 'Nos+'
plot 'mut/ON+/final_P.txt' u 1 w l lc 18 t 'kni\_model','mut/tg_plot_data/N+/kni_tg_N+_P.txt' w p pt 12 lc 18 t 'kni'

set term png 
set output 'mut/ON+/hb.png'
set yrange [0:1]
set title 'Nos+'
plot 'mut/ON+/final_P.txt' u 2 w l lc 7 t 'hb\_model','mut/tg_plot_data/N+/hb_tg_N+_P.txt' w p pt 12 lc 7 t 'hb'

set term png 
set output 'mut/ON+/kr.png'
set yrange [0:1]
set title 'Nos+'
plot 'mut/ON+/final_P.txt' u 3 w l lc 14 t 'kr\_model','mut/tg_plot_data/N+/kr_tg_N+_P.txt' w p pt 12 lc 14 t 'kr'

set term png 
set output 'mut/ON+/gt.png'
set yrange [0:1]
set title 'Nos+'
plot 'mut/ON+/final_P.txt' u 4 w l lc 20 t 'gt\_model','mut/tg_plot_data/N+/gt_tg_N+_P.txt' w p pt 12 lc 20 t 'gt'




set term png
set output 'mut/ON-/kni.png'
set yrange [0:1]
set title 'Nos-'
plot 'mut/ON-/final_P.txt' u 1 w l lc 18 t 'kni\_model','mut/tg_plot_data/N-/kni_tg_N-_P.txt' w p pt 12 lc 18 t 'kni'

set term png
set output 'mut/ON-/hb.png'
set yrange [0:1]
set title 'Nos-'
plot 'mut/ON-/final_P.txt' u 2 w l lc 7 t 'hb\_model','mut/tg_plot_data/N-/hb_tg_N-_P.txt' w p pt 12 lc 7 t 'hb'

set term png
set output 'mut/ON-/kr.png'
set yrange [0:1]
set title 'Nos-'
plot 'mut/ON-/final_P.txt' u 3 w l lc 14 t 'kr\_model','mut/tg_plot_data/N-/kr_tg_N-_P.txt' w p pt 12 lc 14 t 'kr'

set term png
set output 'mut/ON-/gt.png'
set yrange [0:1]
set title 'Nos-'
plot 'mut/ON-/final_P.txt' u 4 w l lc 20 t 'gt\_model','mut/tg_plot_data/N-/gt_tg_N-_P.txt' w p pt 12 lc 20 t 'gt'




set term png
set output 'mut/OT-/kni.png'
set yrange [0:1]
set title 'Tll-'
plot 'mut/OT-/final_P.txt' u 1 w l lc 18 t 'kni\_model','mut/tg_plot_data/T-/kni_tg_T-_P.txt' w p pt 12 lc 18 t 'kni'

set term png
set output 'mut/OT-/hb.png'
set yrange [0:1]
set title 'Tll-'
plot 'mut/OT-/final_P.txt' u 2 w l lc 7 t 'hb\_model','mut/tg_plot_data/T-/hb_tg_T-_P.txt' w p pt 12 lc 7 t 'hb'

set term png
set output 'mut/OT-/kr.png'
set yrange [0:1]
set title 'Tll-'
plot 'mut/OT-/final_P.txt' u 3 w l lc 14 t 'kr\_model','mut/tg_plot_data/T-/kr_tg_T-_P.txt' w p pt 12 lc 14 t 'kr'

set term png
set output 'mut/OT-/gt.png'
set yrange [0:1]
set title 'Tll-'
plot 'mut/OT-/final_P.txt' u 4 w l lc 20 t 'gt\_model','mut/tg_plot_data/T-/gt_tg_T-_P.txt' w p pt 12 lc 20 t 'gt'



