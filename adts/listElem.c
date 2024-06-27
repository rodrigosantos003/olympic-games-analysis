#include "listElem.h"
#include <stdio.h>

void listElemPrint(ListElem elem)
{
    printf("%-30s%-30s%-20s%c%c%c%-10s%-10s%-10s", elem.discipline, elem.game, elem.eventTitle, elem.gender, elem.medalType, elem.participantType, elem.athleteID, elem.country, elem.countryCode);
}