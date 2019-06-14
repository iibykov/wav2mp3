#include <qendian.h>
#include "wavfile.h"

WavFile::WavFile(QObject *parent)
    : QFile(parent)
    , m_headerLength(0)
{
}

bool WavFile::open(const QString &fileName)
{
    close();
    setFileName(fileName);

    return QFile::open(QIODevice::ReadOnly) && readHeader();
}

qint64 WavFile::headerLength() const
{
    return m_headerLength;
}

CombinedHeader WavFile::combinedHeader()
{
    return m_header;
}

bool WavFile::readHeader()
{
    seek(0);

    CombinedHeader header;
    bool result = read(reinterpret_cast<char *>(&header),
                       sizeof(CombinedHeader)) == sizeof(CombinedHeader);

    if (result)
    {
        if ((memcmp(&header.riff.descriptor.id, "RIFF", 4) == 0
            || memcmp(&header.riff.descriptor.id, "RIFX", 4) == 0)
            && memcmp(&header.riff.type, "WAVE", 4) == 0
            && memcmp(&header.wave.descriptor.id, "fmt ", 4) == 0
            && (header.wave.audioFormat == 1 || header.wave.audioFormat == 0))
        {

            // Read off remaining header information
            DATAHeader dataHeader;

            if (qFromLittleEndian<quint32>(header.wave.descriptor.size) > sizeof(FMT))
            {
                // Extended data available
                quint16 extraFormatBytes;
                if (peek(reinterpret_cast<char *>(&extraFormatBytes), sizeof(quint16)) != sizeof(quint16))
                    return false;

                const qint64 throwAwayBytes = sizeof(quint16) + qFromLittleEndian<quint16>(extraFormatBytes);
                if (read(throwAwayBytes).size() != throwAwayBytes)
                    return false;
            }

            if (read(reinterpret_cast<char *>(&dataHeader), sizeof(DATAHeader)) != sizeof(DATAHeader))
                return false;
        }
        else
        {
            result = false;
        }
    }

    m_headerLength = pos();
    m_header = header;

    return result;
}
