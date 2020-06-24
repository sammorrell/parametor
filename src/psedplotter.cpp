#include "psedplotter.h"
#include "ui_psedplotter.h"

PSEDPlotter::PSEDPlotter(QString dir, QString filePrefix, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PSEDPlotter)
{
    ui->setupUi(this);
    this->setWorkingDirectory(dir);
    this->setFilePrefix(filePrefix);

    //Scan for SEDs in the current directory
    this->refreshSEDFiles();

    // Create axes
    lambda_axis = new QLogValueAxis();
    lambda_axis->setTitleText("Wavelength (microns)");
    lambda_axis->setRange(0.1, 200.0);
    ui->grp_SEDGraph->chart()->addAxis(lambda_axis, Qt::AlignBottom);

    flux_axis = new QLogValueAxis();
    flux_axis->setTitleText("Flux (W/m^2)");
    flux_axis->setRange(1.0, 1.0E8);
    ui->grp_SEDGraph->chart()->addAxis(flux_axis, Qt::AlignLeft);

    //Init our Curves
    this->InitCurves();

    ui->grp_SEDGraph->setRenderHint(QPainter::Antialiasing);
    ui->grp_SEDGraph->chart()->show();

    //Connect the Signals of the Checkboxes to Trigger the Graph Replot
    connect(ui->chk_Combined, SIGNAL(clicked()), this, SLOT(checkboxUpdateGraph()));
    connect(ui->chk_StelDir, SIGNAL(clicked()), this, SLOT(checkboxUpdateGraph()));
    connect(ui->chk_StelScat, SIGNAL(clicked()), this, SLOT(checkboxUpdateGraph()));
    connect(ui->chk_ThermDir, SIGNAL(clicked()), this, SLOT(checkboxUpdateGraph()));
    connect(ui->chk_ThermScat, SIGNAL(clicked()), this, SLOT(checkboxUpdateGraph()));

}

PSEDPlotter::~PSEDPlotter()
{
    delete ui;
}

void PSEDPlotter::setWorkingDirectory(QString dir) {
    this->workingDir = dir;
}

void PSEDPlotter::setFilePrefix(QString prefix) {
    this->namePrefix = prefix;
}

void PSEDPlotter::refreshSEDFiles() {
    //First Clear Our Listbox
    ui->lst_SEDList->clear();

    QDir wrkDir(this->workingDir);
    QStringList fileNameTemplates;
    QStringList listEntries;
    QString filePattern = "_stellar_direct.dat|_stellar_scattered.dat|_thermal_direct.dat|_thermal_scattered.dat|.dat";
    fileNameTemplates << this->namePrefix + "_inc*.dat";

    wrkDir.setNameFilters(fileNameTemplates);
    foreach(QString file, wrkDir.entryList()) {
        if(!listEntries.contains(file.remove(QRegExp(filePattern)))) {
            listEntries << file.remove(QRegExp(filePattern));
        }
    }

    //Add to listbox
    ui->lst_SEDList->addItems(listEntries);
}

void PSEDPlotter::closeEvent(QCloseEvent *e) {
    Q_UNUSED(e);
    emit this->isGoingToClose();
}

