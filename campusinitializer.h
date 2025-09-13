#ifndef CAMPUSINITIALIZER_H
#define CAMPUSINITIALIZER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class CampusInitializer;
}
QT_END_NAMESPACE

class CampusInitializer : public QMainWindow
{
    Q_OBJECT

public:
    CampusInitializer(QWidget *parent = nullptr);
    ~CampusInitializer();

private:
    Ui::CampusInitializer *ui;
};
#endif // CAMPUSINITIALIZER_H
