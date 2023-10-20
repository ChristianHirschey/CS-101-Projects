#include <iostream>
#include <string>

#include "p3.h"

using namespace std;

Region::Region() {
    this->name = "No Name Set";
    this->viewers = 0;
    this->next = nullptr;
}

Region::Region(std::string name, int viewers, Region *next) {
    this->name = name;
    this->viewers = viewers;
    this->next = next;
}

Media::Media() {
    this->name = "No Name Set";
    this->next = nullptr;
    this->headRegionList = nullptr;
}

Media::Media(std::string name, Media *next) {
    this->name = name;
    this->next = next;
    this->headRegionList = nullptr;
}

MediaList::MediaList() {
    this->headMediaList = nullptr;
    this->count = 0;
}

int MediaList::getCount() {
    return this->count;
}

// print the specified media and its regions
// 1. return false and print nothing if the media is not in the list
// 2. otherwise return true and print the media and its regions
bool MediaList::printMedia(std::ostream &os, std::string name) {
    if(!isInList(name)) return false;
    Media *m = headMediaList;

    os << "Media Name: " << name << endl;

    while(m) {
        if(m->name == name) break;
        else m = m->next;
    }

    Region *r = m->headRegionList;
    while(r){
        os << "\t" << r->name << " | " << r->viewers << endl;
        r = r->next;
    }
    return true;
}

// print all media and their regions
// print nothing if the list is empty
void MediaList::print(std::ostream &os) {
    if(headMediaList != nullptr){
        Media *m = headMediaList;
        while(m) {
            Region *r = m->headRegionList;
            os << "Media Name: " << m->name << endl;
            while(r) {
                os << "\t" << r->name << " | " << r->viewers << endl;
                r = r->next;
            }
            m = m->next;
        }
    }
}

// add the media to the back of the list
// 1. return false and do nothing if the media is already in the list
// 2. otherwise return true and add the media to the back of the list
bool MediaList::addMedia(std::string name) {
    if(isInList(name)) return false;
    Media *m = new Media(name, nullptr);
    if(headMediaList == nullptr) {
        headMediaList = m;
    }
    else {
        Media *last = headMediaList;
        while(last->next) last = last->next;
        last->next = m;
    }
    count++;
    return true;
}

// add the region to the back of the media's region list
// 1. return false and do nothing if the media is not in the list
// 2. if the regionName is already in the region list, update the viewers and return true
// 3. otherwise add the region to the back of the media's list and return true
bool MediaList::addRegion(std::string mediaName, std::string regionName, int viewers) {
    if(!isInList(mediaName)) return false;
    Media *m = headMediaList;
    while(m) {
        if(m->name == mediaName) break;
        else m = m->next;
    }

    Region *r = new Region(regionName, viewers, nullptr);
    Region *last = m->headRegionList;

    while(last) {
        if(last->name == regionName) {
            last->viewers = viewers;
            return true;
        }
        last = last->next;
    }


    if(m->headRegionList == nullptr){
        m->headRegionList = r;
    }
    else {
        last = m->headRegionList;
        while(last->next) last = last->next;
        last->next = r;
    }
    return true;
}

// add the media to the list in ascending order by name
// 1. return false and do nothing if the media is already in the list
// 2. otherwise return true and add the media to the list
bool MediaList::addMediaOrdered(std::string name) {
    if(isInList(name)) return false;

    Media *newM = new Media(name, nullptr);

    if(headMediaList == nullptr || name < headMediaList->name) {
        newM->next = headMediaList;
        newM->headRegionList = nullptr;
        headMediaList = newM;
    }
    else {
        Media *m = headMediaList;
        while(m->next != nullptr && name > m->next->name) {
            m = m->next;
        }
        newM->next = m->next;
        newM->headRegionList = nullptr;
        m->next = newM;
    }
    count++;
    return true;
}

