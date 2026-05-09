#include <stdlib.h>
#include "obstacleQueue.h"

void initObstacleQueue(ObstacleQueue *queue) {
    queue->front = NULL;
    queue->rear = NULL;
}

int isObstacleQueueEmpty(ObstacleQueue *queue) {
    return (queue->front == NULL);
}

void enqueueObstacle(ObstacleQueue *queue, Obstacle obstacle) {
    ObstacleNode *newNode = (ObstacleNode*)malloc(sizeof(ObstacleNode));
    newNode->obstacle = obstacle;
    newNode->next = NULL;

    if (isObstacleQueueEmpty(queue)) {
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

void dequeueObstacle(ObstacleQueue *queue) {
    if (!isObstacleQueueEmpty(queue)) {
        ObstacleNode *tmp = queue->front;
        queue->front = queue->front->next;
        free(tmp);

        if (queue->front == NULL) {
            queue->rear = NULL;
        }
    }
}

void freeObstacleQueue(ObstacleQueue *queue) {
    while (!isObstacleQueueEmpty(queue)) {
        dequeueObstacle(queue);
    }
}