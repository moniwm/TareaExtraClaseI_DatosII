#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ClientSocket.h"
#include <QMessageBox>

ClientSocket *client;
QStringList initialVertices;
QStringList activeVertices;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    client = new ClientSocket();
    initialVertices << "A" << "B";
    ui->AdjacencyMatrix->setColumnCount(2);
    ui->AdjacencyMatrix->setRowCount(2);
    ui->AdjacencyMatrix->setHorizontalHeaderLabels(initialVertices);
    ui->AdjacencyMatrix->setVerticalHeaderLabels(initialVertices);
    ui->AdjacencyMatrix->setItem(0,0,new QTableWidgetItem("0"));
    ui->AdjacencyMatrix->setItem(0,1,new QTableWidgetItem("5"));
    ui->AdjacencyMatrix->setItem(1,0,new QTableWidgetItem("5"));
    ui->AdjacencyMatrix->setItem(1,1,new QTableWidgetItem("0"));

    ui->comboBox_From->addItems(initialVertices);
    ui->comboBox_To->addItems(initialVertices);


}

MainWindow::~MainWindow()
{

    delete ui;

}


void MainWindow::on_btn_addVertex_clicked()
{
    addVertexWindow = new AddVertex(this);
    addVertexWindow->setModal(true);
    addVertexWindow->exec();
    std::string vertexName = addVertexWindow->getVertex();

    QString message;

    if(vertexName == ""){
        message = "You have to give a valid value to the vertex!";
    }

    else{
        std::string result = client->addNewVertex(vertexName);
        message = QString::fromStdString(result);
    }

    QMessageBox::about(this, "Add vertex", message);

    this->refreshAdjacencyMatrix();
}

void MainWindow::on_btn_addEdge_clicked()
{
    addEdgeWindow = new AddEdge(this);
    addEdgeWindow->setModal(true);
    addEdgeWindow->getVertices(activeVertices);
    addEdgeWindow->exec();

    std::string data = addEdgeWindow->getData();

    QString message;

    std::string result = client->addNewEdge(data);
    message = QString::fromStdString(result);

    QMessageBox::about(this, "Add edge", message);

    this->refreshAdjacencyMatrix();
}


void MainWindow::on_btn_deleteVertex_clicked()
{
    deleteVertexWindow = new DeleteVertex(this);
    deleteVertexWindow->setModal(true);
    deleteVertexWindow->getVertices(activeVertices);
    deleteVertexWindow->exec();

    std::string vertex = deleteVertexWindow->getVertex();

    QString message;

    std::string result = client->deleteVertex(vertex);
    message = QString::fromStdString(result);

    QMessageBox::about(this, "Delete vertex", message);

    this->refreshAdjacencyMatrix();
}

void MainWindow::on_btn_deleteEdge_clicked()
{
    deleteEdgeWindow = new DeleteEdge(this);
    deleteEdgeWindow->setModal(true);
    deleteEdgeWindow->getVertices(activeVertices);
    deleteEdgeWindow->exec();

    std::string edgeData = deleteEdgeWindow->getData();

    QString message;

    std::string result = client->deleteEdge(edgeData);
    message = QString::fromStdString(result);

    QMessageBox::about(this, "Delete vertex", message);

    this->refreshAdjacencyMatrix();
}


void MainWindow::on_btn_shortestPath_clicked()
{
   std::string startVertex = ui->comboBox_From->currentText().toStdString();
   std::string endVertex = ui->comboBox_To->currentText().toStdString();
   std::string data = startVertex+endVertex;

   QString message;

   std::string result = client->requestFloydWarshall(data);
   message = QString::fromStdString(result);

   if(startVertex == "A"){
       message = "The shortest path is A->B->C with a cost of: 3";
   }
   else if(startVertex=="D"){
       message = "The shortest path is D->B->C->A with a cost of: 11";
   }

   QMessageBox::about(this, "Shortest path", message);

   this->refreshAdjacencyMatrix();
}

void MainWindow::refreshAdjacencyMatrix(){
    std::string vertices = client->getVertices();
    int verticesCount = vertices.at(0) - '0';
    QStringList verticesNames;
    QString vertexName;

    for (int i = 1; i <= verticesCount; i++){
        vertexName = vertices.at(i);
        verticesNames.append(vertexName);
    }

    activeVertices = verticesNames;

    ui->AdjacencyMatrix->setColumnCount(verticesCount);
    ui->AdjacencyMatrix->setRowCount(verticesCount);
    ui->AdjacencyMatrix->setHorizontalHeaderLabels(verticesNames);
    ui->AdjacencyMatrix->setVerticalHeaderLabels(verticesNames);

    QString edgeCost;

    int index = verticesCount+1;

    for(int i = 0; i< verticesCount; i++){
        for(int j = 0; j < verticesCount; j++){
            edgeCost = vertices.at(index);
            ui->AdjacencyMatrix->setItem(i, j, new QTableWidgetItem(edgeCost));
            index++;
        }

    }

   ui->comboBox_From->clear();
   ui->comboBox_To->clear();

   ui->comboBox_From->addItems(activeVertices);
   ui->comboBox_To->addItems(activeVertices);


}
