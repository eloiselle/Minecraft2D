#include "FileOpener.h"

FileOpener::FileOpener(const char * fileName)
{
    if (fileName != nullptr)
        openFile(fileName);
}

FileOpener::~FileOpener()
{
    _ifs.close();
}

bool FileOpener::reOpen()
{
    return openFile(_fileName);
}

bool FileOpener::openFile(const char * fileName)
{
    _fileName = fileName;
    _ifs.open(fileName);

    return isValidFile();
}

bool FileOpener::isValidFile()
{
    return (_ifs.is_open() &&
        _ifs.peek() != ifstream::traits_type::eof()); // Pas a la fin
}

int FileOpener::getInt()
{
    int i;
    _ifs >> i;
    return i;
}

char FileOpener::getChar()
{
    char c;
    _ifs >> c;
    return c;
}

char FileOpener::getCharNoSkipWhiteSpace()
{
    char c;
    _ifs >> std::noskipws >> c;
    return c;
}

string FileOpener::getString()
{
    string str;
    getline(_ifs, str);
    return str;
}