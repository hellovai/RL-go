#!/bin/bash

#number of games
game=100
#configuration
BasicBasic=true
BasicUct=false
UctUct=false
UctBasic=false
#level associated
blacklevel=()
blacklist=(0 3)
whitelevel=()
whitelist=(0 3)

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
					./go -c1 -type $btype -level $blevel -dump results/tree-black-$blevel-$btype -c2 -type $wtype -level $wblevel -dump results/tree-white-$wlevel-$wtype -g $game -output results/black_$blevel-$btype-white_$wlevel-$wtype.dat   
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
				./go -c1 -type $btype -level $blevel -dump results/tree-black-$blevel-$btype -c2 -type $wtype -g $game -output results/black_$blevel-$btype-white_$wtype.dat   
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
				./go -c1 -type $btype -c2 -type $wtype -level $wblevel -dump results/tree-white-$wlevel-$wtype -g $game -output results/black_$blevel-$btype-white_$wtype.dat   
			done
		done
	done
elif $BasicBasic ; then
	#basic vs basic
	echo "TRUE"
	for btype in ${blacklist[*]}
	do
		for wtype in ${whitelist[*]}
		do
			./go -c1 -type $btype -c2 -type $wtype -g $game -output results/black_$btype-white_$wtype.dat   
		done
	done
fi