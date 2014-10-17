/*
 * SNOOPY LOGGER
 *
 * File: snoopy/input/group.c
 *
 * Copyright (c) 2014 bostjan@a2o.si
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */



/*
 * SNOOPY INPUT PROVIDER: group
 *
 * Description:
 *     Returns literal group name (Group ID) of current process
 *
 * Params:
 *     input: pointer to string, to write result into
 *
 * Return:
 *     number of characters in the returned string
 */
#include "snoopy.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <grp.h>



int snoopy_input_group (char *input)
{
    struct group   gr;
    struct group  *gr_gid         = NULL;
    char          *buffgr_gid     = NULL;
    size_t         buffgrsize_gid = 0;
    int            messageLength  = 0;

    /* Allocate memory */
    buffgrsize_gid = sysconf(_SC_GETGR_R_SIZE_MAX);
    if (buffgrsize_gid == -1) {
        buffgrsize_gid = 16384;
    }
    buffgr_gid = malloc(buffgrsize_gid);
    if(buffgr_gid == NULL) {
        return snprintf(input, SNOOPY_INPUT_MESSAGE_MAX_SIZE, "ERROR(malloc)");
    }

    /* Format return string */
    getgrgid_r(getgid(), &gr, buffgr_gid, buffgrsize_gid, &gr_gid);
    messageLength = snprintf(input, SNOOPY_INPUT_MESSAGE_MAX_SIZE, "%s", gr_gid->gr_name);

    /* Cleanup and return */
    free(buffgr_gid);
    return messageLength;
}