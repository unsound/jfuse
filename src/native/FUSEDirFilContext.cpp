/*-
 * jFUSE - FUSE bindings for Java
 * Copyright (C) 2008-2009  Erik Larsson <erik82@kth.se>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

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

