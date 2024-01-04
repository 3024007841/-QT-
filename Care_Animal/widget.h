#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlQueryModel>
#include <QSqlTableModel>


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:

    void on_Pet_pushButton_clicked();

    void on_Adopters_pushButton_clicked();

    void on_history_pushButton_clicked();

    void switchPage();

    void on_addPet_pushButton_clicked();

    void on_addAdopter_pushButton_clicked();

    void on_cancel_pushButton_clicked();

    void on_add_pushButton_clicked();


    //void on_tableView_pressed(const QModelIndex &index);

private:
    Ui::Widget *ui;

    QSqlDatabase db= QSqlDatabase::addDatabase("QMYSQL");

    QSqlQueryModel *userMode_pet;//数据模型

    QSqlQueryModel *userMode_adopter;//数据模型

    QSqlQueryModel *userMode_history;//数据模型

    QSqlTableModel *m_sqlModel;


};
#endif // WIDGET_H
