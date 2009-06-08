#include <fuse.h>
#include <fuse/fuse_common.h>
#include <errno.h>

#include "fuse_module.h"

static struct jfuse_context *context = NULL;

static int javaErrnoToErrno(jint javaErrno) {
    switch(javaErrno) {
        case 0: return 0; // All is fine.
        case 1: return EPERM;
        case 2: return ENOENT;
        case 3: return ESRCH;
        case 4: return EINTR;
        case 5: return EIO;
        case 6: return ENXIO;
        case 7: return E2BIG;
        case 8: return ENOEXEC;
        case 9: return EBADF;
        case 10: return ECHILD;
        case 11: return EDEADLK;
        case 12: return ENOMEM;
        case 13: return EACCES;
        case 14: return EFAULT;
        case 15: return ENOTBLK;
        case 16: return EBUSY;
        case 17: return EEXIST;
        case 18: return EXDEV;
        case 19: return ENODEV;
        case 20: return ENOTDIR;
        case 21: return EISDIR;
        case 22: return EINVAL;
        case 23: return ENFILE;
        case 24: return EMFILE;
        case 25: return ENOTTY;
        case 26: return ETXTBSY;
        case 27: return EFBIG;
        case 28: return ENOSPC;
        case 29: return ESPIPE;
        case 30: return EROFS;
        case 31: return EMLINK;
        case 32: return EPIPE;
        case 33: return EDOM;
        case 34: return ERANGE;
        case 35: return EAGAIN;
        case 102: return EWOULDBLOCK;
        case 36: return EINPROGRESS;
        case 37: return EALREADY;
        case 38: return ENOTSOCK;
        case 39: return EDESTADDRREQ;
        case 40: return EMSGSIZE;
        case 41: return EPROTOTYPE;
        case 42: return ENOPROTOOPT;
        case 43: return EPROTONOSUPPORT;
        case 44: return ESOCKTNOSUPPORT;
        case 45: return ENOTSUP;
        case 103: return EOPNOTSUPP;
        case 46: return EPFNOSUPPORT;
        case 47: return EAFNOSUPPORT;
        case 48: return EADDRINUSE;
        case 49: return EADDRNOTAVAIL;
        case 50: return ENETDOWN;
        case 51: return ENETUNREACH;
        case 52: return ENETRESET;
        case 53: return ECONNABORTED;
        case 54: return ECONNRESET;
        case 55: return ENOBUFS;
        case 56: return EISCONN;
        case 57: return ENOTCONN;
        case 58: return ESHUTDOWN;
        case 59: return ETOOMANYREFS;
        case 60: return ETIMEDOUT;
        case 61: return ECONNREFUSED;
        case 62: return ELOOP;
        case 63: return ENAMETOOLONG;
        case 64: return EHOSTDOWN;
        case 65: return EHOSTUNREACH;
        case 66: return ENOTEMPTY;
        case 67: return EPROCLIM;
        case 68: return EUSERS;
        case 69: return EDQUOT;
        case 70: return ESTALE;
        case 71: return EREMOTE;
        case 72: return EBADRPC;
        case 73: return ERPCMISMATCH;
        case 74: return EPROGUNAVAIL;
        case 75: return EPROGMISMATCH;
        case 76: return EPROCUNAVAIL;
        case 77: return ENOLCK;
        case 78: return ENOSYS;
        case 79: return EFTYPE;
        case 80: return EAUTH;
        case 81: return ENEEDAUTH;
        case 82: return EPWROFF;
        case 83: return EDEVERR;
        case 84: return EOVERFLOW;
        case 85: return EBADEXEC;
        case 86: return EBADARCH;
        case 87: return ESHLIBVERS;
        case 88: return EBADMACHO;
        case 89: return ECANCELED;
        case 90: return EIDRM;
        case 91: return ENOMSG;
        case 92: return EILSEQ;
        case 93: return ENOATTR;
        case 94: return EBADMSG;
        case 95: return EMULTIHOP;
        case 96: return ENODATA;
        case 97: return ENOLINK;
        case 98: return ENOSR;
        case 99: return ENOSTR;
        case 100: return EPROTO;
        case 101: return ETIME;

        default: return EOPNOTSUPP; // ??
    }
}

