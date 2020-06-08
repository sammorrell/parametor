#ifndef PTORUSMONITOR_H
#define PTORUSMONITOR_H

#include <QWidget>

namespace Ui {
class PTorusMonitor;
}

class PTorusMonitor : public QWidget
{
    Q_OBJECT
    
public:
    explicit PTorusMonitor(QWidget *parent = 0);
    ~PTorusMonitor();
    
private:
    Ui::PTorusMonitor *ui;
};

#endif // PTORUSMONITOR_H
