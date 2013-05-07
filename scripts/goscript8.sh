#!/bin/bash
outputfile="out8.dat"
#number of games
game=100
#configuration
BasicBasic=true
BasicUct=false
UctUct=false
UctBasic=false
#level associated
blacklevel=()
blacklist=(1 3)
whitelevel=()
whitelist=(1 3)

if $UctUct ; then
	#uct vs uct
	for blevel in ${blacklevel[*]}
	do
		for btype in ${blacklist[*]}
		do
			for wlevel in ${whitelevel[*]}
			do
				for wtype in ${whitelist[*]}
				do
					./go -c1 -type $btype -level $blevel -dump results/tree+black-$blevel-$btype+white-$wlevel-$wtype -c2 -type $wtype -level $wlevel -dump results/tree+white-$wlevel-$wtype+black-$blevel-$btype -g $game -output results/result+black-$blevel-$btype+white-$wlevel-$wtype.dat >> $outputfile
				done
			done
		done
	done
elif $UctBasic; then
	#uct vs basic
	for blevel in ${blacklevel[*]}
	do
		for btype in ${blacklist[*]}
		do
			for wtype in ${whitelist[*]}
			do
				./go -c1 -type $btype -level $blevel -dump results/tree+black-$blevel-$btype+white-$wtype -c2 -type $wtype -g $game -output results/result+black-$blevel-$btype+white-$wtype.dat    >> $outputfile
			done
		done
	done
elif $BasicUct; then
	#basic vs uct
	for wlevel in ${whitelevel[*]}
	do
		for btype in ${blacklist[*]}
		do
			for wtype in ${whitelist[*]}
			do
				./go -c1 -type $btype -c2 -type $wtype -level $wlevel -dump results/tree+white-$wlevel-$wtype+black-$btype -g $game -output results/result+black-$btype+white-$wlevel-$wtype.dat  >> $outputfile
			done
		done
	done
elif $BasicBasic ; then
	#basic vs basic
	for btype in ${blacklist[*]}
	do
		for wtype in ${whitelist[*]}
		do
			./go -c1 -type $btype -c2 -type $wtype -g $game -output results/result+black-$btype+white-$wtype.dat >> $outputfile
		done
	done
fi