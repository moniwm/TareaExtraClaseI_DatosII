#ifndef DELETEEDGE_H
#define DELETEEDGE_H

#include <QDialog>

namespace Ui {
class DeleteEdge;
}

class DeleteEdge : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteEdge(QWidget *parent = nullptr);
    ~DeleteEdge();
    std::string getData();
    void getVertices(QStringList vertices);

private slots:
    void on_btn_deleteEdgeConfirm_clicked();

private:
    Ui::DeleteEdge *ui;
};

#endif // DELETEEDGE_H
