#include "cpuusagefetcher.h"

#include <QDebug>

CpuUsageFetcher::CpuUsageFetcher(QObject *parent) :
    BaseFetcher(parent)
{
    _query = QStringList() << "cpu" << "get" << "loadpercentage";

}

/*!
 * reimpl
 */
void CpuUsageFetcher::run()
{
    forever
    {
        QProcess pro;
        pro.setProcessChannelMode(QProcess::MergedChannels);
        pro.start(kProcess,query());
        pro.waitForFinished();
        QString strOutput(pro.readAllStandardOutput());
        QStringList infoList = strOutput.split('\n');
        infoList.removeFirst();
        infoList.removeLast();
        infoList.removeLast();

        if(infoList.size() == 1)
        {
            QString strUsage(infoList.at(0));
            bool ok = false;
            int usage = strUsage.toInt(&ok);
            if(ok)
            {
                emit sig_setCpuUsage(usage);
            }
        }
        sleep(interval());
    }
}
