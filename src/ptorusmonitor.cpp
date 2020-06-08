#include "ptorusmonitor.h"
#include "ui_ptorusmonitor.h"

PTorusMonitor::PTorusMonitor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PTorusMonitor)
{
    ui->setupUi(this);
}

PTorusMonitor::~PTorusMonitor()
{
    delete ui;
}
