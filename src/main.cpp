#include <string>

#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>

#include <boost/shared_ptr.hpp>
#include <boost/python.hpp>


int main(int argc, char *argv[])
{
    //Py_Initialize();

    boost::shared_ptr<QString> a(new QString("iksde"));

    QApplication app(argc, argv);
    QLabel *label = new QLabel(*a);
    label->setFixedSize(200, 200);
    label->setAlignment(Qt::AlignmentFlag::AlignCenter);
    label->show();
    int code = app.exec();
    return code;
}