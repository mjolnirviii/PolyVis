#include "polygon.h"

// https://stackoverflow.com/questions/30002249/undefined-reference-to-static-const-member-in-g-if-no-using-code-is-linked
QSet<QRgb> Polygon::color_set;
QVector<int> Polygon::sides_list;

void Polygon::create_points(){

    //algorithm to add points to create any shape, depending on num_sides

    for(int n = 0; n < num_sides; n++){
        double x = radius * qCos(2*M_PI*n / num_sides) + x_pos;
        double y = radius * qSin(2*M_PI*n / num_sides) + y_pos;

        points << QPointF(x,y);
    }

}

float Polygon::background_color_diff(){
    // Background color: QColor(ARGB 1, 0.117647, 0.117647, 0.117647), found through QWidget::palette().color(QWidget::backgroundRole())
    float diff_red = qFabs(color.redF() - 0.117647);
    float diff_green = qFabs(color.greenF() - 0.117647);
    float diff_blue = qFabs(color.blueF() - 0.117647);

    float avg_diff = (diff_red + diff_green + diff_blue) / 3;
    return avg_diff;
}

QRectF Polygon::boundingRect() const
{
    return points.boundingRect();
}

void Polygon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(color);
    painter->drawPolygon(points);
}

// is radius even needed in constructor????

Polygon::Polygon(int num_sides, double radius, double x_pos, double y_pos, QGraphicsItem* parent)
    // random color with qrandgen (see doc)    QRandomGenerator::global()->bounded(256) 3 times or QColor::fromRgb(QRandomGenerator::global()->generate());
    : num_sides(num_sides), radius(radius), x_pos(x_pos), y_pos(y_pos), color(QColor::fromRgb(QRandomGenerator::global()->generate())), QGraphicsItem(parent){

    // make sure color unique AND isn't too close to background
    // https://stackoverflow.com/questions/9018016/how-to-compare-two-colors-for-similarity-difference
    while(color_set.contains(color.rgb()) || background_color_diff() <= 0.2){  // 0.2?? idk
        color = QColor::fromRgb(QRandomGenerator::global()->generate());
    }
    color_set << color.rgb();

    // make sure sides list is in order small to big
    if(sides_list.isEmpty() || num_sides > sides_list.back()){
        sides_list << num_sides; // other classes makes sure no repeats
        init_list_pos = sides_list.size()-1;
    }
    else{
        for(int i = 0; i < sides_list.size(); i++){
            if(num_sides < sides_list.at(i)){
                sides_list.insert(i, num_sides);
                init_list_pos = i;
                break;
            }
        }
    }

    this->radius = (init_list_pos + 1) * 50; // maybe make 50 a const ex SPACING or some shit
    //update();
    create_points();

    ball = new RhythmBall(points, 5, this); // constant x radius ball?
}


QPolygonF Polygon::get_points(){
    return points;
}

QColor Polygon::get_color(){
    return color;
}

int Polygon::get_init_list_pos(){
    return init_list_pos;
}

double Polygon::get_radius(){
    return radius;
}

RhythmBall* Polygon::get_ball(){
    return ball;
}

void Polygon::scale_polygon(double new_radius){
    prepareGeometryChange(); // Need this
    points.clear();
    radius = new_radius;
    create_points();
    ball->update_moving();
}
