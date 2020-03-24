#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QComboBox>
#include <QCheckBox>
#include <QTextStream>

#include "ScriptViewDialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidgetDevParams->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidgetVirParams->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);

    initExample();

    setAlarmExampleLabels();

    connect(ui->pushButton_GenAlarm, SIGNAL(clicked()), this, SLOT(onGenerateAlarm()));

    connect(ui->spinBox_AlarmId, SIGNAL(editingFinished()), this, SLOT(setAlarmExampleLabels()));
    connect(ui->lineEditDevAddr, SIGNAL(editingFinished()), this, SLOT(setAlarmExampleLabels()));
    connect(ui->lineEditVirAddr, SIGNAL(editingFinished()), this, SLOT(setAlarmExampleLabels()));

    connect(ui->toolButtonAddDevParam, SIGNAL(clicked()), this, SLOT(onAddAlarmDevParam()));
    connect(ui->toolButtonDelDevParam, SIGNAL(clicked()), this, SLOT(onDelAlarmDevParam()));
    connect(ui->toolButtonAddVirParam, SIGNAL(clicked()), this, SLOT(onAddAlarmVirParam()));
    connect(ui->toolButtonDelVirParam, SIGNAL(clicked()), this, SLOT(onDelAlarmVirParam()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initExample()
{
    onAddAlarmDevParam();
    onAddAlarmDevParam();

    onAddAlarmVirParam();

    QSpinBox* spinBox = NULL;
    QCheckBox* checkBox = NULL;
    QComboBox* comboBox = NULL;

    // Dev %1
    spinBox = static_cast<QSpinBox*>(ui->tableWidgetDevParams->cellWidget(0, TableColumn_Def));     // default
    spinBox->setValue(1000);
    spinBox = static_cast<QSpinBox*>(ui->tableWidgetDevParams->cellWidget(0, TableColumn_Inc));     // increase
    spinBox->setValue(1);
    spinBox = static_cast<QSpinBox*>(ui->tableWidgetDevParams->cellWidget(0, TableColumn_IncPer));  // increase per
    spinBox->setValue(16);
    comboBox = static_cast<QComboBox*>(ui->tableWidgetDevParams->cellWidget(0, TableColumn_Base));   // base
    comboBox->setCurrentIndex(0);
    spinBox = static_cast<QSpinBox*>(ui->tableWidgetDevParams->cellWidget(0, TableColumn_Width));   // width
    spinBox->setValue(5);
    checkBox = static_cast<QCheckBox*>(ui->tableWidgetDevParams->cellWidget(0, TableColumn_Range)); // range
    checkBox->setChecked(false);
    spinBox = static_cast<QSpinBox*>(ui->tableWidgetDevParams->cellWidget(0, TableColumn_Min));     // min
    spinBox->setValue(0);
    spinBox = static_cast<QSpinBox*>(ui->tableWidgetDevParams->cellWidget(0, TableColumn_Max));     // max
    spinBox->setValue(0);

    // Dev %2
    spinBox = static_cast<QSpinBox*>(ui->tableWidgetDevParams->cellWidget(1, TableColumn_Def));     // default
    spinBox->setValue(0);
    spinBox = static_cast<QSpinBox*>(ui->tableWidgetDevParams->cellWidget(1, TableColumn_Inc));     // increase
    spinBox->setValue(1);
    spinBox = static_cast<QSpinBox*>(ui->tableWidgetDevParams->cellWidget(1, TableColumn_IncPer));  // increase per
    spinBox->setValue(1);
    comboBox = static_cast<QComboBox*>(ui->tableWidgetDevParams->cellWidget(1, TableColumn_Base));   // base
    comboBox->setCurrentIndex(0);
    spinBox = static_cast<QSpinBox*>(ui->tableWidgetDevParams->cellWidget(1, TableColumn_Width));   // width
    spinBox->setValue(2);
    checkBox = static_cast<QCheckBox*>(ui->tableWidgetDevParams->cellWidget(1, TableColumn_Range)); // range
    checkBox->setChecked(true);
    spinBox = static_cast<QSpinBox*>(ui->tableWidgetDevParams->cellWidget(1, TableColumn_Min));     // min
    spinBox->setValue(0);
    spinBox = static_cast<QSpinBox*>(ui->tableWidgetDevParams->cellWidget(1, TableColumn_Max));     // max
    spinBox->setValue(15);

    // Vir %1
    spinBox = static_cast<QSpinBox*>(ui->tableWidgetVirParams->cellWidget(0, TableColumn_Def));     // default
    spinBox->setValue(101);
    spinBox = static_cast<QSpinBox*>(ui->tableWidgetVirParams->cellWidget(0, TableColumn_Inc));     // increase
    spinBox->setValue(1);
    spinBox = static_cast<QSpinBox*>(ui->tableWidgetVirParams->cellWidget(0, TableColumn_IncPer));  // increase per
    spinBox->setValue(1);
    comboBox = static_cast<QComboBox*>(ui->tableWidgetVirParams->cellWidget(0, TableColumn_Base));   // base
    comboBox->setCurrentIndex(0);
    spinBox = static_cast<QSpinBox*>(ui->tableWidgetVirParams->cellWidget(0, TableColumn_Width));   // width
    spinBox->setValue(0);
    checkBox = static_cast<QCheckBox*>(ui->tableWidgetVirParams->cellWidget(0, TableColumn_Range)); // range
    checkBox->setChecked(false);
    spinBox = static_cast<QSpinBox*>(ui->tableWidgetVirParams->cellWidget(0, TableColumn_Min));     // min
    spinBox->setValue(0);
    spinBox = static_cast<QSpinBox*>(ui->tableWidgetVirParams->cellWidget(0, TableColumn_Max));     // max
    spinBox->setValue(0);

    ui->spinBox_AlarmId->setValue(101);
}

void MainWindow::addParameter(QTableWidget *widget)
{
    if( widget == NULL ) { return; }

    int row = widget->rowCount();
    widget->setRowCount(row+1);

    // default
    QSpinBox* spinVal = new QSpinBox();
    spinVal->setRange(0x80000000, 0x7FFFFFFF);
    spinVal->setValue(0);
    spinVal->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    widget->setCellWidget(row, TableColumn_Def, spinVal);
    connect(spinVal, SIGNAL(editingFinished()), this, SLOT(setAlarmExampleLabels()));

    // increase
    QSpinBox* spinInc = new QSpinBox();
    spinInc->setRange(0x80000000, 0x7FFFFFFF);
    spinInc->setValue(1);
    spinInc->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    widget->setCellWidget(row, TableColumn_Inc, spinInc);

    // increase per
    QSpinBox* spinIncPer = new QSpinBox();
    spinInc->setRange(1, 0x7FFFFFFF);
    spinInc->setValue(1);
    spinInc->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    widget->setCellWidget(row, TableColumn_IncPer, spinIncPer);

    // base
    QComboBox* comboBase = new QComboBox();
    comboBase->addItem("DEC");
    comboBase->addItem("HEX");
    widget->setCellWidget(row, TableColumn_Base, comboBase);
    connect(comboBase, SIGNAL(currentIndexChanged(int)), this, SLOT(setAlarmExampleLabels()));

    // field width
    QSpinBox* spinWidth = new QSpinBox();
    spinWidth->setRange(0, 10);
    spinWidth->setValue(0);
    spinWidth->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    widget->setCellWidget(row, TableColumn_Width, spinWidth);
    connect(spinWidth, SIGNAL(editingFinished()), this, SLOT(setAlarmExampleLabels()));

    // use range
    QCheckBox* checkRange = new QCheckBox();
    widget->setCellWidget(row, TableColumn_Range, checkRange);

    // min
    QSpinBox* spinMin = new QSpinBox();
    spinMin->setRange(0x80000000, 0x7FFFFFFF);
    spinMin->setValue(0);
    spinMin->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    widget->setCellWidget(row, TableColumn_Min, spinMin);

    // max
    QSpinBox* spinMax = new QSpinBox();
    spinMax->setRange(0x80000000, 0x7FFFFFFF);
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

QString MainWindow::makeAlarmScript() const
{
    QString result;

    int count = ui->spinBox_AlarmCount->value();

    for( int i = 0; i < count; i++ )
    {
        QString devAddr = ui->lineEditDevAddr->text();
        QString virAddr = ui->lineEditVirAddr->text();

        for( int j = 0; j < ui->tableWidgetDevParams->rowCount(); j++ )
        {
            QSpinBox* itemVal = static_cast<QSpinBox*>(ui->tableWidgetDevParams->cellWidget(j, TableColumn_Def));
            QSpinBox* itemInc = static_cast<QSpinBox*>(ui->tableWidgetDevParams->cellWidget(j, TableColumn_Inc));
            QSpinBox* itemIncPer = static_cast<QSpinBox*>(ui->tableWidgetDevParams->cellWidget(j, TableColumn_IncPer));
            QComboBox* itemBase = static_cast<QComboBox*>(ui->tableWidgetDevParams->cellWidget(j, TableColumn_Base));
            QSpinBox* itemWidth = static_cast<QSpinBox*>(ui->tableWidgetDevParams->cellWidget(j, TableColumn_Width));
            QCheckBox* itemRange = static_cast<QCheckBox*>(ui->tableWidgetDevParams->cellWidget(j, TableColumn_Range));
            QSpinBox* itemMin = static_cast<QSpinBox*>(ui->tableWidgetDevParams->cellWidget(j, TableColumn_Min));
            QSpinBox* itemMax = static_cast<QSpinBox*>(ui->tableWidgetDevParams->cellWidget(j, TableColumn_Max));

            if( itemVal == NULL || itemInc == NULL || itemBase == NULL || itemWidth == NULL || itemRange == NULL || itemMin == NULL || itemMax == NULL ) { break; }

            int val = itemVal->value();
            int inc = itemInc->value();
            int incPer = itemIncPer->value();
            int base = (itemBase->currentText() == "DEC") ? 10 : 16;
            int width = itemWidth->value();
            bool useRange = itemRange->isChecked();
            int min = itemMin->value();
            int max = itemMax->value();

            val += inc * (i / incPer);

            if( useRange ) {
                val = (val % max) + min;
            }

            devAddr = devAddr.arg(val, width, base, QChar('0'));
        }

        for( int j = 0; j < ui->tableWidgetVirParams->rowCount(); j++ )
        {
            QSpinBox* itemVal = static_cast<QSpinBox*>(ui->tableWidgetVirParams->cellWidget(j, TableColumn_Def));
            QSpinBox* itemInc = static_cast<QSpinBox*>(ui->tableWidgetVirParams->cellWidget(j, TableColumn_Inc));
            QSpinBox* itemIncPer = static_cast<QSpinBox*>(ui->tableWidgetVirParams->cellWidget(j, TableColumn_IncPer));
            QComboBox* itemBase = static_cast<QComboBox*>(ui->tableWidgetVirParams->cellWidget(j, TableColumn_Base));
            QSpinBox* itemWidth = static_cast<QSpinBox*>(ui->tableWidgetVirParams->cellWidget(j, TableColumn_Width));
            QCheckBox* itemRange = static_cast<QCheckBox*>(ui->tableWidgetVirParams->cellWidget(j, TableColumn_Range));
            QSpinBox* itemMin = static_cast<QSpinBox*>(ui->tableWidgetVirParams->cellWidget(j, TableColumn_Min));
            QSpinBox* itemMax = static_cast<QSpinBox*>(ui->tableWidgetVirParams->cellWidget(j, TableColumn_Max));

            if( itemVal == NULL || itemInc == NULL || itemBase == NULL || itemWidth == NULL || itemRange == NULL || itemMin == NULL || itemMax == NULL ) { break; }

            int val = itemVal->value();
            int inc = itemInc->value();
            int incPer = itemIncPer->value();
            int base = (itemBase->currentText() == "DEC") ? 10 : 16;
            int width = itemWidth->value();
            bool useRange = itemRange->isChecked();
            int min = itemMin->value();
            int max = itemMax->value();

            val += inc * (i / incPer);

            if( useRange ) {
                val = (val % max) + min;
            }

            virAddr = virAddr.arg(val, width, base, QChar('0'));
        }

        QString condition = QString("if( %1 != %2 )").arg(devAddr).arg(virAddr);
        QString line1 = QString("\tHsmsAlarmReport(%1, %2)").arg(ui->spinBox_AlarmId->value()).arg(devAddr);
        QString line2 = QString("\t%1 = %2;").arg(virAddr).arg(devAddr);

        result += condition + "\r";
        result += "{\r";
        result += line1 + "\r";
        result += line2 + "\r";
        result += "}\r\r";
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
    QString devAddr = ui->lineEditDevAddr->text();
    QString virAddr = ui->lineEditVirAddr->text();

    for( int i = 0; i < ui->tableWidgetDevParams->rowCount(); i++ )
    {
        QSpinBox* itemVal = static_cast<QSpinBox*>(ui->tableWidgetDevParams->cellWidget(i, TableColumn_Def));
        QComboBox* itemBase = static_cast<QComboBox*>(ui->tableWidgetDevParams->cellWidget(i, TableColumn_Base));
        QSpinBox* itemWidth = static_cast<QSpinBox*>(ui->tableWidgetDevParams->cellWidget(i, TableColumn_Width));

        if( itemVal == NULL || itemBase == NULL || itemWidth == NULL ) { break; }

        int val = itemVal->value();
        int base = (itemBase->currentText() == "DEC") ? 10 : 16;
        int width = itemWidth->value();

        devAddr = devAddr.arg(val, width, base, QChar('0'));
    }

    for( int i = 0; i < ui->tableWidgetVirParams->rowCount(); i++ )
    {
        QSpinBox* itemVal = static_cast<QSpinBox*>(ui->tableWidgetVirParams->cellWidget(i, TableColumn_Def));
        QComboBox* itemBase = static_cast<QComboBox*>(ui->tableWidgetVirParams->cellWidget(i, TableColumn_Base));
        QSpinBox* itemWidth = static_cast<QSpinBox*>(ui->tableWidgetVirParams->cellWidget(i, TableColumn_Width));

        if( itemVal == NULL || itemBase == NULL || itemWidth == NULL ) { break; }

        int val = itemVal->value();
        int base = (itemBase->currentText() == "DEC") ? 10 : 16;
        int width = itemWidth->value();

        virAddr = virAddr.arg(val, width, base, QChar('0'));
    }

    QString condition = QString("if( %1 != %2 )").arg(devAddr).arg(virAddr);
    QString line1 = QString("\tHsmsAlarmReport(%1, %2)").arg(ui->spinBox_AlarmId->value()).arg(devAddr);
    QString line2 = QString("\t%1 = %2;").arg(virAddr).arg(devAddr);

    ui->label_condition->setText(condition);
    ui->label_line1->setText(line1);
    ui->label_line2->setText(line2);
}

void MainWindow::onAddAlarmDevParam()
{
    addParameter(ui->tableWidgetDevParams);
}

void MainWindow::onDelAlarmDevParam()
{
    delParameter(ui->tableWidgetDevParams);
}

void MainWindow::onAddAlarmVirParam()
{
    addParameter(ui->tableWidgetVirParams);
}

void MainWindow::onDelAlarmVirParam()
{
    delParameter(ui->tableWidgetVirParams);
}