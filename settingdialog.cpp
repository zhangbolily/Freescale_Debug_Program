#include "settingdialog.h"

#include <QtSerialPort/QSerialPortInfo>
#include <QIntValidator>
#include <QLineEdit>

static const char blankString[] = QT_TRANSLATE_NOOP("SettingsDialog", "N/A");

SettingDialog::SettingDialog(QWidget *parent) :
    QDialog(parent)
{
    uiIniate();

    intValidator = new QIntValidator(0, 4000000, this);

    this->setWindowTitle(tr("设置参数"));
    this->setWindowIcon(QIcon(":/image/icon.png"));

    baudRateBox->setInsertPolicy(QComboBox::NoInsert);

    connect(applyButton, &QPushButton::clicked,
            this, &SettingDialog::apply);
    connect(serialPortInfoListBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this, &SettingDialog::showPortInfo);
    connect(baudRateBox,  static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this, &SettingDialog::checkCustomBaudRatePolicy);
    connect(serialPortInfoListBox,  static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this, &SettingDialog::checkCustomDevicePathPolicy);

    fillPortsParameters();
    fillPortsInfo();

    updateSettings();
}

SettingDialog::~SettingDialog()
{
}

void SettingDialog::uiIniate()
{
    //Layouts
    leftLayout = new QGridLayout();
    rightLayout = new QGridLayout();
    mainLayout = new QGridLayout();
    horizontalLayout = new QHBoxLayout();
    horizontalLayout1 = new QHBoxLayout();
    horizontalSpacer = new QSpacerItem(96, 20, QSizePolicy::Expanding, QSizePolicy::Expanding);

    //PushButtons
    applyButton = new QPushButton(tr("应用"));

    //GroupBox
    additionalOptionsGroupBox = new QGroupBox(tr("其他选项"));
    parametersBox = new QGroupBox(tr("选择参数"));
    selectBox = new QGroupBox(tr("选择串口"));

    //CheckBox
    localEchoCheckBox = new QCheckBox(tr("本地回显"));
    localEchoCheckBox->setChecked(true);

    //ComboBox
    baudRateBox = new QComboBox();
    dataBitsBox = new QComboBox();
    flowControlBox = new QComboBox();
    parityBox = new QComboBox();
    stopBitsBox = new QComboBox();
    serialPortInfoListBox = new QComboBox();

    //Labels
    baudRateLabel = new QLabel(tr("波特率:"));
    dataBitsLabel = new QLabel(tr("数据位:"));
    flowControlLabel = new QLabel(tr("流控制:"));
    parityLabel = new QLabel(tr("校验位:"));
    stopBitsLabel = new QLabel(tr("停止位:"));
    descriptionLabel = new QLabel();
    locationLabel = new QLabel();
    manufacturerLabel = new QLabel();
    pidLabel = new QLabel();
    serialNumberLabel = new QLabel(tr("串口:"));
    vidLabel = new QLabel();

    //Layout all of the items.
    leftLayout->addWidget(serialPortInfoListBox, 0, 0);
    leftLayout->addWidget(descriptionLabel, 1, 0);
    leftLayout->addWidget(manufacturerLabel, 2, 0);
    leftLayout->addWidget(serialNumberLabel, 3, 0);
    leftLayout->addWidget(locationLabel, 4, 0);
    leftLayout->addWidget(vidLabel, 5, 0);
    leftLayout->addWidget(pidLabel, 6, 0);

    selectBox->setLayout(leftLayout);

    rightLayout->addWidget(baudRateLabel, 0, 0);
    rightLayout->addWidget(baudRateBox, 0, 1);
    rightLayout->addWidget(dataBitsLabel, 1, 0);
    rightLayout->addWidget(dataBitsBox, 1, 1);
    rightLayout->addWidget(parityLabel, 2, 0);
    rightLayout->addWidget(parityBox, 2, 1);
    rightLayout->addWidget(stopBitsLabel, 3, 0);
    rightLayout->addWidget(stopBitsBox, 3, 1);
    rightLayout->addWidget(flowControlLabel, 4, 0);
    rightLayout->addWidget(flowControlBox, 4, 1);

    parametersBox->setLayout(rightLayout);

    horizontalLayout1->addWidget(localEchoCheckBox);
    additionalOptionsGroupBox->setLayout(horizontalLayout1);

    horizontalLayout->addItem(horizontalSpacer);
    horizontalLayout->addWidget(applyButton);

    mainLayout->addWidget(selectBox, 0, 0);
    mainLayout->addWidget(parametersBox, 0, 1);
    mainLayout->addWidget(additionalOptionsGroupBox, 1, 0, 1, 2);
    mainLayout->addLayout(horizontalLayout, 2, 0, 1, 2);

    this->setLayout(mainLayout);
}

SettingDialog::Settings SettingDialog::settings() const
{
    return currentSettings;
}

void SettingDialog::showPortInfo(int idx)
{
    if (idx == -1)
        return;

    QStringList list = serialPortInfoListBox->itemData(idx).toStringList();
    descriptionLabel->setText(tr("描述: %1").arg(list.count() > 1 ? list.at(1) : tr(blankString)));
    manufacturerLabel->setText(tr("制造商: %1").arg(list.count() > 2 ? list.at(2) : tr(blankString)));
    serialNumberLabel->setText(tr("串口号: %1").arg(list.count() > 3 ? list.at(3) : tr(blankString)));
    locationLabel->setText(tr("位置: %1").arg(list.count() > 4 ? list.at(4) : tr(blankString)));
    vidLabel->setText(tr("供应商识别号: %1").arg(list.count() > 5 ? list.at(5) : tr(blankString)));
    pidLabel->setText(tr("制造商识别号: %1").arg(list.count() > 6 ? list.at(6) : tr(blankString)));
}

