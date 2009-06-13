/* 
 * File:   fusefilldircontext.h
 * Author: erik
 *
 * Created on den 30 januari 2009, 13:36
 */

#ifndef _FUSEFILLDIRCONTEXT_H
#define	_FUSEFILLDIRCONTEXT_H

#include <fuse.h>

class FUSEFillDirContext {
public:
    FUSEFillDirContext(fuse_fill_dir_t filler, void *buf);
    FUSEFillDirContext(const FUSEFillDirContext& orig);
    virtual ~FUSEFillDirContext();

    fuse_fill_dir_t getFiller();
    void* getBuf();
private:
    fuse_fill_dir_t filler;
    void *buf;
};

#endif	/* _FUSEFILLDIRCONTEXT_H */

