#include "add_form.h"
#include "ui_add_form.h"


add_Form::add_Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::add_Form)
{
    ui->setupUi(this);

    setWindowTitle("小可爱来了！");

    QStringList items_age;
    for(int i=1; i<=20; i++){
        items_age << QString::number(i);
    }
    ui->age_comboBox->addItems(items_age);


}

add_Form::~add_Form()
{
    delete ui;
}

void add_Form::on_cancel_pushButton_clicked()
{
    close();
}


void add_Form::on_add_pushButton_clicked()
{
    QString name = ui->name_lineEdit->text();
    QString status = ui->status_lineEdit->text();
    QString habits = ui->habits_lineEdit->text();
    QString age = ui->age_comboBox->currentText();
    QString variety = ui->variety_lineEdit->text();

    QSqlQuery query;
    QString str1 = "'" + name +"','" + variety + "','" + age +"','"+ status + "','" + habits + "'";
    QString str = "insert into `pet`(`宠物`, `品种`, `年龄`, `身体状况`, `爱好`) values(" + str1 + ");";

    bool success = query.exec(str); // 执行插入操作
    if(success)
    {
        qDebug() << "插入成功";
        close();



    }
    else
    {
        qDebug() << "插入失败：" << query.lastError().text();
    }


}



