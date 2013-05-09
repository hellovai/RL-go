#!/bin/bash
outputfile="selfout.dat"
#number of games
game=100
#configuration
BasicBasic=false
BasicUct=true
UctUct=false
UctBasic=false
UctSelf=false
UctDif=false
#level associated
blacklevel=()
blacklist=(0)
whitelevel=(5)
whitelist=(10 13 20 23)
selflevel=(1 5)
selftype=(10 13 20 23)
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
				screen -d -m ./go -c1 -type $btype -level $blevel -c2 -type $wtype -g $game -output results/result+black-$blevel-$btype+white-$wtype.dat
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
				screen -d -m ./go -c1 -type $btype -c2 -type $wtype -level $wlevel -g $game -output results/result+black-$btype+white-$wlevel-$wtype.dat
			done
		done
	done
elif $BasicBasic ; then
	#basic vs basic
	for btype in ${blacklist[*]}
	do
		for wtype in ${whitelist[*]}
		do
			screen -d -m ./go -c1 -type $btype -c2 -type $wtype -g $game -output results/result+black-$btype+white-$wtype.dat >> $outputfile
		done
	done
elif $UctSelf ; then
	#basic vs basic
	for type in ${selftype[*]}
	do
		for level in ${selflevel[*]}
		do
			screen -d -m  ./go -c1 -type $type -level $level -c2 -type $type -level $level -g $game -output results/result+black-$level-$type+white-$level-$type.dat
		done
	done
elif $UctDif ; then
	#basic vs basic
	for btype in ${selftype[*]}
	do
		for wtype in ${selftype[*]}
		do
			if [[ $btype -ne $wtype ]];
			then
				for level in ${selflevel[*]}
				do
					screen -d -m  ./go -c1 -type $btype -level $level -c2 -type $wtype -level $level -g $game -output results/result+black-$level-$btype+white-$level-$wtype.dat
				done
			fi
		done
	done
fi