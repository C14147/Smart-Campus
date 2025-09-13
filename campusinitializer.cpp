#include "."
#include "./ui_campusinitializer.h"

CampusInitializer::CampusInitializer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CampusInitializer)
{
    ui->setupUi(this);
}

CampusInitializer::~CampusInitializer()
{
    delete ui;
}
