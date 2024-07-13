#ifndef RHYTHMBALL_H
#define RHYTHMBALL_H

#include <QGraphicsItem>
#include <QPointF>
#include <QPainter>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QEasingCurve>
#include <QVector>
#include "sound.h"

qreal myEasingFunction(qreal progress);

// inherit QObject too for animation
class RhythmBall : public QObject, public QGraphicsItem // instead of QGraphicsEllipse?
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ get_pos WRITE set_pos)

public:
    RhythmBall(QPolygonF& points, double radius, QGraphicsItem* parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    // static int anim_count; // ugly like polygon list, could make destructor instead
    static double duration; // time to go to all points back to start
    void update_moving();
    void update_duration();
    void remove_anim();

// private slots:
//     void clear_visited();
//     void reset_clear();

private:
    double radius;
    // double x_pos;
    // double y_pos;   instead below
    QPointF pos;
    QPolygonF& points;
    Sound* ball_sound;

    static QParallelAnimationGroup* anim_group;
    QPropertyAnimation* move_anim;

    QPointF get_pos();
    void set_pos(QPointF new_pos);
    bool is_near(QPointF point, qreal tolerance);
    QVector<QPointF> visited_points; // prevent triggering passing more than once
    bool can_clear; //put back in constructor if needed again

    void set_anim_path(); // start and update moving are same pretty much, dont want to think too much rn about making only 1 func
    void start_moving(); // maybe add a parameter "start" later on and make public

};

#endif // RHYTHMBALL_H
