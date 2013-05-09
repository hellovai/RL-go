#!/bin/bash

cd results;
rm black/*
#gets easy result data
array=`wc -l *.dat | grep "100 " | awk -F "100 " '{print $2}'`
array=`ls result+black-3+white-*.dat`
for i in  $array
do 
	ctr=0
	sum=0
	avg=0
	while read line
	do 
		val=`echo $line | awk -F " " '{print $2}'`
		if [[ $val -gt 0 ]]; then
			val=1
		else
			#statements
			val=0
		fi
		ctr=$(($ctr+$val))
		# ctr=$(($ctr+1))
		# avg=$(($sum + $val * $ctr))
		# sum=$(($sum+$val))
		# avg=$(($avg / $ctr))
		echo "$ctr">> "black/$i"
	done < "$i"
	# title=`echo $i | awk -F "result+" '{print $2}' | awk -F "." '{print $1}' | tr '-' ' ' | tr '+' ' '`
done
	name="UCT-Heuristic vs UCT-Random"
	echo "reset
	set term postscript
	set output \"./plot/graphs/plot.ps\"
	set xlabel 'Episode'
	set ylabel 'Total Accumulated Wins'
	plot x with lines linecolor rgb 'black' lt 1 notitle, x*0.5 with lines linecolor rgb 'black' lt 1 notitle, \
	 './black/result+black-3+white-0.dat' with lines linecolor rgb 'red' lt 1 lw 2 title 'Heuristic vs Random'
	" | gnuplot
	convert -rotate 90 -flatten plot/graphs/plot.ps ~/Desktop/data/plot0.png

	name="UCT-Heuristic vs UCT-Random"
	echo "reset
	set term postscript
	set output \"./plot/graphs/plot.ps\"
	set xlabel 'Episode'
	set ylabel 'Total Accumulated Wins'
	plot x with lines linecolor rgb 'black' lt 1 notitle, x*0.5 with lines linecolor rgb 'black' lt 1 notitle, \
	 './black/result+black-1-13+white-1-10.dat' with lines linecolor rgb 'red' lt 1 lw 2 title 'Level 1',\
	 './black/result+black-5-13+white-5-10.dat' with lines linecolor rgb 'blue' lt 1 lw 2 title 'Level 5'
	" | gnuplot
	convert -rotate 90 -flatten plot/graphs/plot.ps ~/Desktop/data/plot1.png

	name="Heuristic vs UCT-Random"
	echo "reset
	set term postscript
	set output \"./plot/graphs/plot.ps\"
	set xlabel 'Episode'
	set ylabel 'Total Accumulated Wins'
	plot x with lines linecolor rgb 'black' lt 1 notitle, x*0.5 with lines linecolor rgb 'black' lt 1 notitle, \
	 './black/result+black-3+white-1-10.dat' with lines linecolor rgb 'red' lt 1 lw 2 title 'Level 1', \
	 './black/result+black-3+white-5-10.dat' with lines linecolor rgb 'blue' lt 1 lw 2 title 'Level 5', \
	 './black/result+black-3+white-10-10.dat' with lines linecolor rgb 'green' lt 1 lw 2 title 'Level 10'
	" | gnuplot
	convert -rotate 90 -flatten plot/graphs/plot.ps ~/Desktop/data/plot2.png

	name="Heuristic vs UCT-Heuristic"
	echo "reset
	set term postscript
	set output \"./plot/graphs/plot.ps\"
	set xlabel 'Episode'
	set ylabel 'Total Accumulated Wins'
	plot x with lines linecolor rgb 'black' lt 1 notitle, x*0.5 with lines linecolor rgb 'black' lt 1 notitle, \
	 './black/result+black-3+white-1-13.dat' with lines linecolor rgb 'red' lt 1 lw 2 title 'Level 1', \
	 './black/result+black-3+white-5-13.dat' with lines linecolor rgb 'blue' lt 1 lw 2 title 'Level 5', \
	 './black/result+black-3+white-10-13.dat' with lines linecolor rgb 'green' lt 1 lw 2 title 'Level 10'
	" | gnuplot
	convert -rotate 90 -flatten plot/graphs/plot.ps ~/Desktop/data/plot3.png

	name="Heuristic vs UCT-Rave-Random"
	echo "reset
	set term postscript
	set output \"./plot/graphs/plot.ps\"
	set xlabel 'Episode'
	set ylabel 'Total Accumulated Wins'
	plot x with lines linecolor rgb 'black' lt 1 notitle, x*0.5 with lines linecolor rgb 'black' lt 1 notitle, \
	 './black/result+black-3+white-1-20.dat' with lines linecolor rgb 'red' lt 1 lw 2 title 'Level 1', \
	 './black/result+black-3+white-5-20.dat' with lines linecolor rgb 'blue' lt 1 lw 2 title 'Level 5', \
	 './black/result+black-3+white-10-20.dat' with lines linecolor rgb 'green' lt 1 lw 2 title 'Level 10'
	" | gnuplot
	convert -rotate 90 -flatten plot/graphs/plot.ps ~/Desktop/data/plot4.png
	
	name="Heuristic vs UCT-Rave-Heuristic"
	echo "reset
	set term postscript
	set output \"./plot/graphs/plot.ps\"
	set xlabel 'Episode'
	set ylabel 'Total Accumulated Wins'
	plot x with lines linecolor rgb 'black' lt 1 notitle, x*0.5 with lines linecolor rgb 'black' lt 1 notitle, \
	 './black/result+black-3+white-1-23.dat' with lines linecolor rgb 'red' lt 1 lw 2 title 'Level 1', \
	 './black/result+black-3+white-5-23.dat' with lines linecolor rgb 'blue' lt 1 lw 2 title 'Level 5', \
	 './black/result+black-3+white-10-23.dat' with lines linecolor rgb 'green' lt 1 lw 2 title 'Level 10'
	" | gnuplot
	convert -rotate 90 -flatten plot/graphs/plot.ps ~/Desktop/data/plot5.png

	name="Self Play Level 5"
	echo "reset
	set term postscript
	set output \"./plot/graphs/plot.ps\"
	set xlabel 'Episode'
	set ylabel 'Total Accumulated Wins'
	plot x with lines linecolor rgb 'black' lt 1 notitle, x*0.5 with lines linecolor rgb 'black' lt 1 notitle, \
	 './black/result+black-5-10+white-5-10.dat' with lines linecolor rgb 'red' lt 1 lw 2 title 'UCT-Random', \
	 './black/result+black-5-13+white-5-13.dat' with lines linecolor rgb 'blue' lt 1 lw 2 title 'UCT-Heuristic', \
	 './black/result+black-5-20+white-5-20.dat' with lines linecolor rgb 'green' lt 1 lw 2 title 'UCT-Rave-Random', \
	 './black/result+black-5-23+white-5-23.dat' with lines linecolor rgb 'purple' lt 1 lw 2 title 'UCT-Rave-Heuristic'
	" | gnuplot
	convert -rotate 90 -flatten plot/graphs/plot.ps ~/Desktop/data/plot6.png	

	name="UCT-Rave vs UCT, Level 5"
	echo "reset
	set term postscript
	set output \"./plot/graphs/plot.ps\"
	set xlabel 'Episode'
	set ylabel 'Total Accumulated Wins'
	plot x with lines linecolor rgb 'black' lt 1 notitle, x*0.5 with lines linecolor rgb 'black' lt 1 notitle, \
	 './black/result+black-5-20+white-5-10.dat' with lines linecolor rgb 'red' lt 1 lw 2 title 'Random Policy', \
	 './black/result+black-5-23+white-5-13.dat' with lines linecolor rgb 'blue' lt 1 lw 2 title 'Heuristic Policy'
	" | gnuplot
	convert -rotate 90 -flatten plot/graphs/plot.ps ~/Desktop/data/plot7.png	

	name="UCT-Random vs Random"
	echo "reset
	set term postscript
	set output \"./plot/graphs/plot.ps\"
	set xlabel 'Episode'
	set ylabel 'Total Accumulated Wins'
	plot x with lines linecolor rgb 'black' lt 1 notitle, x*0.5 with lines linecolor rgb 'black' lt 1 notitle, \
	 './black/result+black-1-10+white-1.dat' with lines linecolor rgb 'red' lt 1 lw 2 title 'Raw Reward', \
	 './black/reward1.dat' with lines linecolor rgb 'blue' lt 1 lw 2 title 'Normalized Reward'
	" | gnuplot
	convert -rotate 90 -flatten plot/graphs/plot.ps ~/Desktop/data/plot8.png	

	name="Cumulative"
	echo "reset
	set term postscript
	set output \"./plot/graphs/plot.ps\"
	set xlabel 'Episode'
	set ylabel 'Total Accumulated Wins'
	plot x with lines linecolor rgb 'black' lt 1 notitle, x*0.5 with lines linecolor rgb 'black' lt 1 notitle, \
	 './black/result+black-3+white-10-10.dat' with lines linecolor rgb 'red' lt 1 lw 2 title 'UCT-Random', \
	 './black/result+black-3+white-10-13.dat' with lines linecolor rgb 'blue' lt 1 lw 2 title 'UCT-Heuristic', \
	 './black/result+black-3+white-10-20.dat' with lines linecolor rgb 'green' lt 1 lw 2 title 'UCT-Rave-Random', \
	 './black/result+black-3+white-10-23.dat' with lines linecolor rgb 'purple' lt 1 lw 2 title 'UCT-Rave-Heuristic'
	" | gnuplot
	convert -rotate 90 -flatten plot/graphs/plot.ps ~/Desktop/data/plot9.png

	name="Cumulative"
	echo "reset
	set term postscript
	set output \"./plot/graphs/plot.ps\"
	set xlabel 'Episode'
	set ylabel 'Total Accumulated Wins'
	plot x with lines linecolor rgb 'black' lt 1 notitle, x*0.5 with lines linecolor rgb 'black' lt 1 notitle, \
	 './black/result+black-0+white-5-10.dat' with lines linecolor rgb 'red' lt 1 lw 2 title 'UCT-Random', \
	 './black/result+black-0+white-5-13.dat' with lines linecolor rgb 'blue' lt 1 lw 2 title 'UCT-Heuristic', \
	 './black/result+black-0+white-5-20.dat' with lines linecolor rgb 'green' lt 1 lw 2 title 'UCT-Rave-Random', \
	 './black/result+black-0+white-5-23.dat' with lines linecolor rgb 'purple' lt 1 lw 2 title 'UCT-Rave-Heuristic'
	" | gnuplot
	convert -rotate 90 -flatten plot/graphs/plot.ps ~/Desktop/data/plot10.png

cd ../