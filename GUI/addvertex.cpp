#include "addvertex.h"
#include "ui_addvertex.h"

AddVertex::AddVertex(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddVertex)
{
    ui->setupUi(this);
}

AddVertex::~AddVertex()
{
    delete ui;
}