static bool setBooleanField(JNIEnv *env, jclass fieldClass, jobject fieldObject,
        char *fieldName, jboolean value) {
    jfieldID fieldID = env->GetFieldID(fieldClass, fieldName, "Z");
    if(fieldID == NULL)
        return false;

    env->SetBooleanField(fieldObject, fieldID, value);

    return true;
}

static bool setIntField(JNIEnv *env, jclass fieldClass, jobject fieldObject,
        char *fieldName, jint value) {
    jfieldID fieldID = env->GetFieldID(fieldClass, fieldName, "I");
    if(fieldID == NULL)
        return false;

    env->SetIntField(fieldObject, fieldID, value);

    return true;
}

static bool setLongField(JNIEnv *env, jclass fieldClass, jobject fieldObject,
        char *fieldName, jlong value) {
    jfieldID fieldID = env->GetFieldID(fieldClass, fieldName, "J");
    if(fieldID == NULL)
        return false;

    env->SetLongField(fieldObject, fieldID, value);

    return true;
}

static bool getBooleanField(JNIEnv *env, jclass fieldClass, jobject fieldObject,
        char *fieldName, jboolean *target) {
    jfieldID fieldID = env->GetFieldID(fieldClass, fieldName, "Z");
    if(fieldID == NULL)
        return false;

    *target = env->GetBooleanField(fieldObject, fieldId);
    return true;
}

static bool getIntField(JNIEnv *env, jclass fieldClass, jobject fieldObject,
        char *fieldName, jint *target) {
    jfieldID fieldID = env->GetFieldID(fieldClass, fieldName, "I");
    if(fieldID == NULL)
        return false;

    *target = env->GetIntField(fieldObject, fieldId);
    return true;
}

static bool getLongField(JNIEnv *env, jclass fieldClass, jobject fieldObject,
        char *fieldName, jlong *target) {
    jfieldID fieldID = env->GetFieldID(fieldClass, fieldName, "J");
    if(fieldID == NULL)
        return false;

    *target = env->GetLongField(fieldObject, fieldId);
    return true;
}

/**
 * Merges the contents of statObject into the struct stat target.
 */
