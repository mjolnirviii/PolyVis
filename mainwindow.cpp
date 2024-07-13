#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : scene(new Scene(this)), num_sides_chosen(2), QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("PolyVis");

    // create scene where stuff shows up
    // scene = new Scene(this); move to initializer list
    ui->graphicsView->setScene(scene);

    ui->add_shape_button->setText("Add shape");
    ui->remove_shape_button->setText("Remove shape");
    ui->shape_label->setText("Number of sides");
    ui->duration_label->setText("Cycle duration (s)");
    ui->shape_spinbox->setMinimum(2);
    ui->duration_spinbox->setValue(3); // starting value?
    ui->duration_spinbox->setSingleStep(0.1);

    // connect signals from ui stuff to slots
    // Syntax: connect(sender, SIGNAL(destroyed()), this, SLOT(objectDestroyed()));
    connect(ui->add_shape_button, SIGNAL(clicked()), this, SLOT(add_shape_clicked()));
    connect(ui->remove_shape_button, SIGNAL(clicked()), this, SLOT(remove_shape_clicked()));
    connect(ui->shape_spinbox, SIGNAL(valueChanged(int)), this, SLOT(num_sides_changed(int))); // if has params just put type
    connect(ui->duration_spinbox, SIGNAL(valueChanged(double)), this, SLOT(duration_changed(double)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

// slots
void MainWindow::add_shape_clicked()
{
    qDebug() << "Add shape clicked";

    if(!Polygon::sides_list.contains(num_sides_chosen)){
        qDebug() << num_sides_chosen << "sided polygon was added to scene";
        scene->draw_polygon(num_sides_chosen);
    }
}

void MainWindow::remove_shape_clicked()
{
    qDebug() << "Remove shape clicked";

    if(Polygon::sides_list.contains(num_sides_chosen)){
        qDebug() << num_sides_chosen << "sided polygon was removed from scene";
        scene->remove_polygon(num_sides_chosen);
    }
}

void MainWindow::num_sides_changed(int sides)
{
    qDebug() << "Value changed to" << sides;

    num_sides_chosen = sides;
}

void MainWindow::duration_changed(double duration){
    scene->change_duration(duration);
}

