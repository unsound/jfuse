/* 
 * File:   FUSEDirFilContext.h
 * Author: erik
 *
 * Created on den 23 juni 2009, 10:45
 */

#ifndef _FUSEDIRFILCONTEXT_H
#define	_FUSEDIRFILCONTEXT_H

#define FUSE_USE_VERSION 26
#include <fuse.h>

class FUSEDirFilContext {
public:
    FUSEDirFilContext(fuse_dirfil_t dirFil, fuse_dirh_t handle);
    FUSEDirFilContext(const FUSEDirFilContext& orig);
    virtual ~FUSEDirFilContext();

    fuse_dirfil_t getDirFil();
    fuse_dirh_t getHandle();
private:
    fuse_dirfil_t dirFil;
    fuse_dirh_t handle;
};

#endif	/* _FUSEDIRFILCONTEXT_H */

