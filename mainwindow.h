#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "scene.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void add_shape_clicked();
    void remove_shape_clicked();
    void num_sides_changed(int sides);
    void duration_changed(double duration);

private:
    Ui::MainWindow *ui;

    Scene* scene;
    int num_sides_chosen;

};
#endif // MAINWINDOW_H
