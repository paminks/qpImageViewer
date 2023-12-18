#ifndef FILES_H
#define FILES_H

#include <QStringList>


class Files
{
public:
    Files();


    void setExtensions(const QStringList& extensions);
    void openFile(const QString& fullPath);

    QString nextFile();
    QString previousFile();

    bool hasNestFile();
    bool hasPreviousFile();

    QString getCurrentFilename();

private:
    QStringList fileNamesInCurrentPath;

    QString currentFilePath;
    QString currentFileName;

    bool hasNext = false;
    bool hasPrevious = false;

    QStringList supportedExtensions;

};

#endif // FILES_H
