#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ClientSocket.h"
#include <QMessageBox>

ClientSocket *client;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    client = new ClientSocket();

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

    std::string vertices = client->getVertices();
    QString strVertices = QString::fromStdString(vertices);

    QMessageBox::about(this, "Vertices", strVertices);

    this->refreshAdjacencyMatrix();
}

void MainWindow::on_btn_addEdge_clicked()
{
    addEdgeWindow = new AddEdge(this);
    addEdgeWindow->setModal(true);
    addEdgeWindow->exec();
    client->addNewEdge();


}

void MainWindow::on_btn_deleteVertex_clicked()
{
    deleteVertexWindow = new DeleteVertex(this);
    deleteVertexWindow->setModal(true);
    deleteVertexWindow->exec();
    client->deleteVertex();
}

void MainWindow::on_btn_deleteEdge_clicked()
{
    deleteEdgeWindow = new DeleteEdge(this);
    deleteEdgeWindow->setModal(true);
    deleteEdgeWindow->exec();
    client->deleteEdge();
}


void MainWindow::on_btn_shortestPath_clicked()
{
    client->requestFloydWarshall();
}

void MainWindow::refreshAdjacencyMatrix(){
    std::string vertices = client->getVertices();
    int verticesCount = vertices.size();
    QStringList verticesNames;
    QString vertexName;

    for (int i = 0; i < verticesCount; i++){
        vertexName = vertices.at(i);
        verticesNames.append(vertexName);

    }

    ui->AdjacencyMatrix->setColumnCount(verticesCount);
    ui->AdjacencyMatrix->setRowCount(verticesCount);
    ui->AdjacencyMatrix->setHorizontalHeaderLabels(verticesNames);
    ui->AdjacencyMatrix->setVerticalHeaderLabels(verticesNames);

}
