#include "rhythmball.h"

// doing same thing as I did with static in polygon.cpp
QParallelAnimationGroup* RhythmBall::anim_group = new QParallelAnimationGroup();
double RhythmBall::duration = 3.00;

qreal g_offset = 0;
qreal g_offset_last = 0;

// bool can_clear = true;
// Emitter emitter;

QRectF RhythmBall::boundingRect() const{
    return QRectF(pos.x()-radius, pos.y()-radius, radius*2, radius*2);
}

void RhythmBall::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->setBrush(Qt::red);
    painter->drawEllipse(pos.x()-radius, pos.y()-radius, radius*2, radius*2);
}

void RhythmBall::set_anim_path(){
    double key_percent = 1.0 / points.size();
    for(int i = 0; i < points.size(); i++){
        move_anim->setKeyValueAt(i * key_percent, points.at(i));
    }
    move_anim->setKeyValueAt(1, points.at(0)); // last move is back to start
}

void RhythmBall::start_moving(){ // maybe add a parameter "start" later on and make public
    move_anim->setDuration(duration*1000); // must be in millisec
    set_anim_path();

    QEasingCurve custom_easing;
    custom_easing.setCustomType(myEasingFunction);
    move_anim->setEasingCurve(custom_easing);

    if(anim_group->state() == QAbstractAnimation::Stopped){ // this replaces need for anim_count, only runs once
        anim_group->setLoopCount(-1); // run infinitely
        anim_group->addAnimation(move_anim);
        anim_group->start();
    }
    else{
        anim_group->pause();
        anim_group->addAnimation(move_anim);
        anim_group->resume();
    }
}

void RhythmBall::update_moving(){
    anim_group->pause();
    set_anim_path();
    anim_group->resume();
}

void RhythmBall::update_duration(){
    g_offset = g_offset_last;
    anim_group->stop(); // pause resume doesnt work, has to be stop start
    move_anim->setDuration(duration*1000);
    anim_group->start();
}

// Big credits to Serhiy https://stackoverflow.com/questions/55526530/change-qpropertyanimation-duration-on-the-fly
// idk how the hell "saving" of progress works
qreal myEasingFunction(qreal progress)    // has to be non member function
{
    //qDebug() << "progress:" << progress;
    //qDebug() << "g_offset:" << g_offset;
    qreal val = g_offset + progress;                // THIS is the "TRUE" progress (1 is start of new loop, complete)
    // if(val >= 1 && can_clear){
    //     qDebug() << "Cleared visited set";
    //     can_clear = false;
    //     emit emitter.signal_clear();
    // }
    //qDebug() << "val (before normalize):" << val;
    while (val > 1) {
        val -= 1;  //normalize
    }
    g_offset_last = val;
    //qDebug() << "g_offset_last / val (after normalize):" << g_offset_last;
    return val;
}

RhythmBall::RhythmBall(QPolygonF& points, double radius, QGraphicsItem* parent)
    : points(points), radius(radius), pos(points.at(0)), move_anim(new QPropertyAnimation(this, "pos")),
    can_clear(true), ball_sound(new Sound(points.size())), QGraphicsItem(parent) {

    //qDebug() << "Points:" << points;
    // connect(anim_group, SIGNAL(currentLoopChanged(int)), this, SLOT(reset_clear())); // set can_clear to true, im assuming that "progress" determines this
    // connect(&emitter, SIGNAL(signal_clear()), this, SLOT(clear_visited()));
    start_moving();

}

void RhythmBall::remove_anim(){
    anim_group->removeAnimation(move_anim);
}

QPointF RhythmBall::get_pos(){
    return pos;
}

bool RhythmBall::is_near(QPointF point, qreal tolerance){
    qreal x_diff = pos.x() - point.x();
    qreal y_diff = pos.y() - point.y();

    return qSqrt(x_diff*x_diff + y_diff*y_diff) <= tolerance;
}

void RhythmBall::set_pos(QPointF new_pos){
    prepareGeometryChange();
    pos = new_pos;

    if(is_near(points.at(0), 2) && can_clear){
        //qDebug() << "Cleared visited set";
        visited_points.clear();
        can_clear = false;
    }
    else if(is_near(points.at(1), 2)){       // reset can_clear at the next point (assured that polygon 2+ points)
        //qDebug() << "Reset can_clear";
        can_clear = true;
    }

    for(int i = 0; i < points.size(); i++){
        if(is_near(points.at(i), 2) && !visited_points.contains(points.at(i))){  // seems like 2 does the trick, if not misses (test bigger vals)
            qDebug() << points.size() << "sided polygon passed point #" << i;
            visited_points << points.at(i);
        }
    }
}
