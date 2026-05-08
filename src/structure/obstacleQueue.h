// obstacleQueue.h

#ifndef OBSTACLE_QUEUE_H
#define OBSTACLE_QUEUE_H

#include "../entities/obstacle.h"

typedef struct ObstacleNode {
    Obstacle obstacle;
    struct ObstacleNode *next;
} ObstacleNode;

typedef struct {
    ObstacleNode *front;
    ObstacleNode *rear;
} ObstacleQueue;

void initObstacleQueue(ObstacleQueue *queue);
int isObstacleQueueEmpty(ObstacleQueue *queue);
void enqueueObstacle(ObstacleQueue *queue, Obstacle obstacle);
void dequeueObstacle(ObstacleQueue *queue);
void freeObstacleQueue(ObstacleQueue *queue);

#endif