void PSEDPlotter::InitCurves() {
    //Allocate the Curves
    this->combinedCurve = new QLineSeries();
    this->stellarDirectCurve = new QLineSeries();
    this->stellarScatteredCurve = new QLineSeries();
    this->thermalDirectCurve = new QLineSeries();
    this->thermalScatteredCurve = new QLineSeries();

    //Combined Curve Setup
    QPen combinedPen = QPen();
    combinedPen.setBrush(Qt::black);
    combinedPen.setStyle(Qt::DashLine);
    combinedPen.setWidth(2);
    combinedCurve->setPen(combinedPen);
    //combinedCurve->setSymbol(new QwtSymbol(QwtSymbol::Cross, QBrush(Qt::black, Qt::SolidPattern), QPen(Qt::black, 0, Qt::DashLine), QSize(2, 2)));
    combinedCurve->setName("Combined");
    ui->grp_SEDGraph->chart()->addSeries(combinedCurve);
    combinedCurve->attachAxis(lambda_axis);
    combinedCurve->attachAxis(flux_axis);

    //Stellar Direct Curve Setup
    QPen stellarDirectPen = QPen();
    stellarDirectPen.setBrush(Qt::blue);
    stellarDirectPen.setStyle(Qt::SolidLine);
    stellarDirectPen.setWidth(2);
    stellarDirectCurve->setPen(stellarDirectPen);
    //stellarDirectCurve->setSymbol(new QwtSymbol(QwtSymbol::Cross, QBrush(Qt::blue, Qt::SolidPattern), QPen(Qt::blue, 0, Qt::DashLine), QSize(2, 2)));
    stellarDirectCurve->setName("Stellar Direct");
    ui->grp_SEDGraph->chart()->addSeries(stellarDirectCurve);
    stellarDirectCurve->attachAxis(lambda_axis);
    stellarDirectCurve->attachAxis(flux_axis);

    //Stellar Scattered Curve Setup
    QPen stellarScatteredPen = QPen();
    stellarScatteredPen.setBrush(Qt::green);
    stellarScatteredPen.setStyle(Qt::SolidLine);
    stellarScatteredPen.setWidth(2);
    stellarScatteredCurve->setPen(stellarScatteredPen);
    //stellarScatteredCurve->setSymbol(new QwtSymbol(QwtSymbol::Cross, QBrush(Qt::green, Qt::SolidPattern), QPen(Qt::green, 0, Qt::DashLine), QSize(2, 2)));
    stellarScatteredCurve->setName("Stellar Scattered");
    ui->grp_SEDGraph->chart()->addSeries(stellarScatteredCurve);
    stellarScatteredCurve->attachAxis(lambda_axis);
    stellarScatteredCurve->attachAxis(flux_axis);

    //Thermal Direct Curve Setup
    QPen thermalDirectPen = QPen();
    thermalDirectPen.setBrush(Qt::red);
    thermalDirectPen.setStyle(Qt::SolidLine);
    thermalDirectPen.setWidth(2);
    thermalDirectCurve->setPen(thermalDirectPen);
    //thermalDirectCurve->setSymbol(new QwtSymbol(QwtSymbol::Cross, QBrush(Qt::red, Qt::SolidPattern), QPen(Qt::red, 0, Qt::DashLine), QSize(2, 2)));
    thermalDirectCurve->setName("Thermal Direct");
    ui->grp_SEDGraph->chart()->addSeries(thermalDirectCurve);
    thermalDirectCurve->attachAxis(lambda_axis);
    thermalDirectCurve->attachAxis(flux_axis);

    //Thermal Scattered Curve Curve Setup
    QPen thermalScatteredPen = QPen();
    thermalScatteredPen.setBrush(QColor(255, 123, 0));
    thermalScatteredPen.setStyle(Qt::SolidLine);
    thermalScatteredPen.setWidth(2);
    thermalScatteredCurve->setPen(thermalScatteredPen);
    //thermalScatteredCurve->setSymbol(new QwtSymbol(QwtSymbol::Cross, QBrush(QColor(255, 123, 0), Qt::SolidPattern), QPen(QColor(255, 123, 0), 0, Qt::DashLine), QSize(2, 2)));
    thermalScatteredCurve->setName("Thermal Scattered");
    ui->grp_SEDGraph->chart()->addSeries(thermalScatteredCurve);
    thermalScatteredCurve->attachAxis(lambda_axis);
    thermalScatteredCurve->attachAxis(flux_axis);
}

void PSEDPlotter::on_lst_SEDList_itemSelectionChanged() {
    QString file = this->workingDir + "/" + ui->lst_SEDList->currentItem()->text();
    this->PlotGraphs(file);
}

void PSEDPlotter::checkboxUpdateGraph() {
    QString file = this->workingDir + "/" + ui->lst_SEDList->currentItem()->text();
    this->PlotGraphs(file);
}

