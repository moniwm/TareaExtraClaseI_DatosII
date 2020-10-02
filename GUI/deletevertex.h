#ifndef DELETEVERTEX_H
#define DELETEVERTEX_H

#include <QDialog>

namespace Ui {
class DeleteVertex;
}

class DeleteVertex : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteVertex(QWidget *parent = nullptr);
    ~DeleteVertex();

private slots:
    void on_btn_deleteVertexConfirm_clicked();

private:
    Ui::DeleteVertex *ui;
};

#endif // DELETEVERTEX_H
