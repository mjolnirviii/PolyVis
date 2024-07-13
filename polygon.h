#ifndef POLYGON_H
#define POLYGON_H

#include <QRectF>
#include <QColor>
#include <QRgb>
#include <QRandomGenerator>
#include <QSet>
#include "rhythmball.h"

class Polygon : public QGraphicsItem    // instead of QGraphicsPolygon?
{
public:
    Polygon(int num_sides, double radius = 1, double x_pos = 0, double y_pos = 0, QGraphicsItem *parent = nullptr);

    static QVector<int> sides_list; // widget/scene access, ordered from small to big

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    QPolygonF get_points();
    QColor get_color();
    double get_radius();
    void scale_polygon(double new_radius);
    int get_init_list_pos();
    RhythmBall* get_ball();

private:
    RhythmBall* ball;

    int num_sides; // use qint32 or those versions?
    double radius;
    double x_pos;
    double y_pos;
    QPolygonF points;
    QColor color;
    // static because want all classes to know which colors/shapes taken
    static QSet<QRgb> color_set;
    int init_list_pos; // dumb variable thats only used once, used by scene, is there a better way?

    // default radius is 1, can scale later
    void create_points(); // calls in constructor to make list of points
    float background_color_diff();

};

#endif // POLYGON_H
