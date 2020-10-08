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

void DeleteEdge::on_btn_deleteEdgeConfirm_clicked()
{
    std::string startVertex = ui->comboBox_start->currentText().toStdString();
    std::string endVertex = ui->comboBox_end->currentText().toStdString();
    this->close();
}

void DeleteEdge::getVertices(QStringList vertices){

    ui->comboBox_start->addItems(vertices);
    ui->comboBox_end->addItems(vertices);
}

std::string DeleteEdge::getData(){

    std::string startVertex = ui->comboBox_start->currentText().toStdString();
    std::string endVertex = ui->comboBox_end->currentText().toStdString();

    return startVertex+endVertex;
}
