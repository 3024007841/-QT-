#include "widget.h"
#include "ui_widget.h"
#include "add_form.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //增加按钮图标        这里也可以自己去找图标
    ui->Pet_pushButton->setIcon(QIcon(":/pet.svg"));
    ui->Pet_pushButton->setIconSize(QSize(20, 20)); // 调整图标大小

    ui->Adopters_pushButton->setIcon(QIcon(":/adopter.svg"));
    ui->Adopters_pushButton->setIconSize(QSize(20, 20));

    ui->history_pushButton->setIcon(QIcon(":/history.svg"));
    ui->history_pushButton->setIconSize(QSize(20, 20));



    //连接并打开数据库
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("care_animals");//数据库名称
    db.setUserName("*****");//用户名
    db.setPassword("********");//密码



    qDebug()<<"available drivers:"; //显示可用驱动
    QStringList drivers = QSqlDatabase::drivers();
    for(auto &driver: drivers)
        qDebug() << driver;
    db.open();
    /*if(ok) 测试代码
    {
        QMessageBox::information(this, "提示","数据库连接成功");
        qDebug()<<"数据库连接成功";
    }
    else
    {
        QMessageBox::information(this, "提示","数据库连接失败");
        this->close();
        qDebug()<<"数据库连接失败";
    }*/


    // 设置编辑策略为双击行触发
    //connect(ui->pet_tableView, &QTableView::pressed, this, &Widget::on_tableView_pressed);



    setWindowTitle("Care_animals");


    //换页功能
    connect(ui->Pet_pushButton,&QPushButton::clicked,this,&Widget::switchPage);
    connect(ui->Adopters_pushButton,&QPushButton::clicked,this,&Widget::switchPage);
    connect(ui->history_pushButton,&QPushButton::clicked,this,&Widget::switchPage);


    userMode_pet = new QSqlQueryModel(ui->pet_tableView);//绑定

    userMode_adopter = new QSqlQueryModel(ui->adopter_tableView);

    userMode_history = new QSqlQueryModel(ui->history_tableView);


}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_Pet_pushButton_clicked()
{
    userMode_pet->setQuery("select * from pet;");
    // 设置列的自适应大小模式为根据内容自动调整

    ui->pet_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    // 设置最小行的大小
    ui->pet_tableView->horizontalHeader()->setMinimumSectionSize(100);

    userMode_pet->setHeaderData(0,Qt::Horizontal,tr("宠物名"));
    userMode_pet->setHeaderData(1,Qt::Horizontal,tr("品种"));
    userMode_pet->setHeaderData(2,Qt::Horizontal,tr("年龄"));
    userMode_pet->setHeaderData(3,Qt::Horizontal,tr("身体状况"));
    userMode_pet->setHeaderData(4,Qt::Horizontal,tr("爱好"));
    ui->pet_tableView->setModel(userMode_pet);
}


void Widget::on_Adopters_pushButton_clicked()
{

    userMode_adopter->setQuery("select * from adopter;");
    // 设置列的自适应大小模式为根据内容自动调整

    ui->adopter_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    // 设置最小行的大小
    ui->adopter_tableView->horizontalHeader()->setMinimumSectionSize(100);

    userMode_adopter->setHeaderData(0,Qt::Horizontal,tr("名字"));
    userMode_adopter->setHeaderData(1,Qt::Horizontal,tr("宠物"));
    userMode_adopter->setHeaderData(2,Qt::Horizontal,tr("手机号码"));
    userMode_adopter->setHeaderData(3,Qt::Horizontal,tr("家庭住址"));
    userMode_adopter->setHeaderData(4,Qt::Horizontal,tr("生活状况"));
    ui->adopter_tableView->setModel(userMode_adopter);
}


void Widget::on_history_pushButton_clicked()
{
    userMode_history->setQuery("select * from history;");
    // 设置列的自适应大小模式为根据内容自动调整

    ui->history_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    // 设置最小行的大小
    ui->history_tableView->horizontalHeader()->setMinimumSectionSize(100);

    userMode_history->setHeaderData(0,Qt::Horizontal,tr("领养者"));
    userMode_history->setHeaderData(1,Qt::Horizontal,tr("宠物"));
    userMode_history->setHeaderData(2,Qt::Horizontal,tr("领养时间"));
    userMode_history->setHeaderData(3,Qt::Horizontal,tr("签订协议"));
    ui->history_tableView->setModel(userMode_history);
}

void Widget::switchPage()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if(button==ui->Pet_pushButton)
        ui->stackedWidget->setCurrentIndex(0);
    else if(button==ui->Adopters_pushButton)
        ui->stackedWidget->setCurrentIndex(1);
    else if(button==ui->history_pushButton)
        ui->stackedWidget->setCurrentIndex(2);
}





void Widget::on_addPet_pushButton_clicked()
{
    add_Form *f = new add_Form;
    f->show();
}


void Widget::on_addAdopter_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void Widget::on_cancel_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void Widget::on_add_pushButton_clicked()
{
    QString name = ui->name_lineEdit->text();
    QString pet = ui->pet_lineEdit->text();
    QString number = ui->number_lineEdit->text();
    QString aggreement = ui->agreement_lineEdit->text();
    QString address = ui->address_textEdit->toPlainText();
    QString status = ui->status_textEdit->toPlainText();

    QSqlQuery query;
    QString str1 = "'" + name +"','" + pet + "','" + number +"','"+ address + "','" + status + "','" + aggreement + "'";
    QString str = "insert into `adopter`(`名字`, `宠物`, `手机号码`, `家庭地址`, `生活状况`, `签订协议`) values(" + str1 + ");";

    bool success = query.exec(str); // 执行插入操作
    if(success)
    {
        qDebug() << "插入成功";
        ui->stackedWidget->setCurrentIndex(1);


    }
    else
    {
        qDebug() << "插入失败：" << query.lastError().text();
    }
}





/* 未实现的双击点击表格修改数据功能
void Widget::on_tableView_pressed(const QModelIndex &index)
{
    add_Form *f = new add_Form;

    QString name = userMode_pet->data(userMode_pet->index(index.row(), 0)).toString();
    QString age = userMode_pet->data(userMode_pet->index(index.row(), 1)).toString();
    int variety = userMode_pet->data(userMode_pet->index(index.row() , 2));
    QString status = userMode_pet->data(userMode_pet->index(index.row(), 3)).toString();
    QString habits = userMode_pet->data(userMode_pet->index(index.row(), 4)).toString();

    f->setFields(name, variety, age, status , habits);

    f->show();
}
*/
