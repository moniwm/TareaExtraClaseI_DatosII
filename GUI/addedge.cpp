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

void AddEdge::on_pushButton_clicked()
{
    this->close();
}

void AddEdge::getVertices(QStringList vertices){

    ui->comboBox_EndVertex->addItems(vertices);
    ui->comboBox_StartVertex->addItems(vertices);
}

std::string AddEdge::getData(){

    std::string startVertex = ui->comboBox_StartVertex->currentText().toStdString();
    std::string endVertex = ui->comboBox_EndVertex->currentText().toStdString();
    int cost = ui->spinBox_Cost->value();
    std::string strCost = std::to_string(cost);

    return startVertex+strCost+endVertex;
}
