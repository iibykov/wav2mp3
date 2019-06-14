#pragma once

#include <QObject>
#include <QFile>
#include <QAudioFormat>

#include "wavHeader.h"

class WavFile : public QFile
{
public:
    WavFile(QObject *parent = nullptr);

    using QFile::open;
    bool open(const QString &fileName);
    qint64 headerLength() const;
    CombinedHeader combinedHeader();

private:
    bool readHeader();

private:
    QAudioFormat m_fileFormat;
    CombinedHeader m_header;
    qint64 m_headerLength;
};
