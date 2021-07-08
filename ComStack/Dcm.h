#ifndef DCM_H
#define DCM_H

#include <QObject>
#include <QVector>
#include <QString>

/**
 * @brief The Dcm class
 * Diagnostic command manager, it used to
 * - Send diagnostic command;
 * - Implement the UDS reprogramming;
 */
class Dcm : public QObject
{
    Q_OBJECT
public:
    explicit Dcm(QObject *parent = nullptr);

signals:
    void transmit(const QVector<QString> &dspItems);
public slots:

};

#endif // DCM_H
