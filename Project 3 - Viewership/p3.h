#ifndef _P3_H_
#define _P3_H_

#include <iostream>
#include <string>

class Region {
public:
    std::string name;
    int viewers;
    Region *next;

    Region();
    Region(std::string name, int viewers, Region *next = nullptr);
};

class Media {
public:
    std::string name;
    Media *next;
    Region *headRegionList;

    Media();
    Media(std::string name, Media *next = nullptr);
};

class MediaList {
private:
    Media *headMediaList;
    int count;
public:
    MediaList();

    int getCount();
    
    bool printMedia(std::ostream &os, std::string mediaName);
    void print(std::ostream &os);

    bool addMedia(std::string mediaName);
    bool addRegion(std::string mediaName, std::string regionName, int viewers);

    bool addMediaOrdered(std::string mediaName);
    bool addRegionOrdered(std::string mediaName, std::string regionName, int viewers);
    
    bool removeMedia(std::string mediaName);
    bool removeRegion(std::string mediaName, std::string regionName);

    ~MediaList();
    MediaList(const MediaList &src);
    const MediaList &operator=(const MediaList &src);

    bool isInList(std::string name);
};

#endif
