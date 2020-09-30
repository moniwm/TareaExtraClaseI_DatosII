#include "deleteedge.h"
#include "ui_deleteedge.h"

DeleteEdge::DeleteEdge(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteEdge)
{
    ui->setupUi(this);
}

DeleteEdge::~DeleteEdge()
{
    delete ui;
}
