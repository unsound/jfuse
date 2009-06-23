#include "FUSEDirFilContext.h"

FUSEDirFilContext::FUSEDirFilContext(fuse_dirfil_t dirFil, fuse_dirh_t handle) {
    this->dirFil = dirFil;
    this->handle = handle;
}

FUSEDirFilContext::FUSEDirFilContext(const FUSEDirFilContext& orig) {
    this->dirFil = orig.dirFil;
    this->handle = orig.handle;
}

FUSEDirFilContext::~FUSEDirFilContext() {
}

fuse_dirfil_t FUSEDirFilContext::getDirFil() {
    return dirFil;
}

fuse_dirh_t FUSEDirFilContext::getHandle() {
    return handle;
}

