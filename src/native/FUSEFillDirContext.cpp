/* 
 * File:   fusefilldircontext.cpp
 * Author: erik
 * 
 * Created on den 30 januari 2009, 13:36
 */

#include "FUSEFillDirContext.h"

FUSEFillDirContext::FUSEFillDirContext(fuse_fill_dir_t filler, void *buf) {
    this->filler = filler;
    this->buf = buf;
}

FUSEFillDirContext::FUSEFillDirContext(const FUSEFillDirContext& orig) {
    this->filler = orig.filler;
    this->buf = orig.buf;
}

FUSEFillDirContext::~FUSEFillDirContext() {
}

fuse_fill_dir_t FUSEFillDirContext::getFiller() {
    return filler;
}

void* FUSEFillDirContext::getBuf() {
    return buf;
}