int mergeStat(JNIEnv *env, jobject statObject, struct stat *target) {
  //LOG_DEBUG("    - Getting class Stat");
  //jclass statClass = env->FindClass(env, "org/catacombae/jfuse/Stat");
  jclass statClass = env->GetObjectClass(statObject);
  //LOG_DEBUG("      - statClass: %X", (int)statClass);
  //LOG_DEBUG("    - Getting field id for st_mode");
  
  jlong jl_dev;
  jlong jl_ino;
  jlong jl_mode;
  jlong jl_nlink;
  jlong jl_uid;
  jlong jl_gid;
  jlong jl_rdev;
  jlong jl_atimespec_sec;
  jlong jl_atimespec_nsec;
  jlong jl_mtimespec_sec;
  jlong jl_mtimespec_nsec;
  jlong jl_ctimespec_sec;
  jlong jl_ctimespec_nsec;
  jlong jl_size;
  jlong jl_blocks;
  jlong jl_blocksize;
  jlong jl_flags;
  jlong jl_gen;

  if(!getLongField(env, statClass, statObject, "st_dev", &jl_dev))
      handleError();
  if(!getLongField(env, statClass, statObject, "st_ino", &jl_ino))
      handleError();
  if(!getLongField(env, statClass, statObject, "st_mode", &jl_mode))
      handleError();
  if(!getLongField(env, statClass, statObject, "st_nlink", &jl_nlink))
      handleError();
  if(!getLongField(env, statClass, statObject, "st_uid", &jl_uid))
      handleError();
  if(!getLongField(env, statClass, statObject, "st_gid", &jl_gid))
      handleError();
  if(!getLongField(env, statClass, statObject, "st_rdev", &jl_rdev))
      handleError();
  if(!getLongField(env, statClass, statObject, "st_atimespec_sec", &jl_atimespec_sec))
      handleError();
  if(!getLongField(env, statClass, statObject, "st_atimespec_nsec", &jl_atimespec_nsec))
      handleError();
  if(!getLongField(env, statClass, statObject, "st_mtimespec_sec", &jl_mtimespec_sec))
      handleError();
  if(!getLongField(env, statClass, statObject, "st_mtimespec_nsec", &jl_mtimespec_nsec))
      handleError();
  if(!getLongField(env, statClass, statObject, "st_ctimespec_sec", &jl_ctimespec_sec))
      handleError();
  if(!getLongField(env, statClass, statObject, "st_ctimespec_nsec", &jl_ctimespec_nsec))
      handleError();
  if(!getLongField(env, statClass, statObject, "st_size", &jl_size))
      handleError();
  if(!getLongField(env, statClass, statObject, "st_blocks", &jl_blocks))
      handleError();
  if(!getLongField(env, statClass, statObject, "st_blocksize", &jl_blocksize))
      handleError();
  if(!getLongField(env, statClass, statObject, "st_flags", &jl_flags))
      handleError();
  if(!getLongField(env, statClass, statObject, "st_gen", &jl_gen))
      handleError();

  target->st_dev = jl_dev;
  target->st_ino = jl_ino;
  target->st_mode = jl_mode;
  target->st_nlink = jl_nlink;
  target->st_uid = jl_uid;
  target->st_gid = jl_;
  target->st_rdev = jl_;
  target->st_atimespec->tv_sec = jl_atimespec_sec;
  target->st_atimespec->tv_nsec = jl_atimespec_nsec;
  target->st_mtimespec->tv_sec = jl_mtimespec_sec;
  target->st_mtimespec->tv_nsec = jl_mtimespec_nsec;
  target->st_ctimespec->tv_sec = jl_ctimespec_sec;
  target->st_ctimespec->tv_nsec = jl_ctimespec_nsec;
  target->st_size = jl_size;
  target->st_blocks = jl_blocks;
  target->st_blksize = jl_blocksize;
  target->st_flags = jl_flags;
  target->st_gen = jl_gen;
}


static bool mergeFUSEFileInfo(JNIEnv *env, jobject ffiObject, struct fuse_file_info *target) {
  //LOG_DEBUG("    - Getting class Stat");
  //jclass statClass = env->FindClass(env, "org/catacombae/jfuse/Stat");
  jclass ffiClass = env->GetObjectClass(ffiObject);
  //LOG_DEBUG("      - statClass: %X", (int)statClass);
  //LOG_DEBUG("    - Getting field id for st_mode");

  jint flags;
  jlong fh_old;
  jint writepage;
  jboolean direct_io;
  jboolean keep_cache;
  jboolean flush;
  jlong fh;
  jlong lock_owner;

  if(!getIntField(env, ffiClass, ffiObject, "flags", &flags))
      return false;
  if(!getLongField(env, ffiClass, ffiObject, "fh_old", &fh_old))
      return false;
  if(!getIntField(env, ffiClass, ffiObject, "writepage", &writepage))
      return false;
  if(!getBooleanField(env, ffiClass, ffiObject, "direct_io", &direct_io))
      return false;
  if(!getBooleanField(env, ffiClass, ffiObject, "keep_cache", &keep_cache))
      return false;
  if(!getBooleanField(env, ffiClass, ffiObject, "flush", &flush))
      return false;
  if(!getLongField(env, ffiClass, ffiObject, "fh", &fh))
      return false;
  if(!getLongField(env, ffiClass, ffiObject, "lock_owner", &lock_owner))
      return false;

  target->flags = flags;
  target->fh_old = fh_old;
  target->writepage = writepage;
  target->direct_io = direct_io;
  target->keep_cache = keep_cache;
  target->flush = flush;
  target->fh = fh;
  target->lock_owner = lock_owner;

  return true;
}

