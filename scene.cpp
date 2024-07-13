#include "scene.h"

Scene::Scene(QObject* parent) : QGraphicsScene(parent) {

    Sound::initialize_audio_format(); // put here because constructor looked empty

}

QVector<Polygon*>& Scene::get_polygons(){        // do i need this
    return polygons;
}

void Scene::draw_polygon(int num_sides){
    Polygon* new_polygon = new Polygon(num_sides);

    // put polygon in right place, if insert in some middle position have to scale the rest that come after it
    qDebug() << Polygon::sides_list;

    polygons.insert(new_polygon->get_init_list_pos(), new_polygon); // polygons and sides_list are parallel vectors
    //addPolygon(new_polygon->get_points()); BRUH doesn't work, used addItem instead
    addItem(new_polygon);

    qDebug() << "Radius:" << new_polygon->get_radius();

    for(int i = new_polygon->get_init_list_pos() + 1; i < polygons.size(); i++){
        qDebug() << "Resize shape at index" << i;
        polygons.at(i)->scale_polygon((i+1) * 50);
    }
}

void Scene::remove_polygon(int num_sides){
    int remove_index = Polygon::sides_list.indexOf(num_sides);
    Polygon::sides_list.removeAt(remove_index); // should sides_list be modifiable from outside class like this???
    qDebug() << Polygon::sides_list;

    removeItem(polygons.at(remove_index));
    polygons.at(remove_index)->get_ball()->remove_anim();
    polygons.removeAt(remove_index);

    for(int i = remove_index; i < polygons.size(); i++){
        qDebug() << "Resize shape at index" << i;
        polygons.at(i)->scale_polygon((i+1) * 50);
    }
}

void Scene::change_duration(double new_duration){
    RhythmBall::duration = new_duration;
    for(int i = 0; i < polygons.size(); i++){
        polygons.at(i)->get_ball()->update_duration();
    }
}
