#include <stdio.h>
#include "structure/stepList.h"

int main() {

    Phase *head = NULL;
    Phase *phase1 = createPhase(1, "Pedalando no Caos");
    insertPhase(&head, phase1);

    Phase *currentPhase = head;

    printf("Fase Atual: %s\n", currentPhase->phaseName);
    
    nextPhase(&currentPhase);
    printf("Próxima Fase: %s\n", currentPhase->phaseName);
    
    previousPhase(&currentPhase);
    printf("Fase Anterior: %s\n", currentPhase->phaseName);
    

    return 0;

}