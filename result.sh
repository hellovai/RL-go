#!/bin/bash

cd results;
rm black/*
#gets easy result data
array=`wc -l result+* | grep "100 " | awk -F "100 " '{print $2}'`
for i in $array
do 
	ctr=0
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
		echo $ctr >> "black/$i"
	done < "$i"
	title=`echo $i | awk -F "result+" '{print $2}' | awk -F "." '{print $1}' | tr '-' ' ' | tr '+' ' '`

	echo "reset
	set term postscript
	set output \"./plot/graphs/$i.ps\"
	plot x with lines linecolor rgb 'blue' lt 1 notitle, x*0.5 with lines linecolor rgb 'blue' lt 1 notitle, './black/$i' with lines linecolor rgb 'red' lt 1 title '$title'" | gnuplot 
done

cd ../