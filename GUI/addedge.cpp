#include "addedge.h"
#include "ui_addedge.h"

AddEdge::AddEdge(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddEdge)
{
    ui->setupUi(this);
}

AddEdge::~AddEdge()
{
    delete ui;
}
