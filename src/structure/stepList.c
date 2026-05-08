#include <stdlib.h>
#include "stepList.h"

Phase *createPhase(int number, char *name) {
    Phase *newPhase = (Phase*)malloc(sizeof(Phase));
    if (!newPhase) return NULL;

    newPhase->phaseNumber = number;
    newPhase->phaseName = name;
    newPhase->prev = NULL;
    newPhase->next = NULL;

    return newPhase;
}

void insertPhase(Phase **head, Phase *newPhase) {
    if (*head == NULL) {
        *head = newPhase;
        newPhase->next = newPhase;
        newPhase->prev = newPhase;
    } else {
        Phase *last = (*head)->prev;
        newPhase->next = *head;
        (*head)->prev = newPhase;
        newPhase->prev = last;
        last->next = newPhase;
    }
}

void nextPhase(Phase **currentPhase) {
    *currentPhase = (*currentPhase)->next;
}

void previousPhase(Phase **currentPhase) {
    *currentPhase = (*currentPhase)->prev;
}