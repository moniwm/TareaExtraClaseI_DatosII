#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "addvertex.h"
#include "deletevertex.h"
#include "addedge.h"
#include "deleteedge.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    AddVertex *addVertexWindow;
    DeleteVertex *deleteVertexWindow;
    AddEdge *addEdgeWindow;
    DeleteEdge *deleteEdgeWindow;

private slots:
    void on_btn_addVertex_clicked();

    void on_btn_addEdge_clicked();

    void on_btn_deleteVertex_clicked();

    void on_btn_deleteEdge_clicked();

    void on_btn_shortestPath_clicked();

    void refreshAdjacencyMatrix();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