static bool fillFUSEFileInfo(JNIEnv *env, struct fuse_file_info *fi, jobject ffiObject) {
  jclass ffiClass = env->GetObjectClass(statObject);

  if(!setIntField(env, ffiClass, ffiObject, "flags", fi->flags))
      return false;
  if(!setLongField(env, ffiClass, ffiObject, "fh_old", fi->fh_old))
      return false;
  if(!setIntField(env, ffiClass, ffiObject, "writepage", fi->writepage))
      return false;
  if(!setBooleanField(env, ffiClass, ffiObject, "direct_io", (fi->direct_io == 0?JNI_FALSE:JNI_TRUE)))
      return false;
  if(!setBooleanField(env, ffiClass, ffiObject, "keep_cache", (fi->keep_cache == 0?JNI_FALSE:JNI_TRUE)))
      return false;
  if(!setBooleanField(env, ffiClass, ffiObject, "flush", (fi->flush == 0?JNI_FALSE:JNI_TRUE)))
      return false;
  if(!setLongField(env, ffiClass, ffiObject, "fh", fi->fh))
      return false;
  if(!setLongField(env, ffiClass, ffiObject, "lock_owner", fi->lock_owner))
      return false;
  
  return true;
}

/**
 * Creates a new FUSEFileInfo object and fills it using the fields in
 * <code>fi</code>.
 */
static jobject newFUSEFileInfo(JNIEnv *env, struct fuse_file_info *fi) {
    jclass ffiClass = env->FindClass("org/catacombae/jfuse/FUSEFileInfo");
    jmethodID ffiConstructor = env->GetMethodID(statClass, "<init>", "void(V)");
    jobject obj = env->NewObject(ffiClass, ffiConstructor);
    fillFUSEFileInfo(env, fi, obj);
    return obj;
}


void jfuse_set_context(struct jfuse_context *ctx) {
    context = ctx;
}

int jfuse_getattr(const char *path, struct stat *stbuf) {
    JNIEnv *env = context->env;
    jobject obj = context->fsProvider;

    // Argument 1: path
    int pathlen = strlen(path);
    jbyteArray pathJava = env->NewByteArray(pathlen); // <alloc>
    env->SetByteArrayRegion(pathJava, 0, pathLen, path);

    // Argument 2: stbuf
    jclass statClass = env->FindClass("org/catacombae/jfuse/Stat");
    jmethodID statConstructor = env->GetMethodID(statClass, "<init>", "void(V)");
    jobject statInstance = env->NewObject(statClass, statConstructor);

    jint retval = env->CallIntMethod(obj, context->getattrMID, pathJava, statInstance);

    // Merge stat fields into stbuf
    mergeStat(env, statInstance, stbuf);

    env->DeleteLocalRef(statInstance);
    env->DeleteLocalRef(pathJava);

    return -javaErrnoToErrno(retval);
}


int jfuse_readlink(const char *path, char *target, size_t target_len) {
    return -ENOTSUP;
}

int jfuse_getdir(const char *path, fuse_dirh_t a, fuse_dirfil_t b) {
    return -ENOTSUP;
}

int jfuse_mknod(const char *path, mode_t a, dev_t b) {
    return -ENOTSUP;
}

int jfuse_mkdir(const char *path, mode_t dirmode) {
    return -ENOTSUP;
}

int jfuse_unlink(const char *path) {
    return -ENOTSUP;
}

int jfuse_rmdir(const char *path) {
    return -ENOTSUP;
}

