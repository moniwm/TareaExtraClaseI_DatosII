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
    std::string startVertex = ui->comboBox_StartVertex->currentText().toStdString();
    std::string endVertex = ui->comboBox_EndVertex->currentText().toStdString();
    int cost = ui->spinBox_Cost->value();
    this->close();
}
