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

void DeleteVertex::on_btn_deleteVertexConfirm_clicked()
{
    std::string vertexName = ui->comboBox_VertexName->currentText().toStdString();
    this->close();
}

void DeleteVertex::getVertices(QStringList vertices){
    ui->comboBox_VertexName->addItems(vertices);
}

std::string DeleteVertex::getVertex(){
    return ui->comboBox_VertexName->currentText().toStdString();
}
