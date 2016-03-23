#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtSql/QSqlDatabase>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);

    //测试连接
    bool connection();
    //创建数据库
    void createDB();
    QSqlDatabase db;
    //绑定数据
    void bindData();


    ~Widget();

private:
    Ui::Widget *ui;

};

#endif // WIDGET_H
