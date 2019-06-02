#pragma once

#include <QCommandLineParser>
#include <QDirIterator>

enum CommandLineParseResult
{
    CommandLineOk,
    CommandLineError,
    CommandLineVersionRequested,
    CommandLineHelpRequested
};

class CommandLineParser : public QCommandLineParser
{
public:
    CommandLineParser();
    CommandLineParseResult parseCommandLine(QString &errorMessage);
    QString wavPath() const;
    QString mp3Path() const;
    QDirIterator::IteratorFlag procSubDirs() const;

private:
    QString m_wavPath;
    QString m_mp3Path;
    QDirIterator::IteratorFlag m_procSubDirs;
};


