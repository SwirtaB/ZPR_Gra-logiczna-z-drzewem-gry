#include <string>

#include <boost/python.hpp>

#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>

namespace py = boost::python;

int main(int argc, char *argv[])
{
    Py_Initialize();
    py::object main_module = py::import("__main__");
    py::object main_namespace = main_module.attr("__dict__");
    bool worked = false;
    char *res;
    try {
        py::object noneType = py::exec("a = \"hello\"", main_namespace);
        res = py::extract<char*>(main_namespace["a"]);
        worked = true;
    } catch (py::error_already_set const &) {
        PyErr_Print();
    }

    QApplication app(argc, argv);
    QLabel *label = worked ? new QLabel(res) : new QLabel("ohno");
    label->setFixedSize(200, 200);
    label->setAlignment(Qt::AlignmentFlag::AlignCenter);
    label->show();
    int code = app.exec();
    return code;
}