//Graph Plotting Function
void PSEDPlotter::PlotGraphs(QString file) {
    //ui->grp_SEDGraph->detachItems(QwtPlotItem::Rtti_PlotCurve, false);

    ui->grp_SEDGraph->chart()->removeSeries(combinedCurve);
    if(ui->chk_Combined->isChecked()) {
        this->PlotSED(file, SEDCombinedPlot);
        ui->grp_SEDGraph->chart()->addSeries(combinedCurve);
        combinedCurve->attachAxis(lambda_axis);
        combinedCurve->attachAxis(flux_axis);
    }

    ui->grp_SEDGraph->chart()->removeSeries(stellarDirectCurve);
    if(ui->chk_StelDir->isChecked()) {
        this->PlotSED(file, SEDStellarDirectPlot);
        ui->grp_SEDGraph->chart()->addSeries(stellarDirectCurve);
        stellarDirectCurve->attachAxis(lambda_axis);
        stellarDirectCurve->attachAxis(flux_axis);
    }

    ui->grp_SEDGraph->chart()->removeSeries(stellarScatteredCurve);
    if(ui->chk_StelScat->isChecked()) {
        this->PlotSED(file, SEDStellarScatteredPlot);
        ui->grp_SEDGraph->chart()->addSeries(stellarScatteredCurve);
        stellarScatteredCurve->attachAxis(lambda_axis);
        stellarScatteredCurve->attachAxis(flux_axis);
    }

    ui->grp_SEDGraph->chart()->removeSeries(thermalDirectCurve);
    if(ui->chk_ThermDir->isChecked()) {
        this->PlotSED(file, SEDThermalDirectPlot);
        ui->grp_SEDGraph->chart()->addSeries(thermalDirectCurve);
        thermalDirectCurve->attachAxis(lambda_axis);
        thermalDirectCurve->attachAxis(flux_axis);
    }

    ui->grp_SEDGraph->chart()->removeSeries(thermalScatteredCurve);
    if(ui->chk_ThermScat->isChecked()) {
        this->PlotSED(file, SEDThermalScatteredPlot);
        ui->grp_SEDGraph->chart()->addSeries(thermalScatteredCurve);
        thermalScatteredCurve->attachAxis(lambda_axis);
        thermalScatteredCurve->attachAxis(flux_axis);
    }
}

//File Plotting Methods
void PSEDPlotter::PlotSED(QString prefixName, SEDPlotType type) {
    QPolygonF data;

    switch (type) {
        case SEDCombinedPlot:
            ParseSEDDataFile(prefixName + ".dat", combinedCurve);
            break;

        case SEDStellarDirectPlot:
            ParseSEDDataFile(prefixName + "_stellar_direct.dat", stellarDirectCurve);
            break;

        case SEDStellarScatteredPlot:
            ParseSEDDataFile(prefixName + "_stellar_scattered.dat", stellarScatteredCurve);
            break;

        case SEDThermalDirectPlot:
            ParseSEDDataFile(prefixName + "_thermal_direct.dat", thermalDirectCurve);
            break;

        case SEDThermalScatteredPlot:
            ParseSEDDataFile(prefixName + "_thermal_scattered.dat", thermalScatteredCurve);
            break;

        default:

            break;
    }
}

void PSEDPlotter::ParseSEDDataFile(QString filename, QLineSeries* series) {
    QFile file(filename);
    QPointF lineValue;
    QMessageBox msgBox;

    qDebug() << "Loading File: " << filename;

    file.open(QIODevice::ReadOnly | QIODevice::Text);

    // Clear the series of existing points.
    series->clear();

    while(file.atEnd() == false) {
        QByteArray line = file.readLine();
        lineValue = this->ParseSEDLine(line);

        if(!lineValue.isNull() ) {

            //Prevent the Scale Breaking
            if(lineValue.y() != 0)
                *series << lineValue;
        }
    }
}

QPointF PSEDPlotter::ParseSEDLine(QByteArray line) {
    SEDParseStates state = ParseStart;
    QString buffer;
    int columnNo = 0;
    QPointF returnPoint;

    for(int i = 0; i < line.count(); i++) {
        char character = line.at(i);

        switch(state) {
             case ParseStart :
                switch(character) {
                    case ' ' :
                        state = ParseExpectNumber;
                    break;

                    case '#' :
                        state = ParseReadComment;
                    break;

                    default :
                        buffer.push_back(character);
                        state = ParseReadNumber;
                    break;
                }
             break;

            case ParseExpectNumber :
                switch(character) {
                    case '#' :
                        state = ParseReadComment;
                    break;

                    case ' ' :
                    break;

                    default :
                        buffer.push_back(character);
                        state = ParseReadNumber;
                    break;
                }
            break;

            case ParseReadNumber :
            switch(character) {
                case '#' :
                    state = ParseReadComment;
                break;

                case ' ' :
                    if(columnNo < 2) {
                        if(columnNo == 0) {
                            returnPoint.setX((buffer.toDouble()));
                        } else if(columnNo == 1) {
                            returnPoint.setY((buffer.toDouble()));
                        }
                    }
                    buffer.clear();
                    columnNo++;
                    state = ParseExpectNumber;
                break;

                default :
                    buffer.push_back(character);
                    state = ParseReadNumber;
                break;
            }
            break;

            case ParseReadComment :
                //Do Nothing
                buffer.clear();
            break;

            default :
            break;
        }
    }

    return returnPoint;
}
