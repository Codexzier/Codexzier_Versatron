//
// Created by codexzier on 22.06.26.
//

#pragma once

#ifndef CODEXZIER_VERSATRON_SUBFILEMANAGER_H
#define CODEXZIER_VERSATRON_SUBFILEMANAGER_H

#include <FS.h>
#include <string>
#include <vector>
#include <memory>

class SubFileManager {

    std::unique_ptr<std::vector<std::string>> _filenames;
    std::string _viewFilename;

    int _viewIndex = 0;

    uint16_t GetNextPixelColorValue(File &file);

    void readSdCard();
    bool _sdSuccess = false;
public:

    void init();

    void writeFile(const char * path, uint8_t * data, size_t len);
    void readFiles();

    int GetCountPictures();
    int GetCardSizeMb();
    uint8_t* GetPictureData(int index);
    bool IsSdCardInit();
};


#endif //CODEXZIER_VERSATRON_SUBFILEMANAGER_H
