default:
	gcc -Wall -o prog data_structures/athlete.c data_structures/medal.c data_structures/stringWrap.c data_structures/host.c  adts/mapElem.c adts/map.c features/topn.c features/loading.c features/input.c adts/list.c features/disciplines_analysis.c adts/listElem.c adts/set.c adts/setElem.c features/filter.c features/medals_analysis.c main.c
debug:
	gcc -Wall -o prog -g data_structures/athlete.c data_structures/medal.c data_structures/stringWrap.c data_structures/host.c  adts/mapElem.c adts/map.c features/topn.c features/loading.c features/input.c adts/list.c features/disciplines_analysis.c adts/listElem.c adts/set.c adts/setElem.c features/filter.c features/medals_analysis.c main.c
clean:
	rm -f prog