int jfuse_symlink(const char *from_path, const char *to_path) {
    return -ENOTSUP;
}

int jfuse_rename(const char *from_path, const char *to_path) {
    return -ENOTSUP;
}

int jfuse_link(const char *path, const char *to_path) {
    return -ENOTSUP;
}

int jfuse_chmod(const char *path, mode_t filemode) {
    return -ENOTSUP;
}

int jfuse_chown(const char *path, uid_t uid, gid_t gid) {
    return -ENOTSUP;
}

int jfuse_truncate(const char *path, off_t newsize) {
    return -ENOTSUP;
}

int jfuse_utime(const char *path, struct utimbuf *newtime) {
    return -ENOTSUP;
}

int jfuse_open(const char *path, struct fuse_file_info *fi) {
    JNIEnv *env = context->env;
    jobject obj = context->fsProvider;
    
    // Argument 1: path
    int pathlen = strlen(path);
    jbyteArray pathJava = env->NewByteArray(pathlen); // <alloc>
    env->SetByteArrayRegion(pathJava, 0, pathLen, path);

    // Argument 2: fi
    jobject ffiInstance = newFUSEFileInfo(env, fi);

    fillFUSEFileInfo(ffiInstance, fi);

    jint retval = env->CallIntMethod(obj, context->openMID, pathJava, ffiInstance);

    // Merge FUSEFileInfo fields into fi
    mergeFUSEFileInfo(env, ffiInstance, fi);

    env->DeleteLocalRef(ffiInstance);
    env->DeleteLocalRef(pathJava);

    return -javaErrnoToErrno(retval);
}

int jfuse_read(const char *path, char *targetbuf, size_t targetbuf_len, off_t targetbuf_off,
        struct fuse_file_info *fi) {
    JNIEnv *env = context->env;
    jobject obj = context->fsProvider;

    // Argument 1: path
    int pathlen = strlen(path);
    jbyteArray pathJava = env->NewByteArray(pathlen); // <alloc>
    env->SetByteArrayRegion(pathJava, 0, pathLen, path);

    // Argument 2-4: targetbuf
    jbyteArray targetArray = env->NewByteArray(targetbuf_len); // <alloc>

    // Argument 5: fi
    jobject ffiInstance = newFUSEFileInfo(env, fi); // <alloc>

    jint retval = env->CallIntMethod(obj, context->readMID, pathJava, targetArray,
            0, targetbuf_len, ffiInstance);

    // Merge FUSEFileInfo fields into fi
    mergeFUSEFileInfo(env, ffiInstance, fi);

    // Copy data to native buffer
    env->GetByteArrayRegion(targetArray, 0, targetbuf_len, targetbuf+targetbuf_off);

    env->DeleteLocalRef(ffiInstance); // </alloc>
    env->DeleteLocalRef(targetArray); // </alloc>
    env->DeleteLocalRef(pathJava); // </alloc>

    return -javaErrnoToErrno(retval);
}

int jfuse_write(const char *path, const char *sourcebuf,
        size_t sourcebuf_len, off_t sourcebuf_off,
        struct fuse_file_info *fi) {
    return -ENOTSUP;
}

int jfuse_statfs(const char *path, struct statvfs *stvfsbuf) {
    return -ENOTSUP;
}

int jfuse_flush(const char *path, struct fuse_file_info *fi) {
    return -ENOTSUP;
}

int jfuse_release(const char *path, struct fuse_file_info *fi) {
    return -ENOTSUP;
}

int jfuse_fsync(const char *path, int, struct fuse_file_info *fi) {
    return -ENOTSUP;
}

#if (__FreeBSD__ >= 10)

int jfuse_setxattr(const char *path, const char *name, const char *value,
        size_t value_size, int flags, uint32_t position) {
    return -ENOTSUP;
}
#else

