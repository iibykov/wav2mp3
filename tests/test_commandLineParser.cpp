#include <QtTest>
#include "../src/commandLineParser.h"


class TestCommandLineParser : public QObject
{
    Q_OBJECT

public:
    TestCommandLineParser();
    ~TestCommandLineParser();

public slots:
    void initTestCase();

private slots:
    void test_WithoutArguments();
    void test_ExtraArguments();
    void test_InvalidOptions();

};

static char *empty_argv[] = { nullptr };
static int empty_argc = 1;

TestCommandLineParser::TestCommandLineParser()
{

}

TestCommandLineParser::~TestCommandLineParser()
{

}

void TestCommandLineParser::initTestCase()
{
    Q_ASSERT(!empty_argv[0]);
    empty_argv[0] = const_cast<char*>(QTest::currentAppName());
}

Q_DECLARE_METATYPE(CommandLineParser::SingleDashWordOptionMode)

void TestCommandLineParser::test_WithoutArguments()
{
    QCoreApplication app(empty_argc, empty_argv);

    QString errorMessage;
    CommandLineParser parser;
    CommandLineParseResult res = parser.parseCommandLine(errorMessage);
    QCOMPARE(res, CommandLineError);
}

void TestCommandLineParser::test_ExtraArguments()
{
    char *extra_argv [3];
    extra_argv[0] = const_cast<char*>(QTest::currentAppName());
    extra_argv[1] = const_cast<char*>("arg1");
    extra_argv[2] = const_cast<char*>("arg2");

    static int extra_argc = 3;

    QCoreApplication app(extra_argc, extra_argv);

    QString errorMessage;
    CommandLineParser parser;
    CommandLineParseResult res = parser.parseCommandLine(errorMessage);
    QCOMPARE(res, CommandLineError);
}

void TestCommandLineParser::test_InvalidOptions()
{
    char *extra_argv [3];
    extra_argv[0] = const_cast<char*>(QTest::currentAppName());
    extra_argv[1] = const_cast<char*>("C:/Projects/wav2mp3/examples/wav");
    extra_argv[2] = const_cast<char*>("--invalidOption");

    static int extra_argc = 3;

    QCoreApplication app(extra_argc, extra_argv);

    QString errorMessage;
    CommandLineParser parser;
    CommandLineParseResult res = parser.parseCommandLine(errorMessage);
    QCOMPARE(res, CommandLineError);
}

QTEST_APPLESS_MAIN(TestCommandLineParser)

#include "test_commandLineParser.moc"
