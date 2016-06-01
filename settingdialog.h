#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include <QtSerialPort/QSerialPort>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <QCheckBox>
#include <QComboBox>
#include <QPushButton>
#include <QSpacerItem>
#include <QGridLayout>

class QIntValidator;

class SettingDialog : public QDialog
{
    Q_OBJECT

public:
    struct Settings {
        QString name;
        qint32 baudRate;
        QString stringBaudRate;
        QSerialPort::DataBits dataBits;
        QString stringDataBits;
        QSerialPort::Parity parity;
        QString stringParity;
        QSerialPort::StopBits stopBits;
        QString stringStopBits;
        QSerialPort::FlowControl flowControl;
        QString stringFlowControl;
        bool localEchoEnabled;
    };

    explicit SettingDialog(QWidget *parent = 0);
    ~SettingDialog();

    Settings settings() const;

private slots:
    void showPortInfo(int idx);
    void apply();
    void checkCustomBaudRatePolicy(int idx);
    void checkCustomDevicePathPolicy(int idx);
    void fillPortsInfo();

private:
    void uiIniate();
    void fillPortsParameters();
    void updateSettings();

private:
    Settings currentSettings;
    QIntValidator *intValidator;

    //Layouts
    QGridLayout *leftLayout;
    QGridLayout *rightLayout;
    QGridLayout *mainLayout;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *horizontalLayout1;
    QSpacerItem *horizontalSpacer;

    //PushButtons
    QPushButton *applyButton;

    //GroupBox
    QGroupBox *additionalOptionsGroupBox;
    QGroupBox *parametersBox;
    QGroupBox *selectBox;

    //CheckBox
    QCheckBox *localEchoCheckBox;

    //ComboBox
    QComboBox *baudRateBox;
    QComboBox *dataBitsBox;
    QComboBox *flowControlBox;
    QComboBox *parityBox;
    QComboBox *stopBitsBox;
    QComboBox *serialPortInfoListBox;

    //Labels
    QLabel *baudRateLabel;
    QLabel *dataBitsLabel;
    QLabel *flowControlLabel;
    QLabel *parityLabel;
    QLabel *stopBitsLabel;
    QLabel *descriptionLabel;
    QLabel *locationLabel;
    QLabel *manufacturerLabel;
    QLabel *pidLabel;
    QLabel *serialNumberLabel;
    QLabel *vidLabel;
};

#endif // SETTINGSDIALOG_H
