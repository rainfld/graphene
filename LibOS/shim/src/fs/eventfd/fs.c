/*
 * fs.c
 *
 * This file contains codes for implementation of 'eventfd' filesystem.
 */

#include <shim_internal.h>
#include <shim_thread.h>
#include <shim_handle.h>
#include <shim_fs.h>
#include <shim_profile.h>

#include <pal.h>
#include <pal_error.h>
#include <pal_debug.h>

#include <errno.h>

#include <linux/stat.h>
#include <linux/fcntl.h>

#include <asm/fcntl.h>
#include <asm/mman.h>
#include <asm/unistd.h>
#include <asm/prctl.h>
#include <asm/fcntl.h>
#include <shim_profile.h>

#define EVENTFD_COUNTER_SIZE        8
#define EVENTFD_MAX_VAL             0xffffffffffffffffULL

static ssize_t eventfd_read (struct shim_handle * hdl, void * buf,
                          size_t count)
{
    ssize_t ret = EVENTFD_COUNTER_SIZE;

    if (!buf || count != EVENTFD_COUNTER_SIZE)
    {
        ret = -EINVAL;
        goto out;
    }

    if (hdl->info.eventfd.counter == 0)
    {
        if (hdl->flags & O_NONBLOCK)
        {
            ret = -EAGAIN;
            goto out;
        } else {
            struct shim_handle * read_hdl = hdl->info.eventfd.pipe_hdl[0];
            PAL_NUM bytes = DkStreamRead(read_hdl->pal_handle, 0, count, buf, NULL, 0);

            if (!bytes)
                return -PAL_ERRNO;
        }
    }

    *(long long *) buf = hdl->info.eventfd.counter;
out:
    return ret;
}

static ssize_t eventfd_write (struct shim_handle * hdl, const void * buf,
                           size_t count)
{
    ssize_t ret = EVENTFD_COUNTER_SIZE;

    debug("eventfd_write  counter init value: %lld\n", hdl->info.eventfd.counter);
    if (!buf || count != EVENTFD_COUNTER_SIZE || (*(unsigned long long *) buf) >= EVENTFD_MAX_VAL)
    {
        ret = -EINVAL;
        goto out;
    }

    hdl->info.eventfd.counter += *(long long *) buf;

    struct shim_handle * write_hdl = hdl->info.eventfd.pipe_hdl[1];

    PAL_NUM bytes = DkStreamWrite(write_hdl->pal_handle, 0, count, (void *) buf, NULL);

    if (!bytes)
        return -PAL_ERRNO;

out:
    return ret;
}

struct shim_fs_ops eventfd_fs_ops = {
        .read       = &eventfd_read,
        .write      = &eventfd_write,
    };

struct shim_mount eventfd_builtin_fs = { .type = "eventfd",
                                      .fs_ops = &eventfd_fs_ops, };
