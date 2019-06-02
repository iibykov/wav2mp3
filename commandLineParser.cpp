#include <QDir>

#include "commandLineParser.h"

CommandLineParser::CommandLineParser()
{
    setSingleDashWordOptionMode(QCommandLineParser::ParseAsLongOptions);
}

CommandLineParseResult CommandLineParser::parseCommandLine(QString &errorMessage)
{
    const QCommandLineOption helpOption = addHelpOption();
    const QCommandLineOption versionOption = addVersionOption();

    addPositionalArgument("wavPath", "Path to wav collection");

    const QCommandLineOption mp3PathOption(QStringList() << "o" << "out", "Path to mp3 collection", "mp3Path");
    addOption(mp3PathOption);

    const QCommandLineOption SubDirOption(QStringList() << "s" << "sub", "Process wav files in subdirectories");
    addOption(SubDirOption);

    if (!parse(QCoreApplication::arguments()))
    {
        errorMessage = errorText();
        return CommandLineError;
    }

    if (isSet(versionOption))
        return CommandLineVersionRequested;

    if (isSet(helpOption))
        return CommandLineHelpRequested;

    const QStringList positionalArguments = this->positionalArguments();
    if (positionalArguments.isEmpty())
    {
        errorMessage = "Argument 'wavPath' missing.";
        return CommandLineError;
    }

    if (positionalArguments.size() > 1)
    {
        errorMessage = "Several 'wavPath' arguments specified.";
        return CommandLineError;
    }

    m_wavPath = positionalArguments.first();
    if (!QDir(m_wavPath).exists())
    {
        errorMessage = "Bad path to wav collection: " + m_wavPath;
        return CommandLineError;
    }

    m_procSubDirs = (isSet(SubDirOption)) ? QDirIterator::Subdirectories : QDirIterator::NoIteratorFlags;

    m_mp3Path = (isSet(mp3PathOption)) ? value(mp3PathOption) : m_wavPath;

    if (!QDir(m_mp3Path).exists())
    {
        errorMessage = "Bad path to mp3 collection: " + m_mp3Path;
        return CommandLineError;
    }

    return CommandLineOk;
}

QString CommandLineParser::wavPath() const
{
    return m_wavPath;
}

QString CommandLineParser::mp3Path() const
{
    return m_mp3Path;
}

QDirIterator::IteratorFlag CommandLineParser::procSubDirs() const
{
    return m_procSubDirs;
}
