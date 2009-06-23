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
