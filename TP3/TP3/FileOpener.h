/*****************************************************************************
File  : FileOpener.h
Author: Anthony Cote
Date  : 2018-11-13
Goal  : Ouvre un fichier
******************************************************************************/
#pragma once

#include <fstream>
#include <iostream>
#include <String>

#include "pch.h"

using namespace std;

class FileOpener
{
protected:
    const char* _fileName;
    ifstream _ifs;

public:
    FileOpener(const char * fileName = nullptr);    //
    ~FileOpener();                                  //

    bool reOpen();                                  //
    bool openFile(const char* fileName);            //
    bool isValidFile();                             //

    // Ces fonctions sont juste un rappel de comment les utiliser
    int getInt();
    char getChar();
    char getCharNoSkipWhiteSpace();
    string getString();

    // TODO optionnel creer des operator>> pour les type de variable: int, char, string, ...
};
