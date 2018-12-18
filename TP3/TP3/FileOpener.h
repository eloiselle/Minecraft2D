/*****************************************************************************
File  : FileOpener.h
Author: Anthony Cote
Date  : 2018-11-13
Goal  : Ouvre un fichier de facon securitaire
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
    const char* _fileName;  // Nom du fichier
    ifstream _ifs;          // InputFileStream pour lire le fichier

public:
    FileOpener(const char * fileName = nullptr);    // Constructeur
    ~FileOpener();                                  // Destructeur

    bool reOpen();                                  // Reouvre le fichier
    bool openFile(const char* fileName);            // Ouvre le fichier
    bool isValidFile();                             // Verifi si le fichier est valid et non vide

    // Ces fonctions sont juste un rappel de comment les utiliser
    int getInt();                                   // Lit un int
    char getChar();                                 // Lit un char
    char getCharNoSkipWhiteSpace();                 // Lit un char sans eviter les whitespace
    string getString();                             // Lit un string

    // TODO optionnel creer des operator>> pour les type de variable: int, char, string, ...
};
