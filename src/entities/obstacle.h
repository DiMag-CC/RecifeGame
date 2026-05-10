#ifndef OBSTACLE_H
#define OBSTACLE_H

typedef struct {
    int x;
    int y;
    int width;
    int height;
    int type;
    Color color;
} Obstacle;

Obstacle createObstacle(int x, int y, int width, int height);
void updateObstacle(Obstacle *obstacle);
void drawObstacle(Obstacle obstacle);

#endif