int jfuse_setxattr(const char *path, const char *name, const char *value,
        size_t value_size, int flags) {
    return -ENOTSUP;
}
#endif /* __FreeBSD__ >= 10 */

#if (__FreeBSD__ >= 10)

int jfuse_getxattr(const char *path, const char *name, char *value,
        size_t value_size, uint32_t position) {
    return -ENOTSUP;
}
#else

int jfuse_getxattr(const char *path, const char *name, char *value,
        size_t value_size) {
    return -ENOTSUP;
}
#endif /* __FreeBSD__ >= 10 */

int jfuse_listxattr(const char *path, char *namebuf, size_t namebuf_len) {
    return -ENOTSUP;
}

int jfuse_removexattr(const char *path, const char *name) {
    return -ENOTSUP;
}

int jfuse_opendir(const char *path, struct fuse_file_info *fi) {
    return -ENOTSUP;
}

int jfuse_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
        off_t offset, struct fuse_file_info *fi) {
    JNIEnv *env = context->env;
    jobject obj = context->fsProvider;

    // Argument 1: path
    int pathlen = strlen(path);
    jbyteArray pathJava = env->NewByteArray(pathlen); // <alloc>
    env->SetByteArrayRegion(pathJava, 0, pathLen, path);

    // Argument 5: fi
    jobject ffiInstance = newFUSEFileInfo(env, fi); // <alloc>

    fillFUSEFileInfo(ffiInstance, fi);

    jint retval = env->CallIntMethod(obj, context->openMID, pathJava, ffiInstance);

    // Merge FUSEFileInfo fields into fi
    mergeFUSEFileInfo(env, ffiInstance, fi);

    env->DeleteLocalRef(ffiInstance); // </alloc>
    env->DeleteLocalRef(pathJava); // </alloc>

    return -javaErrnoToErrno(retval);}

int jfuse_releasedir(const char *path, struct fuse_file_info *fi) {
    return -ENOTSUP;
}

int jfuse_fsyncdir(const char *path, int, struct fuse_file_info *fi) {
    return -ENOTSUP;
}

void *jfuse_init(struct fuse_conn_info *conn) {
    return -ENOTSUP;
}

void jfuse_destroy(void *) {
    return -ENOTSUP;
}

int jfuse_access(const char *path, int) {
    return -ENOTSUP;
}

int jfuse_create(const char *path, mode_t, struct fuse_file_info *fi) {
    return -ENOTSUP;
}

int jfuse_ftruncate(const char *path, off_t, struct fuse_file_info *fi) {
    return -ENOTSUP;
}

int jfuse_fgetattr(const char *path, struct stat *, struct fuse_file_info *fi) {
    return -ENOTSUP;
}

int jfuse_lock(const char *path, struct fuse_file_info *fi, int cmd,
        struct flock *) {
    return -ENOTSUP;
}

int jfuse_utimens(const char *path, const struct timespec tv[2]) {
    return -ENOTSUP;
}

int jfuse_bmap(const char *path, size_t blocksize, uint64_t *idx) {
    return -ENOTSUP;
}

#if (__FreeBSD__ >= 10)

// Implement these MacFUSE callbacks some time in the future.
/*
int jfuse_setvolname(const char *name) {
}

int jfuse_exchange(const char *, const char *, unsigned long) {
}

int jfuse_getxtimes(const char *, struct timespec *bkuptime,
        struct timespec *crtime) {
}

int jfuse_setbkuptime(const char *, const struct timespec *tv) {
}

int jfuse_setchgtime(const char *, const struct timespec *tv) {
}

int jfuse_setcrtime(const char *, const struct timespec *tv) {
}

int jfuse_chflags(const char *, uint32_t) {
}

int jfuse_setattr_x(const char *, struct setattr_x *) {
}

int jfuse_fsetattr_x(const char *, struct setattr_x *,
        struct fuse_file_info *fi) {
}
*/

#endif /* __FreeBSD__ >= 10 */
