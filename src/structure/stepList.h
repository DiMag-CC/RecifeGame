#ifndef PHASE_LIST_H
#define PHASE_LIST_H

typedef struct Phase {
    int phaseNumber;
    char *phaseName;
    struct Phase *next;
    struct Phase *prev;
} Phase;

Phase* createPhase(int number, char *name);
void insertPhase(Phase **head, Phase *newPhase);
void nextPhase(Phase **currentPhase);
void previousPhase(Phase **currentPhase);

#endif