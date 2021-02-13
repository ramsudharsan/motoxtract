/*
 * motoxtract.c
 *
 * Copyright (c) Ramsudharsan <ramsudharsanm@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define SECTOR_SIZE 512
#define HEADER_SIZE 1024
int usage(char *name) {
    printf("usage:\t%s <path_to_motoboot.img_file>\n", name);
    return 0;
}

struct entry {
    char partitionName[24];
    uint32_t firstSector;
    uint32_t lastSector;
};

struct moto_header {
    uint32_t partitionNumber;
    struct entry partitions[30];
    char padding[28];
}header;

int main (int argc, char **argv) {
    FILE *motoboot, *partitionDump;
    unsigned char buff[HEADER_SIZE];
    int partitionCount, i, j, k;
    char partitionName[32];

    if (argc != 2)
        return usage(argv[0]);

    motoboot = fopen(argv[1], "r");

    if (motoboot == NULL) {
        printf("unable to open %s file, abort\n", argv[1]);
        return -1;
    }
    printf("reading file %s\n", argv[1]);

    fread((void*)buff, sizeof(buff), 1, motoboot);

    memcpy(&header, buff, sizeof(header));
    partitionCount = header.partitionNumber;

    if (partitionCount > 30) {
        printf("error reading the file, too many partitions\n");
        return -1;
    }
    printf("found %d partitions\n", partitionCount);

    for (i = 0; i < partitionCount; i++) {
    	curHdr = &header.partitions[i];
        snprintf(partitionName, sizeof(partitionName), "%s_%#x_%#x.mbn", curHdr->partitionName, curHdr->firstSector, curHdr->lastSector);
        partitionDump = fopen(partitionName, "w+");
        if (partitionDump == NULL) {
            printf("unable to write to file %s", partitionName);
            return -1;
        }
        uint32_t sectors = curHdr->lastSector - curHdr->firstSector + 1;
        printf("dumping partition %d (%s), starting offset in file 0x%08X\n", i, curHdr->partitionName, HEADER_SIZE + curHdr->firstSector * SECTOR_SIZE);
        for (j = 0; j < sectors; j++) {
            fread((void*)buff, SECTOR_SIZE, 1, motoboot);
            fwrite((void*)buff, SECTOR_SIZE, 1, partitionDump);
        }
        fclose(partitionDump);
    }

    fclose(motoboot);
    return 0;
}
