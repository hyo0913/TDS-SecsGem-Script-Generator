#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QComboBox>
#include <QCheckBox>
#include <QTextStream>

#include "ScriptViewDialog.h"

const static QString CR = "\r";
const static QString TAB = "\t";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidgetAlarmDevParams->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidgetAlarmVirParams->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidgetEventDevParams->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidgetEventVirParams->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);

    initExampleAlarm();
    initExampleEvent();

    setAlarmExampleLabels();
    setEventExampleLabels();

    // alarm
    connect(ui->pushButton_GenAlarm, SIGNAL(clicked()), this, SLOT(onGenerateAlarm()));

    connect(ui->spinBox_AlarmId, SIGNAL(editingFinished()), this, SLOT(setAlarmExampleLabels()));
    connect(ui->lineEditAlarmDevAddr, SIGNAL(editingFinished()), this, SLOT(setAlarmExampleLabels()));
    connect(ui->lineEditAlarmVirAddr, SIGNAL(editingFinished()), this, SLOT(setAlarmExampleLabels()));

    connect(ui->toolButtonAlarmAddDevParam, SIGNAL(clicked()), this, SLOT(onAddAlarmDevParam()));
    connect(ui->toolButtonAlarmDelDevParam, SIGNAL(clicked()), this, SLOT(onDelAlarmDevParam()));
    connect(ui->toolButtonAlarmAddVirParam, SIGNAL(clicked()), this, SLOT(onAddAlarmVirParam()));
    connect(ui->toolButtonAlarmDelVirParam, SIGNAL(clicked()), this, SLOT(onDelAlarmVirParam()));

    // event
    connect(ui->pushButton_GenEvent, SIGNAL(clicked()), this, SLOT(onGenerateEvent()));

    connect(ui->spinBox_EventId, SIGNAL(editingFinished()), this, SLOT(setEventExampleLabels()));
    connect(ui->lineEditEventDevAddr, SIGNAL(editingFinished()), this, SLOT(setEventExampleLabels()));
    connect(ui->lineEditEventVirAddr, SIGNAL(editingFinished()), this, SLOT(setEventExampleLabels()));

    connect(ui->toolButtonEventAddDevParam, SIGNAL(clicked()), this, SLOT(onAddEventDevParam()));
    connect(ui->toolButtonEventDelDevParam, SIGNAL(clicked()), this, SLOT(onDelEventDevParam()));
    connect(ui->toolButtonEventAddVirParam, SIGNAL(clicked()), this, SLOT(onAddEventVirParam()));
    connect(ui->toolButtonEventDelVirParam, SIGNAL(clicked()), this, SLOT(onDelEventVirParam()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initExampleAlarm()
{
    ui->lineEditAlarmDevAddr->setText("[@PLC1:D%1.%2:1:UDEC]");
    ui->lineEditAlarmVirAddr->setText("[@Virtual:Alarm_%1:1:UDEC]");

    onAddAlarmDevParam();
    onAddAlarmDevParam();

    onAddAlarmVirParam();

    QSpinBox* spinBox = NULL;
    QCheckBox* checkBox = NULL;
    QComboBox* comboBox = NULL;

    // Dev %1
    spinBox = static_cast<QSpinBox*>(ui->tableWidgetAlarmDevParams->cellWidget(0, TableColumn_Def));        // default
    spinBox->setValue(1000);
    spinBox = static_cast<QSpinBox*>(ui->tableWidgetAlarmDevParams->cellWidget(0, TableColumn_Inc));        // increase
    spinBox->setValue(1);
    spinBox = static_cast<QSpinBox*>(ui->tableWidgetAlarmDevParams->cellWidget(0, TableColumn_IncPer));     // increase per
    spinBox->setValue(16);
    comboBox = static_cast<QComboBox*>(ui->tableWidgetAlarmDevParams->cellWidget(0, TableColumn_Base));     // base
    comboBox->setCurrentIndex(0);
    spinBox = static_cast<QSpinBox*>(ui->tableWidgetAlarmDevParams->cellWidget(0, TableColumn_Width));      // width
    spinBox->setValue(5);
    checkBox = static_cast<QCheckBox*>(ui->tableWidgetAlarmDevParams->cellWidget(0, TableColumn_Range));    // range
    checkBox->setChecked(false);
    spinBox = static_cast<QSpinBox*>(ui->tableWidgetAlarmDevParams->cellWidget(0, TableColumn_Min));        // min
    spinBox->setValue(0);
    spinBox = static_cast<QSpinBox*>(ui->tableWidgetAlarmDevParams->cellWidget(0, TableColumn_Max));        // max
    spinBox->setValue(0);

    // Dev %2
    spinBox = static_cast<QSpinBox*>(ui->tableWidgetAlarmDevParams->cellWidget(1, TableColumn_Def));        // default
    spinBox->setValue(0);
    spinBox = static_cast<QSpinBox*>(ui->tableWidgetAlarmDevParams->cellWidget(1, TableColumn_Inc));        // increase
    spinBox->setValue(1);
    spinBox = static_cast<QSpinBox*>(ui->tableWidgetAlarmDevParams->cellWidget(1, TableColumn_IncPer));     // increase per
    spinBox->setValue(1);
    comboBox = static_cast<QComboBox*>(ui->tableWidgetAlarmDevParams->cellWidget(1, TableColumn_Base));     // base
    comboBox->setCurrentIndex(0);
    spinBox = static_cast<QSpinBox*>(ui->tableWidgetAlarmDevParams->cellWidget(1, TableColumn_Width));      // width
    spinBox->setValue(2);
    checkBox = static_cast<QCheckBox*>(ui->tableWidgetAlarmDevParams->cellWidget(1, TableColumn_Range));    // range
    checkBox->setChecked(true);
    spinBox = static_cast<QSpinBox*>(ui->tableWidgetAlarmDevParams->cellWidget(1, TableColumn_Min));        // min
    spinBox->setValue(0);
    spinBox = static_cast<QSpinBox*>(ui->tableWidgetAlarmDevParams->cellWidget(1, TableColumn_Max));        // max
    spinBox->setValue(15);

    // Vir %1
    spinBox = static_cast<QSpinBox*>(ui->tableWidgetAlarmVirParams->cellWidget(0, TableColumn_Def));        // default
    spinBox->setValue(101);
    spinBox = static_cast<QSpinBox*>(ui->tableWidgetAlarmVirParams->cellWidget(0, TableColumn_Inc));        // increase
    spinBox->setValue(1);
    spinBox = static_cast<QSpinBox*>(ui->tableWidgetAlarmVirParams->cellWidget(0, TableColumn_IncPer));     // increase per
    spinBox->setValue(1);
    comboBox = static_cast<QComboBox*>(ui->tableWidgetAlarmVirParams->cellWidget(0, TableColumn_Base));     // base
    comboBox->setCurrentIndex(0);
    spinBox = static_cast<QSpinBox*>(ui->tableWidgetAlarmVirParams->cellWidget(0, TableColumn_Width));      // width
    spinBox->setValue(0);
    checkBox = static_cast<QCheckBox*>(ui->tableWidgetAlarmVirParams->cellWidget(0, TableColumn_Range));    // range
    checkBox->setChecked(false);
    spinBox = static_cast<QSpinBox*>(ui->tableWidgetAlarmVirParams->cellWidget(0, TableColumn_Min));        // min
    spinBox->setValue(0);
    spinBox = static_cast<QSpinBox*>(ui->tableWidgetAlarmVirParams->cellWidget(0, TableColumn_Max));        // max
    spinBox->setValue(0);

    ui->spinBox_AlarmId->setValue(101);
    ui->spinBox_AlarmCount->setValue(50);
}

void MainWindow::initExampleEvent()
{
    ui->lineEditEventDevAddr->setText("[@PLC1:D%1.%2:1:UDEC]");
    ui->lineEditEventVirAddr->setText("[@Virtual:Event_%1:1:UDEC]");

    onAddEventDevParam();
    onAddEventDevParam();

    onAddEventVirParam();

    QSpinBox* spinBox = NULL;
    QCheckBox* checkBox = NULL;
    QComboBox* comboBox = NULL;

    // Dev %1
    spinBox = static_cast<QSpinBox*>(ui->tableWidgetEventDevParams->cellWidget(0, TableColumn_Def));        // default
    spinBox->setValue(2000);
    spinBox = static_cast<QSpinBox*>(ui->tableWidgetEventDevParams->cellWidget(0, TableColumn_Inc));        // increase
    spinBox->setValue(1);
    spinBox = static_cast<QSpinBox*>(ui->tableWidgetEventDevParams->cellWidget(0, TableColumn_IncPer));     // increase per
    spinBox->setValue(16);
    comboBox = static_cast<QComboBox*>(ui->tableWidgetEventDevParams->cellWidget(0, TableColumn_Base));     // base
    comboBox->setCurrentIndex(0);
    spinBox = static_cast<QSpinBox*>(ui->tableWidgetEventDevParams->cellWidget(0, TableColumn_Width));      // width
    spinBox->setValue(5);
    checkBox = static_cast<QCheckBox*>(ui->tableWidgetEventDevParams->cellWidget(0, TableColumn_Range));    // range
    checkBox->setChecked(false);
    spinBox = static_cast<QSpinBox*>(ui->tableWidgetEventDevParams->cellWidget(0, TableColumn_Min));        // min
    spinBox->setValue(0);
    spinBox = static_cast<QSpinBox*>(ui->tableWidgetEventDevParams->cellWidget(0, TableColumn_Max));        // max
    spinBox->setValue(0);

    // Dev %2
    spinBox = static_cast<QSpinBox*>(ui->tableWidgetEventDevParams->cellWidget(1, TableColumn_Def));        // default
    spinBox->setValue(0);
    spinBox = static_cast<QSpinBox*>(ui->tableWidgetEventDevParams->cellWidget(1, TableColumn_Inc));        // increase
    spinBox->setValue(1);
    spinBox = static_cast<QSpinBox*>(ui->tableWidgetEventDevParams->cellWidget(1, TableColumn_IncPer));     // increase per
    spinBox->setValue(1);
    comboBox = static_cast<QComboBox*>(ui->tableWidgetEventDevParams->cellWidget(1, TableColumn_Base));     // base
    comboBox->setCurrentIndex(0);
    spinBox = static_cast<QSpinBox*>(ui->tableWidgetEventDevParams->cellWidget(1, TableColumn_Width));      // width
    spinBox->setValue(2);
    checkBox = static_cast<QCheckBox*>(ui->tableWidgetEventDevParams->cellWidget(1, TableColumn_Range));    // range
    checkBox->setChecked(true);
    spinBox = static_cast<QSpinBox*>(ui->tableWidgetEventDevParams->cellWidget(1, TableColumn_Min));        // min
    spinBox->setValue(0);
    spinBox = static_cast<QSpinBox*>(ui->tableWidgetEventDevParams->cellWidget(1, TableColumn_Max));        // max
    spinBox->setValue(15);

    // Vir %1
    spinBox = static_cast<QSpinBox*>(ui->tableWidgetEventVirParams->cellWidget(0, TableColumn_Def));        // default
    spinBox->setValue(1001);
    spinBox = static_cast<QSpinBox*>(ui->tableWidgetEventVirParams->cellWidget(0, TableColumn_Inc));        // increase
    spinBox->setValue(1);
    spinBox = static_cast<QSpinBox*>(ui->tableWidgetEventVirParams->cellWidget(0, TableColumn_IncPer));     // increase per
    spinBox->setValue(1);
    comboBox = static_cast<QComboBox*>(ui->tableWidgetEventVirParams->cellWidget(0, TableColumn_Base));     // base
    comboBox->setCurrentIndex(0);
    spinBox = static_cast<QSpinBox*>(ui->tableWidgetEventVirParams->cellWidget(0, TableColumn_Width));      // width
    spinBox->setValue(0);
    checkBox = static_cast<QCheckBox*>(ui->tableWidgetEventVirParams->cellWidget(0, TableColumn_Range));    // range
    checkBox->setChecked(false);
    spinBox = static_cast<QSpinBox*>(ui->tableWidgetEventVirParams->cellWidget(0, TableColumn_Min));        // min
    spinBox->setValue(0);
    spinBox = static_cast<QSpinBox*>(ui->tableWidgetEventVirParams->cellWidget(0, TableColumn_Max));        // max
    spinBox->setValue(0);

    ui->spinBox_EventId->setValue(1001);
    ui->spinBox_EventCount->setValue(50);
}

void MainWindow::addParameter(QTableWidget *widget)
{
    if( widget == NULL ) { return; }

    int row = widget->rowCount();
    widget->setRowCount(row+1);

    // default
    QSpinBox* spinVal = new QSpinBox();
    spinVal->setRange(0, 0x7FFFFFFF);
    spinVal->setValue(0);
    spinVal->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    widget->setCellWidget(row, TableColumn_Def, spinVal);

    // increase
    QSpinBox* spinInc = new QSpinBox();
    spinInc->setRange(0x80000000, 0x7FFFFFFF);
    spinInc->setValue(1);
    spinInc->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    widget->setCellWidget(row, TableColumn_Inc, spinInc);

    // increase per
    QSpinBox* spinIncPer = new QSpinBox();
    spinIncPer->setRange(1, 0x7FFFFFFF);
    spinIncPer->setValue(1);
    spinIncPer->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    widget->setCellWidget(row, TableColumn_IncPer, spinIncPer);

    // base
    QComboBox* comboBase = new QComboBox();
    comboBase->addItem("DEC");
    comboBase->addItem("HEX");
    comboBase->addItem("OCT");
    widget->setCellWidget(row, TableColumn_Base, comboBase);

    // field width
    QSpinBox* spinWidth = new QSpinBox();
    spinWidth->setRange(0, 10);
    spinWidth->setValue(0);
    spinWidth->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    widget->setCellWidget(row, TableColumn_Width, spinWidth);

    // use range
    QCheckBox* checkRange = new QCheckBox();
    widget->setCellWidget(row, TableColumn_Range, checkRange);

    // min
    QSpinBox* spinMin = new QSpinBox();
    spinMin->setRange(0, 0x7FFFFFFF);
    spinMin->setValue(0);
    spinMin->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    widget->setCellWidget(row, TableColumn_Min, spinMin);

    // max
    QSpinBox* spinMax = new QSpinBox();
    spinMax->setRange(0, 0x7FFFFFFF);
    spinMax->setValue(0);
    spinMax->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    widget->setCellWidget(row, TableColumn_Max, spinMax);

    QStringList names;
    for( int i = 1; i <= row+1; i++ ) { names << QString().sprintf("%%%d", i); }
    widget->setVerticalHeaderLabels(names);
}

void MainWindow::delParameter(QTableWidget *widget)
{
    if( widget == NULL ) { return; }

    int row = widget->rowCount()-1;
    int columnCount = widget->columnCount();

    for( int column = 0; column < columnCount; column++ ) {
        widget->removeCellWidget(row, column);
    }

    widget->setRowCount(row);
}

void MainWindow::connectNewParamToSetExample(const QTableWidget *widget, const char *slot)
{
    int row = widget->rowCount()-1;

    QSpinBox* itemVal = static_cast<QSpinBox*>(widget->cellWidget(row, TableColumn_Def));
    //QSpinBox* itemInc = static_cast<QSpinBox*>(widget->cellWidget(row, TableColumn_Inc));
    //QSpinBox* itemIncPer = static_cast<QSpinBox*>(widget->cellWidget(row, TableColumn_IncPer));
    QComboBox* itemBase = static_cast<QComboBox*>(widget->cellWidget(row, TableColumn_Base));
    QSpinBox* itemWidth = static_cast<QSpinBox*>(widget->cellWidget(row, TableColumn_Width));
    QCheckBox* itemRange = static_cast<QCheckBox*>(widget->cellWidget(row, TableColumn_Range));
    QSpinBox* itemMin = static_cast<QSpinBox*>(widget->cellWidget(row, TableColumn_Min));
    QSpinBox* itemMax = static_cast<QSpinBox*>(widget->cellWidget(row, TableColumn_Max));

    if( itemVal == NULL || /*itemInc == NULL || itemIncPer == NULL ||*/ itemBase == NULL ||
        itemWidth == NULL || itemRange == NULL || itemMin == NULL || itemMax == NULL )
    {
        return;
    }

    connect(itemVal, SIGNAL(editingFinished()), this, slot);
    //connect(itemInc, SIGNAL(editingFinished()), this, slot);
    //connect(itemIncPer, SIGNAL(editingFinished()), this, slot);
    connect(itemBase, SIGNAL(currentIndexChanged(int)), this, slot);
    connect(itemWidth, SIGNAL(editingFinished()), this, slot);
    connect(itemRange, SIGNAL(clicked()), this, slot);
    connect(itemMin, SIGNAL(editingFinished()), this, slot);
    connect(itemMax, SIGNAL(editingFinished()), this, slot);
}

QString MainWindow::makeAlarmScript() const
{
    QString result;
    QString devAddr;
    QString virAddr;
    QString condition;
    QString line1;
    QString line2;
    const QString devAddrFormat = ui->lineEditAlarmDevAddr->text();
    const QString virAddrFormat = ui->lineEditAlarmVirAddr->text();

    int count = ui->spinBox_AlarmCount->value();

    for( int i = 0; i < count; i++ )
    {
        devAddr = makeAddress(devAddrFormat, ui->tableWidgetAlarmDevParams, i);
        virAddr = makeAddress(virAddrFormat, ui->tableWidgetAlarmVirParams, i);

        condition = QString("if( %1 != %2 )").arg(devAddr).arg(virAddr);
        line1 = QString("HsmsAlarmReport(%1, %2)").arg(ui->spinBox_AlarmId->value()).arg(devAddr);
        line2 = QString("%1 = %2;").arg(virAddr).arg(devAddr);

        result += condition + CR;
        result += "{" + CR;
        result += TAB + line1 + CR;
        result += TAB + line2 + CR;
        result += "}" + CR;
        result += CR;
    }

    return result;
}

QString MainWindow::makeEventScript() const
{
    QString result;
    QString devAddr;
    QString virAddr;
    QString condition1;
    QString condition2;
    QString line1;
    QString line2;
    const QString devAddrFormat = ui->lineEditEventDevAddr->text();
    const QString virAddrFormat = ui->lineEditEventVirAddr->text();

    int count = ui->spinBox_EventCount->value();

    for( int i = 0; i < count; i++ )
    {
        devAddr = makeAddress(devAddrFormat, ui->tableWidgetEventDevParams, i);
        virAddr = makeAddress(virAddrFormat, ui->tableWidgetEventVirParams, i);

        condition1 = QString("if( %1 != %2 )").arg(devAddr).arg(virAddr);
        condition2 = QString("if( %1 != 0 )").arg(devAddr);
        line1 = QString("HsmsEventReport(%1)").arg(ui->spinBox_EventId->value());
        line2 = QString("%1 = %2;").arg(virAddr).arg(devAddr);

        result += condition1 + CR;
        result += "{" + CR;
        result += TAB + condition2 + CR;
        result += TAB + "{" + CR;
        result += TAB + TAB + line1 + CR;
        result += TAB + "}" + CR;
        result += TAB + line2 + CR;
        result += "}" + CR;
        result += CR;
    }

    return result;
}

QString MainWindow::makeAddress(const QString &addrFormat, const QTableWidget *tableWidget, int sequence) const
{
    if( tableWidget == NULL ) { return QString(); }

    QString result = addrFormat;
    QString arg;

    for( int row = 0; row < tableWidget->rowCount(); row++ )
    {
        QSpinBox* itemVal = static_cast<QSpinBox*>(tableWidget->cellWidget(row, TableColumn_Def));
        QSpinBox* itemInc = static_cast<QSpinBox*>(tableWidget->cellWidget(row, TableColumn_Inc));
        QSpinBox* itemIncPer = static_cast<QSpinBox*>(tableWidget->cellWidget(row, TableColumn_IncPer));
        QComboBox* itemBase = static_cast<QComboBox*>(tableWidget->cellWidget(row, TableColumn_Base));
        QSpinBox* itemWidth = static_cast<QSpinBox*>(tableWidget->cellWidget(row, TableColumn_Width));
        QCheckBox* itemRange = static_cast<QCheckBox*>(tableWidget->cellWidget(row, TableColumn_Range));
        QSpinBox* itemMin = static_cast<QSpinBox*>(tableWidget->cellWidget(row, TableColumn_Min));
        QSpinBox* itemMax = static_cast<QSpinBox*>(tableWidget->cellWidget(row, TableColumn_Max));

        if( itemVal == NULL || itemInc == NULL || itemIncPer == NULL || itemBase == NULL ||
            itemWidth == NULL || itemRange == NULL || itemMin == NULL || itemMax == NULL )
        {
            break;
        }

        int val = itemVal->value();
        int inc = itemInc->value();
        int incPer = itemIncPer->value();
        int base = 10;
        int width = itemWidth->value();
        bool useRange = itemRange->isChecked();
        int min = itemMin->value();
        int max = itemMax->value()+1;

        switch( itemBase->currentIndex() )
        {
        case 0: base = 10; break;
        case 1: base = 16; break;
        case 2: base = 8; break;
        }

        val += inc * (sequence / incPer);

        if( useRange ) {
            val = (val % max) + min;

            if( val < min ) {
                val += max;
            }
        }

        arg = QString("%1").arg(val, width, base, QChar('0'));
        if( base == 16) { arg = arg.toUpper(); }

        result = result.arg(arg);
    }

    return result;
}

void MainWindow::onGenerateAlarm()
{
    ScriptViewDialog dialog;

    QString script = makeAlarmScript();

    dialog.showScript(script);
}

void MainWindow::setAlarmExampleLabels()
{
    QString devAddr = makeAddress(ui->lineEditAlarmDevAddr->text(), ui->tableWidgetAlarmDevParams, 0);
    QString virAddr = makeAddress(ui->lineEditAlarmVirAddr->text(), ui->tableWidgetAlarmVirParams, 0);

    QString condition = QString("if( %1 != %2 )").arg(devAddr).arg(virAddr);
    QString line1 = QString("\tHsmsAlarmReport(%1, %2)").arg(ui->spinBox_AlarmId->value()).arg(devAddr);
    QString line2 = QString("\t%1 = %2;").arg(virAddr).arg(devAddr);

    ui->label_AlarmCondition->setText(condition);
    ui->label_AlarmLine1->setText(line1);
    ui->label_AlarmLine2->setText(line2);
}

void MainWindow::onAddAlarmDevParam()
{
    addParameter(ui->tableWidgetAlarmDevParams);
    connectNewParamToSetExample(ui->tableWidgetAlarmDevParams, SLOT(setAlarmExampleLabels()));
}

void MainWindow::onDelAlarmDevParam()
{
    delParameter(ui->tableWidgetAlarmDevParams);
}

void MainWindow::onAddAlarmVirParam()
{
    addParameter(ui->tableWidgetAlarmVirParams);
    connectNewParamToSetExample(ui->tableWidgetAlarmVirParams, SLOT(setAlarmExampleLabels()));
}

void MainWindow::onDelAlarmVirParam()
{
    delParameter(ui->tableWidgetAlarmVirParams);
}

void MainWindow::onGenerateEvent()
{
    ScriptViewDialog dialog;

    QString script = makeEventScript();

    dialog.showScript(script);
}

void MainWindow::setEventExampleLabels()
{
    QString devAddr = makeAddress(ui->lineEditEventDevAddr->text(), ui->tableWidgetEventDevParams, 0);
    QString virAddr = makeAddress(ui->lineEditEventVirAddr->text(), ui->tableWidgetEventVirParams, 0);

    QString condition1 = QString("if( %1 != %2 )").arg(devAddr).arg(virAddr);
    QString condition2 = QString("\tif( %1 != 0 )").arg(devAddr);
    QString line1 = QString("\t\tHsmsEventReport(%1)").arg(ui->spinBox_EventId->value());
    QString line2 = QString("\t%1 = %2;").arg(virAddr).arg(devAddr);

    ui->label_EventCondition1->setText(condition1);
    ui->label_EventCondition2->setText(condition2);

    ui->label_EventLine1->setText(line1);
    ui->label_EventLine2->setText(line2);
}

void MainWindow::onAddEventDevParam()
{
    addParameter(ui->tableWidgetEventDevParams);
    connectNewParamToSetExample(ui->tableWidgetEventDevParams, SLOT(setEventExampleLabels()));
}

void MainWindow::onDelEventDevParam()
{
    delParameter(ui->tableWidgetEventDevParams);
}

void MainWindow::onAddEventVirParam()
{
    addParameter(ui->tableWidgetEventVirParams);
    connectNewParamToSetExample(ui->tableWidgetEventVirParams, SLOT(setEventExampleLabels()));
}

void MainWindow::onDelEventVirParam()
{
    delParameter(ui->tableWidgetEventVirParams);
}