// add the region to the media's region list in descending order by viewers
// 1. return false and do nothing if the media is not in the list
// 2. if the regionName is already in the region list, update the viewers and return true
// 3. otherwise add the region to the media's list and return true
bool MediaList::addRegionOrdered(std::string mediaName, std::string regionName, int viewers) {
    if(!isInList(mediaName)) return false;

    Media *m = headMediaList;
    while(m) {
        if(m->name == mediaName) break;
        else m = m->next;
    }

    Region *r = new Region(regionName, viewers, nullptr);
    Region *prev = nullptr;
    Region *ind = m->headRegionList;

    while(ind) { // checks if Region r is already in RegionList
        if(ind->name == regionName) {
            ind->viewers = viewers;
            return true;
        }
        ind = ind->next;
    }

    ind = m->headRegionList;

    while(ind && viewers < ind->viewers) {
        prev = ind;
        ind = ind->next;
    }

    if(prev) {
        prev->next = r;
    }
    else {
        m->headRegionList = r;
    }
    r->next = ind;
    return true;
}

// remove the media and its regions from the list
// 1. return false and do nothing if the media is not in the list
// 2. otherwise return true and remove the media and its regions
bool MediaList::removeMedia(std::string name) {
    if(!isInList(name)) return false;

    Media *m = headMediaList;
    Media *prev = nullptr;

    while(m) {
        if(m->name == name) break;
        else {
            prev = m;
            m = m->next;
        }
    }


    if(m) {
        Region *r = m->headRegionList;
        while(r) {
            Region *temp = r;
            r = r->next;
            delete temp;
        }

        if(prev) {
            prev->next = m->next;
        }
        else {
            headMediaList = m->next;
        }
        delete m;
        count--;
        return true;
    }
    return false;
}

// remove the region from the media's region list
// 1. return false and do nothing if the media is not in the list
// 2. return false and do nothing if the region is not in the media's region list
// 3. otherwise return true and remove the region from the media's list
bool MediaList::removeRegion(std::string mediaName, std::string regionName) {
    if (!isInList(mediaName)) return false;

    Media *m = headMediaList;
    while (m) {
        if (m->name == mediaName) {
            Region *prev = nullptr;
            Region *r = m->headRegionList;
            while (r) {
                if (r->name == regionName) {
                    if (prev) {
                        prev->next = r->next;
                    } else {
                        m->headRegionList = r->next;
                    }
                    delete r;
                    return true;
                }
                prev = r;
                r = r->next;
            }
        }
        m = m->next;
    }
    return false;
}

// destroy the list by removing all media and their regions
MediaList::~MediaList() {
    Media *m = headMediaList;
    while(m) {
        Media *tempM = m;
        m = m->next;

        Region *r = tempM->headRegionList;
        while(r) {
            Region *tempR = r;
            r = r->next;
            delete tempR;
        }
        delete tempM;
    }
}

// deep copy the source list
MediaList::MediaList(const MediaList &src) {
    if(this != &src) {
        Media *srcM = src.headMediaList;
        Media *curr = nullptr;
        while(srcM) {
            Media *m = new Media(srcM->name, nullptr);
            if(!headMediaList) headMediaList = m;
            else curr->next = m;
            curr = m;

            Region *srcR = srcM->headRegionList;
            Region *currR = nullptr;
            while(srcR) {
                Region *r = new Region(srcR->name, srcR->viewers, nullptr);
                if(!curr->headRegionList) curr->headRegionList = r;
                else currR->next = r;
                currR = r;
                srcR = srcR->next;
            }
            srcM = srcM->next;
            count++;
        }
    }
}

// remove all media and their regions then deep copy the source list
const MediaList &MediaList::operator=(const MediaList &src) {
    if (this != &src) {
        this->~MediaList(); // calls the destructor to free up space from current MediaList

        Media *srcM = src.headMediaList;
        Media *curr = nullptr;
        while(srcM) {
            Media *m = new Media(srcM->name, nullptr);
            if(!headMediaList) headMediaList = m;
            else curr->next = m;
            curr = m;

            Region *srcR = srcM->headRegionList;
            Region *currR = nullptr;
            while(srcR) {
                Region *r = new Region(srcR->name, srcR->viewers, nullptr);
                if(!curr->headRegionList) curr->headRegionList = r;
                else currR->next = r;
                currR = r;
                srcR = srcR->next;
            }
            srcM = srcM->next;
        }
        count = src.count;
    }
    return *this;
}

bool MediaList::isInList(std::string name) { // checks if a Media is in MediaList
    Media *m = headMediaList;
    while(m){
        if(m->name == name) return true;
        else m = m->next;
    }
    return false;
}