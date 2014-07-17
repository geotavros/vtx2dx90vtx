#include <iostream>
//#include <cstdio>

#include <QtCore/QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QFile>

void processDirectory(const QString &dir, const char *format)
{
    {
        QDir qdir(dir);
        qdir.setNameFilters(QStringList("*.vtx"));

        QFileInfoList files = qdir.entryInfoList(QDir::Files);
        for (int i = 0; i < files.count(); ++i)
        {
            qDebug() << files.at(i).absoluteFilePath();
            QString new_name = files.at(i).absolutePath() + "/" + files.at(i).baseName() + format;
            qDebug() << new_name;
            
            QFile::copy(files.at(i).absoluteFilePath(), new_name);
        }
    }
    
    {
        QDir directories(dir, "", QDir::Name | QDir::IgnoreCase , QDir::Dirs | QDir::NoDotAndDotDot);
        QFileInfoList dirs = directories.entryInfoList();
        for (int i = 0; i < dirs.count(); ++i)
        {
            qDebug() << dirs.at(i).absoluteFilePath();
            processDirectory(dirs.at(i).absoluteFilePath(), format);
        }
    }
    
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Syntax:\nvtx2dx90vtx <path to dir> [file extension]\n"
        "<path to dir> is a path to directory that contains *.vtx files.\n"
        "All subdirectories will be parsed too\n" 
        "[file extension] is optional and by default is .dx90.vtx. "
        "You can specify .dx80.vtx for example\n";
        return 0;
    }
    const char *format = ".dx90.vtx";
    if (argc >= 3)
    {
        format = argv[2];
    }
    QCoreApplication a(argc, argv);

    processDirectory(argv[1], format);
    std::cout << "Finished!\n";

    int result = a.exec();

//     if (argc >= 4)
//     {
//         std::getchar();
//     }
}
