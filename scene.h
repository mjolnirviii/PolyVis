#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include "polygon.h"

class Scene : public QGraphicsScene
{

public:
    Scene(QObject* parent = nullptr);

    void draw_polygon(int num_sides);
    void remove_polygon(int num_sides);
    void change_duration(double new_duration);

    QVector<Polygon*>& get_polygons();

private:
    QVector<Polygon*> polygons; // QList or QVec?

};

#endif // SCENE_H
