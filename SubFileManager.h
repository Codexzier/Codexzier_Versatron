//
// Created by codexzier on 22.06.26.
//

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
public:

    void init();


};


#endif //CODEXZIER_VERSATRON_SUBFILEMANAGER_H
