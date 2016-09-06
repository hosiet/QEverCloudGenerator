#include <QCoreApplication>
#include "Lexer.h"
#include <QDir>
#include <QtDebug>
#include "Parser.h"
#include "Generator.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    try
    {
        if (qApp->arguments().length() != 3) {
            throw std::runtime_error("Incorrect arguments (thriftDir generatedDir)");
        }

        QString thriftDir = qApp->arguments().at(1);
        QString generatedDir = qApp->arguments().at(2);

        Lexer * lexer = new Lexer(&app);
        QDir dir(thriftDir);
        for(QString thriftFile : dir.entryList(QStringList() << "*.thrift", QDir::Files, QDir::Name)) {
            lexer->feedFile(dir.absoluteFilePath(thriftFile));
        }

        Parser * parser = new Parser(&app);
        for(const Lexer::TerminalSymbol & term : lexer->terminals())
        {
            parser->setFile(term.file);
            //qDebug() << term.file << term.line << term.data;
            parser->feed(term.type, term.data);
            if(parser->isError()) {
                throw std::runtime_error(QString("%4 in file %1 at line %2: %3\ndetected token type: %5").arg(term.file).arg(term.line).arg(term.data)
                                         .arg(parser->errorMessage()).arg(static_cast<int>(term.type)).toStdString());
            }
        }

        parser->complete();
        if(parser->isError()) {
            throw std::runtime_error(QString("Parser error at completion: %1").arg(parser->errorMessage()).toStdString());
        }

        generateSources(parser, generatedDir);
    }
    catch(const std::exception & e)
    {
        qDebug() << "\nFAILURE!!!";
        qDebug() << e.what();
        return 1;
    }
    catch(...)
    {
        qDebug() << "\nFAILURE!!! Unknown exception\n";
        return 2;
    }

    return 0;
}