void SettingDialog::apply()
{
    updateSettings();
    hide();
}

void SettingDialog::checkCustomBaudRatePolicy(int idx)
{
    bool isCustomBaudRate = !baudRateBox->itemData(idx).isValid();
    baudRateBox->setEditable(isCustomBaudRate);
    if (isCustomBaudRate) {
        baudRateBox->clearEditText();
        QLineEdit *edit = baudRateBox->lineEdit();
        edit->setValidator(intValidator);
    }
}

void SettingDialog::checkCustomDevicePathPolicy(int idx)
{
    bool isCustomPath = !serialPortInfoListBox->itemData(idx).isValid();
    serialPortInfoListBox->setEditable(isCustomPath);
    if (isCustomPath)
        serialPortInfoListBox->clearEditText();
}

void SettingDialog::fillPortsParameters()
{
    baudRateBox->addItem(QStringLiteral("9600"), QSerialPort::Baud9600);
    baudRateBox->addItem(QStringLiteral("19200"), QSerialPort::Baud19200);
    baudRateBox->addItem(QStringLiteral("38400"), QSerialPort::Baud38400);
    baudRateBox->addItem(QStringLiteral("115200"), QSerialPort::Baud115200);
    baudRateBox->addItem(tr("Custom"));

    dataBitsBox->addItem(QStringLiteral("5"), QSerialPort::Data5);
    dataBitsBox->addItem(QStringLiteral("6"), QSerialPort::Data6);
    dataBitsBox->addItem(QStringLiteral("7"), QSerialPort::Data7);
    dataBitsBox->addItem(QStringLiteral("8"), QSerialPort::Data8);
    dataBitsBox->setCurrentIndex(3);

    parityBox->addItem(tr("None"), QSerialPort::NoParity);
    parityBox->addItem(tr("Even"), QSerialPort::EvenParity);
    parityBox->addItem(tr("Odd"), QSerialPort::OddParity);
    parityBox->addItem(tr("Mark"), QSerialPort::MarkParity);
    parityBox->addItem(tr("Space"), QSerialPort::SpaceParity);

    stopBitsBox->addItem(QStringLiteral("1"), QSerialPort::OneStop);
#ifdef Q_OS_WIN
    stopBitsBox->addItem(tr("1.5"), QSerialPort::OneAndHalfStop);
#endif
    stopBitsBox->addItem(QStringLiteral("2"), QSerialPort::TwoStop);

    flowControlBox->addItem(tr("None"), QSerialPort::NoFlowControl);
    flowControlBox->addItem(tr("RTS/CTS"), QSerialPort::HardwareControl);
    flowControlBox->addItem(tr("XON/XOFF"), QSerialPort::SoftwareControl);
}

void SettingDialog::fillPortsInfo()
{
    serialPortInfoListBox->clear();
    QString description;
    QString manufacturer;
    QString serialNumber;
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        QStringList list;
        description = info.description();
        manufacturer = info.manufacturer();
        serialNumber = info.serialNumber();
        list << info.portName()
             << (!description.isEmpty() ? description : blankString)
             << (!manufacturer.isEmpty() ? manufacturer : blankString)
             << (!serialNumber.isEmpty() ? serialNumber : blankString)
             << info.systemLocation()
             << (info.vendorIdentifier() ? QString::number(info.vendorIdentifier(), 16) : blankString)
             << (info.productIdentifier() ? QString::number(info.productIdentifier(), 16) : blankString);

        serialPortInfoListBox->addItem(list.first(), list);
    }

    serialPortInfoListBox->addItem(tr("Custom"));

    serialPortInfoListBox->setCurrentText(currentSettings.name);
}

void SettingDialog::updateSettings()
{
    currentSettings.name = serialPortInfoListBox->currentText();

    if (baudRateBox->currentIndex() == 4) {
        currentSettings.baudRate = baudRateBox->currentText().toInt();
    } else {
        currentSettings.baudRate = static_cast<QSerialPort::BaudRate>(
                    baudRateBox->itemData(baudRateBox->currentIndex()).toInt());
    }
    currentSettings.stringBaudRate = QString::number(currentSettings.baudRate);

    currentSettings.dataBits = static_cast<QSerialPort::DataBits>(
                dataBitsBox->itemData(dataBitsBox->currentIndex()).toInt());
    currentSettings.stringDataBits = dataBitsBox->currentText();

    currentSettings.parity = static_cast<QSerialPort::Parity>(
                parityBox->itemData(parityBox->currentIndex()).toInt());
    currentSettings.stringParity = parityBox->currentText();

    currentSettings.stopBits = static_cast<QSerialPort::StopBits>(
                stopBitsBox->itemData(stopBitsBox->currentIndex()).toInt());
    currentSettings.stringStopBits = stopBitsBox->currentText();

    currentSettings.flowControl = static_cast<QSerialPort::FlowControl>(
                flowControlBox->itemData(flowControlBox->currentIndex()).toInt());
    currentSettings.stringFlowControl = flowControlBox->currentText();

    currentSettings.localEchoEnabled = localEchoCheckBox->isChecked();
}
