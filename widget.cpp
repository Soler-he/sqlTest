#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include <QStringList>


#include <QtSql/QSqlDatabase>
#include <QLabel>
#include <QDir>
#include <QSqlQuery>
#include <QTableView>
#include <QSqlTableModel>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);


    //实例QLabel
    QLabel *label = new QLabel(this);
    label->setGeometry(QRect(50,50,200,25));
    //注意数据库路径
    this->setWindowTitle(QDir::currentPath());
    //判断数据库文件是否存在
    bool dbFile = !QFile::exists(QDir::currentPath()+"/db.db");

    if(connection())
    {
        //label->setText("连接成功");
        //打开数据库，判断是否连接成功
        if(dbFile)
        {
            label->setText("不存在创建");
            //创建
            createDB();
            //绑定数据
            bindData();
        }
        else
        {
            //label->setText("存在");
            //绑定数据
            bindData();
        }

    //关闭数据库
    db.close();
    }
    else
    {
        label->setText("连接失败");
    }

}

//测试连接
bool Widget::connection()
{
    //实例QSqlDatabase
    db = QSqlDatabase::addDatabase("QSQLITE");
    //数据库名称
    db.setDatabaseName("db.db");
    //判断是否可以打开

    if(!db.open())
    {
        return false;
    }

    return true;
}

//创建数据库
void Widget::createDB()
{
//实例QSqlQuery

    QSqlQuery query;
    //用SQL命令创建表，与Access一样
    //表名：person
    //id:自增，主键
    //name:存人名称
    //time：时间自动添加
    query.exec("CREATE TABLE person ("
    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
    "name VARCHAR(50) NOT NULL, "
    "time TIMESTAMP default CURRENT_TIMESTAMP)");
    //插入数据
    query.exec("INSERT INTO person (name) VALUES ('张三')");
    query.exec("INSERT INTO person (name) VALUES ('李四')");
    query.exec("INSERT INTO person (name) VALUES ('王五')");
}

    //绑定数据
void Widget::bindData()
{
    //QTableView
    QTableView *tableView = new QTableView(this);
    tableView->setGeometry(QRect(50,80,310,200));
    //实例QSqlTableModel
    QSqlTableModel *model = new QSqlTableModel;
    //为数据模型指定表
    model->setTable("person");
    //查询
    model->select();
    //填充模型
    tableView->setModel(model);
    //表格只读，默认单元格可修改
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

}




Widget::~Widget()
{
    delete ui;
}
