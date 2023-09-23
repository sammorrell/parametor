#ifndef PSEDPLOTTER_H
#define PSEDPLOTTER_H

#include <QWidget>
#include <QDir>
#include <QMessageBox>
#include <QColor>
#include <QtCharts>
#include <QValueAxis>

namespace Ui {
class PSEDPlotter;
}

class PSEDPlotter : public QWidget
{
    Q_OBJECT
    
public:

    enum SEDPlotType {
        SEDCombinedPlot,
        SEDStellarDirectPlot,
        SEDStellarScatteredPlot,
        SEDThermalDirectPlot,
        SEDThermalScatteredPlot
    };

    enum SEDParseStates {
        ParseStart,
        ParseExpectNumber,
        ParseReadNumber,
        ParseReadComment
    };

    explicit PSEDPlotter(QString dir, QString filePrefix = "", QWidget *parent = 0);
    ~PSEDPlotter();

    void setWorkingDirectory(QString dir);
    void setFilePrefix(QString prefix);
    void refreshSEDFiles();
    void PlotGraphs(QString file = "");

    //PlotType
    void PlotSED(QString prefixName = "", SEDPlotType type = SEDCombinedPlot);
    void ParseSEDDataFile(QString filename, QLineSeries* series);
    QPointF ParseSEDLine(QByteArray line);
    
private:
    Ui::PSEDPlotter *ui;
    void closeEvent(QCloseEvent *e);
    void InitCurves();

    QString workingDir;
    QString namePrefix;

    //Curves
    QLineSeries *combinedCurve;
    QLineSeries *stellarDirectCurve;
    QLineSeries *stellarScatteredCurve;
    QLineSeries *thermalDirectCurve;
    QLineSeries *thermalScatteredCurve;

    // Axes
    QLogValueAxis *lambda_axis;
    QLogValueAxis *flux_axis;

signals:
    void isGoingToClose();
private slots:
    void on_lst_SEDList_itemSelectionChanged();

public slots:
    void checkboxUpdateGraph();
};

#endif // PSEDPLOTTER_H
