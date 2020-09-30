#include "deletevertex.h"
#include "ui_deletevertex.h"

DeleteVertex::DeleteVertex(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteVertex)
{
    ui->setupUi(this);
}

DeleteVertex::~DeleteVertex()
{
    delete ui;
}
