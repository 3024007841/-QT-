#ifndef ADD_FORM_H
#define ADD_FORM_H

#include <QWidget>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlQueryModel>
#include <QSqlError>


namespace Ui {
class add_Form;
}

class add_Form : public QWidget
{
    Q_OBJECT

public:
    explicit add_Form(QWidget *parent = nullptr);
    ~add_Form();

public slots:

private slots:
    void on_cancel_pushButton_clicked();

    void on_add_pushButton_clicked();

private:
    Ui::add_Form *ui;
};

#endif // ADD_FORM_H
