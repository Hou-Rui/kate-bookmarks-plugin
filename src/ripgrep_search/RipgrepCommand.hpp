#pragma once

#include <QObject>
#include <QProcess>

class RipgrepCommand : public QProcess
{
    Q_OBJECT
public:
    struct Result {
        struct Submatch {
            int start;
            int end;
        };
        QString fileName;
        int lineNumber;
        QString line;
        QList<Submatch> submatches;
    };

    explicit RipgrepCommand(QObject *parent);
    ~RipgrepCommand();

public slots:
    void searchInDir(const QString &term, const QString &dir);
    void searchInFiles(const QString &term, const QList<QString> &files);

    void setWholeWord(bool newValue);
    void setCaseSensitive(bool newValue);
    void setUseRegex(bool newValue);

signals:
    void matchFoundInFile(const QString &path);
    void matchFound(Result result);
    void searchOptionsChanged();

private:
    using QProcess::setArguments;
    using QProcess::setProgram;
    using QProcess::start;
    using QProcess::startCommand;

    void ensureStopped();
    void parseMatch(const QByteArray &match);
    void search(const QString &term, const QString &dir, const QList<QString> &files);

    struct SearchOptions {
        bool wholeWord = false;
        bool caseSensitive = false;
        bool useRegex = false;
    } m_options;
};