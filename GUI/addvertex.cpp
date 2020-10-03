#include "addvertex.h"
#include "ui_addvertex.h"
#include <iostream>
#include <QMessageBox>

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


void AddVertex::on_btn_AddNewVertex_clicked()
{
    std::string vertexName = this->getVertex();
    if(vertexName == ""){
        QMessageBox::about(this, "Error adding vertex", "You have to give a valid value to the new vertex!");
    }
    this->close();

}

std::string AddVertex::getVertex(){
    return ui->lineEdit_VertexName->text().toStdString();
}
