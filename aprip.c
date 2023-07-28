/*
BSD 3-Clause License
Copyright (c) 2022-2023, Alex Free
All rights reserved.
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.
* Neither the name of the copyright holder nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define VER "1.0.5"
FILE *bin;
FILE *mem_dump_1;
FILE *mem_dump_2;

unsigned int bin_size;
unsigned int max_size;
unsigned mem_dump_1_size; 
unsigned int mem_dump_2_size;
unsigned int current_fpos;
unsigned int number_of_sectors;
unsigned int search_size;
unsigned int valid_mem_dump_size = 0x200000; // The exact file size generated when dumping RAM in the DuckStation emulator.
unsigned int gameshark_write_byte_address;
unsigned int get_start_of_pattern_pos;

unsigned char *buf;
unsigned char *bytes;
unsigned char *mem_dump_1_buf;
unsigned char *mem_dump_2_buf;

unsigned char last_byte;
unsigned char gameshark_prefix;
unsigned char sectors[0x1000];
unsigned char match_pattern[16];
unsigned char pattern[16];

const unsigned char sync = 0x00;

const unsigned char medievil_europe_ps_exe [] =  { 0x53, 0x43, 0x45, 0x53, 0x5F, 0x30, 0x30, 0x33, 0x2E, 0x31, 0x31, 0x3B, 0x31}; // SCES_003.11;1
const unsigned char medievil_france_ps_exe [] =  { 0x53, 0x43, 0x45, 0x53, 0x5F, 0x30, 0x31, 0x34, 0x2E, 0x39, 0x32, 0x3B, 0x31}; // SCES_014.92;1
const unsigned char medievil_germany_ps_exe [] = { 0x53, 0x43, 0x45, 0x53, 0x5F, 0x30, 0x31, 0x34, 0x2E, 0x39, 0x33, 0x3B, 0x31}; // SCES_014.93;1
const unsigned char medievil_italian_ps_exe [] = { 0x53, 0x43, 0x45, 0x53, 0x5F, 0x30, 0x31, 0x34, 0x2E, 0x39, 0x34, 0x3B, 0x31}; // SCES_014.94;1
const unsigned char medievil_spain_ps_exe [] =   { 0x53, 0x43, 0x45, 0x53, 0x5F, 0x30, 0x31, 0x34, 0x2E, 0x39, 0x35, 0x3B, 0x31}; // SCES_014.95;1

const unsigned char libcrypt_2_anti_pro_action_replay[] = {
    0x80, 0xE1, 0x02, 0x3C, 0x00, 0x38, 0x82, 0x40
};

const unsigned char libcrypt_2_anti_mod_chip[] = {
    0x08, 0x00, 0x20, 0x14, 0x02, 0x00, 0xE7, 0x30, 0x06, 0x00, 0xE0, 0x10,  0xAD, 0xFF, 0x84, 0x20, 0x04, 0x00, 0x80, 0x14, 0x00, 0x00, 0x00, 0x00
};

const unsigned char libcrypt_2_magic_word[] = {
    0x25, 0x30, 0x86, 0x00    
};

// ICEPICK patch from TRSIMEDI, modified for aprip 
const unsigned char libcrypt_1_medievil_icepick_based_patch[] = {
0x0A, 
0x00, // not a value checked
0x80,
0x14,
0x00, // not a value checked
0x00, // not a value checked
0x00, // not a value checked
0x00, // not a value checked
0x00, // not a value checked
0x00, // not a value checked
0xA3, 
0x90, 
0x02,
0x00, // not a value checked
0x02, 
0x24, 
0x06, 
0x00, // not a value checked
0x62, 
0x14, 
0x0E, 
0x80, 
0x03, 
0x3C, 
0x04, 
0x00, // not a value checked
0xA3, 
0x90, 
0x53, 
0x00, // not a value checked
0x02, 
0x24, 
0x02, 
0x00, // not a value checked
0x62, 
0x14, 
0x0E, 
0x80, 
0x03, 
0x3C, 
0x07,
0x00, // not a value checked
0xA4, 
0x90, 
0x00, 
0x00, // byte 2 of MW
0x00, // byte 1 of MW
0x00, 
0x00
}; // 0x2F, 47 bytes

const unsigned char anti_piracy_v2[] = { // This was first seen in Dino Crisis? Does SCEX/GetTN/GetTD/ReadTOC but is standardized and very easy to bypass. Seems like all games after a certain point began copying in this code to add anti-piracy measures to their product.
    0x01, 0x00, 0x01, 0x03, // GetStat
    0x13, 0x00, 0x03, 0x03, // GetTN
    0x14, 0x01, 0x03, 0x03, // GetTD
    0x02, 0x03, 0x01, 0x03, // SetLoc
    0x16, 0x00, 0x01, 0x05, // SeekAudio
    0x0E, 0x01, 0x01, 0x03, // SetMode
    0x0A, 0x00, 0x01, 0x05, // Init
    0x0B, 0x00, 0x01, 0x03, // Mute
    0x03, 0x00, 0x01, 0x03, // Play
    0x19, 0x01, 0x01, 0x03, // Subfunq X (19'04) //37th
    0x19, 0x01, 0x02, 0x03, // Subfunq Y (19'05) //41st
    0x09, 0x00, 0x01, 0x05, // Pause
    0x1E, 0x00, 0x01, 0x05, // ReadTOC //49th
    0x1A, 0x00, 0x01, 0x05 // GetID
}; //52 byte pattern

bool matched_anti_piracy_v2;
bool check_for_apv2 = true;

bool last_sector;

bool matched_libcrypt_2_anti_pro_action_replay;
bool matched_libcrypt_2_anti_mod_chip;
bool matched_libcrypt_2_magic_word;
bool matched_libcrypt_2;

bool directory_record_sectors_maybe = true;
bool libcrypt_1;
bool matched_libcrypt_1_icepick_based_patch;
bool matched_libcrypt_1_magic_word;
bool matched_libcrypt_1_part_2;
bool matched_libcrypt_1_part_3;

void bin_patch_libcrypt(const char **argv)
{
    /*
        The AP table could possibly start on the end of a sector and end at the beginning of the next sector. Each RAW sector is 0x930 bytes. The first 0x18 bytes are to be ignored as they are just header data. The next 0x800 bytes contains actual data we want to scan through.
        Start at 0. Skip to 0x18. Read the next 0x800 bytes. Skip to a total of 0x930 bytes (one whole raw sector). Skip 0x18 bytes again and then read the next 0x800 bytes. We now have 2 sectors worth of straight up data in a buffer of 0x1000 bytes
        Run search functions on the 0x1000 byte sized buffer.
    */
    fseek(bin, 0, SEEK_END);
    bin_size = ftell(bin);

    if(bin_size > 0x2EE00000) // 750MB max, no PSX software comes even close to such a size
    {
        printf("Error: The BIN file: %s exceeds the maximum filesize of 750MB in bin patch mode\n", argv[3]);
        fclose(bin);
        return;
    }

    unsigned int magic_word = strtoul(argv[2], NULL, 16);
    printf("Magic Word: %08X\n", magic_word);
    unsigned char *bytes;
    bytes=(unsigned char *)&magic_word;
    /*
    printf("Bytes 0: %02X\n", bytes[0]);
    printf("Bytes 1: %02X\n", bytes[1]);
    printf("Bytes 2: %02X\n", bytes[2]);
    printf("Bytes 3: %02X\n", bytes[3]);
    */

    fseek(bin, 0, SEEK_SET);
    buf = (unsigned char *)malloc(bin_size * sizeof(unsigned char)); // Read entire BIN to memory for performance gain, I mean it's 2022 who doesn't have a free ~700MBs of RAM?!

    if(fread(buf, 1, bin_size, bin) != bin_size)
    {
        printf("Error loading BIN: file: %s\n", argv[2]);
        return;
    }

    printf("Successfully loaded BIN file: %s (%d bytes in memory)\n", argv[3], bin_size);
    max_size = bin_size;
    number_of_sectors = (bin_size / 2352);
    printf("Scanning %d sectors, please wait...\n", number_of_sectors);

    while(1)
    {
        if(current_fpos > max_size)
            break; // even number of sectors, done reading the file.

        if((current_fpos + 0x930) == max_size) // odd number of sectors
            last_sector = 1; // This function is reading 2 sectors at a time, so if there is an odd number of sectors we have to change the behavior to only search the last sector. Explicitly break loop when this is set.

        if((current_fpos > (0x930 * 25))) // after 4 sectors (22, 23, 24, 25) stop looking for libcrypt 1 PS-EXE boot filename
            directory_record_sectors_maybe = false;

        for(int i=0; i < 0x800; i++)
        {
            sectors[i] = buf[current_fpos + i + 0x18]; // skip 0x18 header info per sector
        }

        if(!last_sector)
        {
            for(int i=0; i < 0x800; i++)
            {
                sectors[i + 0x800] = buf[current_fpos + i + 0x18 + 0x930]; // skip 0x18 header info then skip exactly 1 sector. Read the next 0x800 bytes. We now have an array's worth of data from 2 sectors which excludes EDC/Header data at the beggining and end of each.
            }
            search_size = 0x1000;
        } else {
            search_size = 0x800;
        }

        for(int s = 0; s < search_size; s++)
        {
            if(check_for_apv2)
            {
                // APv2
                matched_anti_piracy_v2 = true;
                for(int i=0; i < 52; i++)
                {                
    
                    if(anti_piracy_v2[i] != sectors[s + i])
                    {
                        if(i != 3 && i != 7 && i != 11 && i != 15 && i != 19 && i != 23 && i != 27 && i != 31 && i != 35 && i != 39 && i != 43 && i != 47 && i != 51) // These bytes could change, they can be 03 or 05 depending on the AP code in the game but the table itself remains consistent besides the value of every 4th byte and the commands are still obvious via this pattern
                        {
                            matched_anti_piracy_v2 = false;
                        }
                    }      
                }

                if(matched_anti_piracy_v2) 
                {
                   printf("Got anti-piracy v2 table match\n");
                    sectors[s + 48] = sync; // Replace ReadTOC's first byte with the first byte of the sync command. This seems to trigger the VC0 CDROM Controller BIOS Firmware behavior on all consoles. The VC0 CDROM Controller BIOS firmware does not have the ReadTOC command, it is found in the wild in early SCPH-3000 Japanese consoles and in all SCPH-1000 consoles.
			    }
            }

            if((directory_record_sectors_maybe) && (!libcrypt_1))
            {
                libcrypt_1 = true;
                
                for(int i=0; i < 13; i++)
                {                
                    if(
                    (medievil_europe_ps_exe[i] != sectors[s + i]) &&
                    (medievil_france_ps_exe[i] != sectors[s + i]) &&
                    (medievil_germany_ps_exe[i] != sectors[s + i]) &&
                    (medievil_italian_ps_exe[i] != sectors[s + i]) && 
                    (medievil_spain_ps_exe[i] != sectors[s + i])
                    )
                    {
                        libcrypt_1 = false;
                    }
                }
            }

            if(libcrypt_1)
            {
                check_for_apv2 = false;
                matched_libcrypt_1_icepick_based_patch = true;
                for(int i=0; i < 47; i++)
                {                
                    if(libcrypt_1_medievil_icepick_based_patch[i] != sectors[s + i])
                    {
                       if(i != 1 && i != 4 && i != 5 && i != 6  && i != 7 && i != 8 && i != 9 && i != 13 && i != 17 && i != 25 && i != 29 && i != 33 && i != 41) // These are not matchable so they are 0x00 in the array and not checked here
                        {
                            matched_libcrypt_1_icepick_based_patch = false;
                        }
                    }   
                }

                if(matched_libcrypt_1_icepick_based_patch)
                {
                    printf("Got LibCrypt v1 ICEPICK match\n");
                    sectors[s + 0] = 0x00;
                    // skip 1
                    sectors[s + 2] = 0x00;
                    sectors[s + 3] = 0x00;
                    // skip 4
                    // skip 5
                    // skip 6
                    // skip 7
                    // skip 8
                    // skip 9
                    sectors[s + 10] = 0x00;
                    sectors[s + 11] = 0x00;
                    sectors[s + 12] = 0x00;
                    // skip 13
                    sectors[s + 14] = 0x00;
                    sectors[s + 15] = 0x00;
                    sectors[s + 16] = 0x00;
                    // skip 17
                    sectors[s + 18] = 0x00;
                    sectors[s + 19] = 0x00;
                    sectors[s + 20] = 0x00;   
                    sectors[s + 21] = 0x00;
                    sectors[s + 22] = 0x00;
                    sectors[s + 23] = 0x00;  
                    sectors[s + 24] = 0x00;
                    // skip 25
                    sectors[s + 26] = 0x00;
                    sectors[s + 27] = 0x00;
                    sectors[s + 28] = 0x00;
                    // skip 29
                    sectors[s + 30] = 0x00;
                    sectors[s + 31] = 0x00;
                    sectors[s + 32] = 0x00;   
                    // skip 33
                    sectors[s + 34] = 0x00;
                    sectors[s + 35] = 0x00;
                    sectors[s + 36] = 0x00;   
                    sectors[s + 37] = 0x00;
                    sectors[s + 38] = 0x00;
                    sectors[s + 39] = 0x00;  
                    sectors[s + 40] = 0x00;   
                    // skip 41
                    sectors[s + 42] = 0x00;
                    sectors[s + 43] = 0x00;
                    sectors[s + 44] = bytes[0];   // Magic Word byte 2
                    sectors[s + 45] = bytes[1];   // Magic Word byte 1
                    sectors[s + 46] = 0x04;
                    sectors[s + 47] = 0x24;  
                }

            } else {
                // LibCrypt v2 (majority of LibCrypt games)
                matched_libcrypt_2_anti_pro_action_replay = true;
                for(int i=0; i < 8; i++)
                {                
                    if(libcrypt_2_anti_pro_action_replay[i] != sectors[s + i])
                        matched_libcrypt_2_anti_pro_action_replay = false;
                }

                if(matched_libcrypt_2_anti_pro_action_replay)
                {
                    printf("Got LibCrypt v2 Anti-Pro Action Replay match\n");
                    sectors[s + 0] = 0x00;
                    sectors[s + 1] = 0x00;
                    sectors[s + 2] = 0x00;
                    sectors[s + 3] = 0x00;
                    sectors[s + 4] = 0x00;
                    sectors[s + 5] = 0x00;
                    sectors[s + 6] = 0x00;
                    sectors[s + 7] = 0x00;
                }

                matched_libcrypt_2_anti_mod_chip = true;
                for(int i=0; i < 24; i++)
                {                
                    if(libcrypt_2_anti_mod_chip[i] != sectors[s + i])
                        matched_libcrypt_2_anti_mod_chip = false;
                }

                if(matched_libcrypt_2_anti_mod_chip)
                {
                    printf("Got LibCrypt v2 Anti-Mod-Chip match\n");
                    // Part 1
                    sectors[s + 0] = 0x00;
                    sectors[s + 1] = 0x00;
                    sectors[s + 2] = 0x00;
                    sectors[s + 3] = 0x00;
                    // Part 2
                    sectors[s + 4] = 0x02;
                    sectors[s + 5] = 0x00;
                    sectors[s + 6] = 0xE7;
                    sectors[s + 7] = 0x30;
                    // Part 3
                    sectors[s + 8] = 0x00;
                    sectors[s + 9] = 0x00;
                    sectors[s + 10] = 0x00;
                    sectors[s + 11] = 0x00;
                    // Part 4
                    sectors[s + 12] = 0xAD;
                    sectors[s + 13] = 0xFF;
                    sectors[s + 14] = 0x84;
                    sectors[s + 15] = 0x20;
                    // Part 5
                    sectors[s + 16] = 0x00;
                    sectors[s + 17] = 0x00;
                    sectors[s + 18] = 0x00;
                    sectors[s + 19] = 0x00;
                    // Part 6
                    sectors[s + 20] = 0x00;
                    sectors[s + 21] = 0x00;
                    sectors[s + 22] = 0x00;
                    sectors[s + 23] = 0x00;
                }

                matched_libcrypt_2_magic_word = true;
                for(int i=0; i < 4; i++)
                {                
                    if(libcrypt_2_magic_word[i] != sectors[s + i])
                        matched_libcrypt_2_magic_word = false;
                }

                if(matched_libcrypt_2_magic_word)
                {
                    printf("Got LibCrypt v2 Magic Word match\n");
                    sectors[s + 0] = bytes[1];
                    sectors[s + 1] = bytes[0];

                    sectors[s + 2] = 0xC6;
                    sectors[s + 3] = 0x34;
                    		// 6C 3A C6 34
                }

            }
        }
		
        for(int i=0; i < 0x800; i++)
        {
            buf[current_fpos + i + 0x18] = sectors[i]; // skip 0x18 header info per sector
        }

        if(!last_sector)
        {
            for(int i=0; i < 0x800; i++)
            {
                buf[current_fpos + i + 0x18 + 0x930] = sectors[0x800 + i]; // skip 0x18 header info then skip exactly 1 sector. Read the next 0x800 bytes. We now have an array's worth of data from 2 sectors which excludes EDC/Header data at the beginning and end of each.
            }
        } else {
            break; // That was the last sector
        }			
        current_fpos = (current_fpos + 0x930); // Advance one sector.
    }

    fseek(bin, 0, SEEK_SET);
	fwrite(buf, bin_size, 1, bin);
    fclose(bin);
    free(buf);
}

void bin_patch(const char **argv)
{
    /*
        The AP table could possibly start on the end of a sector and end at the beginning of the next sector. Each RAW sector is 0x930 bytes. The first 0x18 bytes are to be ignored as they are just header data. The next 0x800 bytes contains actual data we want to scan through.
        Start at 0. Skip to 0x18. Read the next 0x800 bytes. Skip to a total of 0x930 bytes (one whole raw sector). Skip 0x18 bytes again and then read the next 0x800 bytes. We now have 2 sectors worth of straight up data in a buffer of 0x1000 bytes
        Run search functions on the 0x1000 byte sized buffer.
    */
    fseek(bin, 0, SEEK_END);
    bin_size = ftell(bin);

    if(bin_size > 0x2EE00000) // 750MB max, no PSX software comes even close to such a size
    {
        printf("Error: The BIN file: %s exceeds the maximum filesize of 750MB in bin patch mode\n", argv[2]);
        fclose(bin);
        return;
    }
    
    fseek(bin, 0, SEEK_SET);
    buf = (unsigned char *)malloc(bin_size * sizeof(unsigned char)); // Read entire BIN to memory for performance gain, I mean it's 2022 who doesn't have a free ~700MBs of RAM?!
    
    if(fread(buf, 1, bin_size, bin) != bin_size)
    {
        printf("Error loading BIN: file: %s\n", argv[2]);
        return;
    }

    printf("Successfully loaded BIN file: %s (%d bytes in memory)\n", argv[2], bin_size);
    max_size = bin_size;
    number_of_sectors = (bin_size / 2352);
    printf("Scanning %d sectors, please wait...\n", number_of_sectors);

    while(1)
    {
        if(current_fpos > max_size)
            break; // even number of sectors, done reading the file.

        if((current_fpos + 0x930) == max_size) // odd number of sectors
            last_sector = 1; // This function is reading 2 sectors at a time, so if there is an odd number of sectors we have to change the behavior to only search the last sector. Explicitly break loop when this is set.

        for(int i=0; i < 0x800; i++)
        {
            sectors[i] = buf[current_fpos + i + 0x18]; // skip 0x18 header info per sector
        }

        if(!last_sector)
        {
            for(int i=0; i < 0x800; i++)
            {
                sectors[i + 0x800] = buf[current_fpos + i + 0x18 + 0x930]; // skip 0x18 header info then skip exactly 1 sector. Read the next 0x800 bytes. We now have an array's worth of data from 2 sectors which excludes EDC/Header data at the beggining and end of each.
            }
            search_size = 0x1000;
        } else {
            search_size = 0x800;
        }

        for(int s = 0; s < search_size; s++)
        {
            matched_anti_piracy_v2 = true;
            for(int i=0; i < 52; i++)
            {                
    
                if(anti_piracy_v2[i] != sectors[s + i])
                {
                    if(i != 3 && i != 7 && i != 11 && i != 15 && i != 19 && i != 23 && i != 27 && i != 31 && i != 35 && i != 39 && i != 43 && i != 47 && i != 51) // These bytes could change, they can be 03 or 05 depending on the AP code in the game but the table itself remains consistent besides the value of every 4th byte and the commands are still obvious via this pattern
                    {
                        matched_anti_piracy_v2 = false;
                    }
                }      
            }

            if(matched_anti_piracy_v2) 
            {
                printf("Got anti-piracy v2 table match\n");
                sectors[s + 48] = sync; // Replace ReadTOC's first byte with the first byte of the sync command. This seems to trigger the VC0 CDROM Controller BIOS Firmware behavior on all consoles. The VC0 CDROM Controller BIOS firmware does not have the ReadTOC command, it is found in the wild in early SCPH-3000 Japanese consoles and in all SCPH-1000 consoles.
			}
        }
		
        for(int i=0; i < 0x800; i++)
        {
            buf[current_fpos + i + 0x18] = sectors[i]; // skip 0x18 header info per sector
        }

        if(!last_sector)
        {
            for(int i=0; i < 0x800; i++)
            {
                buf[current_fpos + i + 0x18 + 0x930] = sectors[0x800 + i]; // skip 0x18 header info then skip exactly 1 sector. Read the next 0x800 bytes. We now have an array's worth of data from 2 sectors which excludes EDC/Header data at the beginning and end of each.
            }
        } else {
            break; // That was the last sector
        }			
        current_fpos = (current_fpos + 0x930); // Advance one sector.
    }

    fseek(bin, 0, SEEK_SET);
	fwrite(buf, bin_size, 1, bin);
    fclose(bin);
    free(buf);
}

void gameshark_gen(const char **argv)
{
    fseek(mem_dump_1, 0, SEEK_END);
    mem_dump_1_size = ftell(mem_dump_1);

    if(mem_dump_1_size != valid_mem_dump_size)
    {
        printf("Error: the original RAM dump file: %s is not the expected size\n", argv[2]);
        fclose(mem_dump_1);
        free(buf);
        if(mem_dump_1_size == 8388608)
            printf("Do you have the 'Enable 8MB RAM' option enabled? Uncheck that option if so and make a new RAM dump\n");
        return;
    }

    fseek(mem_dump_1, 0, SEEK_SET);
    buf = (unsigned char *)malloc(mem_dump_1_size * sizeof(unsigned char));

    if(fread(buf, 1, mem_dump_1_size, mem_dump_1) != mem_dump_1_size)
    {
        printf("Error loading RAM dump file: %s\n", argv[2]);
        return;
    }
    
    printf("Loaded RAM dump file: %s (%d bytes in memory)\n", argv[2], mem_dump_1_size);

    while(1)
    {
        if(current_fpos > valid_mem_dump_size)
            break;

        matched_anti_piracy_v2 = true;
        for(int i=0; i < 52; i++)
        {                
            if(anti_piracy_v2[i] != buf[current_fpos + i])
            {
                if(i != 3 && i != 7 && i != 11 && i != 15 && i != 19 && i != 23 && i != 27 && i != 31 && i != 35 && i != 39 && i != 43 && i != 47 && i != 51) // These bytes could change, they can be 03 or 05 depending on the AP code in the game but the table itself remains consistent besides the value of every 4th byte and the commands are still obvious via this pattern
                    matched_anti_piracy_v2 = false;
            }
        }
          
        if(matched_anti_piracy_v2) {
            printf("Got anti-piracy v2 table match starting at offset: 0x%08X\n", current_fpos);
            gameshark_write_byte_address = (current_fpos + 48);

            bytes=(unsigned char *)&gameshark_write_byte_address;
            bytes[3] = 0xD0;
            printf("%08X 001E\n", gameshark_write_byte_address); // Look for ReadTOC command
            bytes=(unsigned char *)&gameshark_write_byte_address;
            bytes[3] = 0x80;        
            gameshark_write_byte_address = bytes[0] + (bytes[1] << 8) + (bytes[2] << 16) + (bytes[3] << 24); // NOT BIG-ENDIAN SAFE    
            printf("%08X 0000\n", gameshark_write_byte_address); // Write the sync command where ReadTOC was. This seems to trigger the VC0 CDROM Controller BIOS Firmware behavior on all consoles. The VC0 CDROM Controller BIOS firmware does not have the ReadTOC command, it is found in the wild in early SCPH-3000 Japanese consoles and in all SCPH-1000 consoles.
            current_fpos = (current_fpos + 52); // Skip the next 52 bytes as we already know this is the table
        } else {
            current_fpos++; // Move to next byte to start APv2 check all over again until EOF
        }
    }

    free(mem_dump_1_buf);
    fclose(mem_dump_1);
}

void sharkconv(const char **argv)
{
    unsigned int gameshark_code_address = strtoul(argv[1], NULL, 16);
    printf("Got old game ver gameshark code address %08X\n", gameshark_code_address);
    bytes=(unsigned char *)&gameshark_code_address;
    printf("Got old game ver gameshark code type prefix: %02X\n", bytes[3]);
    gameshark_prefix = bytes[3];
    bytes[3] = 0x00; // the 80 or D0 is a prefix for the gameshark code type, the actual memory location is 00 in this part of the address
    gameshark_code_address = bytes[0] + (bytes[1] << 8) + (bytes[2] << 16) + (bytes[3] << 24); // NOT BIG-ENDIAN SAFE
    printf("Got old game RAM dump address %08X\n", gameshark_code_address);
    unsigned int base_gameshark_code_address = (gameshark_code_address/16); // rounds down, ignores any remainder
    base_gameshark_code_address = (base_gameshark_code_address * 16); // Boom we got the start of the even memory address that the write value is written into
    printf("Got old game ver gameshark code base address %08X\n", base_gameshark_code_address);
    unsigned int base_to_write_val = (gameshark_code_address - base_gameshark_code_address); // Offset to where the write value is written to from the base address
    printf("Got old game ver gameshark code base address offset for write value: %X\n", base_to_write_val);
    unsigned short gameshark_code_value = strtoul(argv[2], NULL, 16) & 0xFFFF;
    printf("Got old game ver gameshark code value %04X\n", gameshark_code_value);
    unsigned char gameshark_code_write_values[2];
    gameshark_code_write_values[0] = gameshark_code_value;
    gameshark_code_write_values[1] = (gameshark_code_value>>8);
    printf("Write byte 1 in big endian %X\n", gameshark_code_write_values[0]);
    printf("Write byte 2 in big endian %X\n", gameshark_code_write_values[1]);

    if((mem_dump_1 = fopen(argv[3], "rb")) != NULL)
    {
        fseek(mem_dump_1, 0, SEEK_END);
        mem_dump_1_size = ftell(mem_dump_1);

        if(mem_dump_1_size != valid_mem_dump_size)
        {
            printf("Error: the old game ver RAM dump file: %s is not the expected size\n", argv[3]);
            if(mem_dump_1_size == 8388608)
                printf("Do you have the 'Enable 8MB RAM' option enabled? Uncheck that option if so and make a new RAM dump\n");
            fclose(mem_dump_1);
            free(mem_dump_1_buf);
            return;
        }

        fseek(mem_dump_1, 0, SEEK_SET);
        mem_dump_1_buf = (unsigned char *)malloc(mem_dump_1_size * sizeof(unsigned char));

        if(fread(mem_dump_1_buf, 1, valid_mem_dump_size, mem_dump_1) != mem_dump_1_size)
        {
            printf("Error loading old game ver RAM dump file: %s\n", argv[3]);
            fclose(mem_dump_1);
            free(mem_dump_1_buf);
            return;
        }

        printf("Loaded old game ver RAM dump file: %s (%d bytes in memory)\n", argv[3], mem_dump_1_size);
    } else {
            printf("Cannot open the old game ver memory dump file: %s\n", argv[3]);
            return;
    }

    if((mem_dump_2 = fopen(argv[4], "rb")) != NULL) 
    {
        fseek(mem_dump_2, 0, SEEK_END);
        mem_dump_2_size = ftell(mem_dump_2);

        if(mem_dump_2_size != valid_mem_dump_size)
        {
            printf("Error: the new game ver RAM dump file: %s is not the expected size\n", argv[4]);
            if(mem_dump_2_size == 8388608)
                printf("Do you have the 'Enable 8MB RAM' option enabled? Uncheck that option if so and make a new RAM dump\n");
            fclose(mem_dump_1);
            fclose(mem_dump_2);
            free(mem_dump_1_buf);
            free(mem_dump_2_buf);
            return;
        }

        fseek(mem_dump_2, 0, SEEK_SET);
        mem_dump_2_buf = (unsigned char *)malloc(mem_dump_2_size * sizeof(unsigned char));

        if(fread(mem_dump_2_buf, valid_mem_dump_size, 1, mem_dump_2) != mem_dump_2_size)
        {
            printf("Error loading old game ver RAM dump file: %s\n", argv[3]);
            fclose(mem_dump_1);
            fclose(mem_dump_2);
            free(mem_dump_1_buf);
            free(mem_dump_2_buf);
            return;
        }

        printf("Loaded new game ver RAM dump file: %s (%d bytes in memory)\n", argv[4], mem_dump_2_size);
    } else {
        printf("Cannot open the new game ver RAM dump file: %s\n", argv[4]);
        fclose(mem_dump_1);
        free(mem_dump_1_buf);
        return;
    }

    get_start_of_pattern_pos = (gameshark_code_address - base_to_write_val); // Start at beginning of memory address gameshark code is modifying to identify pattern

    for(int i=0; i < 16; i++)
    {
        pattern[i] = mem_dump_1_buf[get_start_of_pattern_pos + i];
        unsigned int current_address = (get_start_of_pattern_pos + i);
        printf("%08X: %02X\n", current_address, pattern[i]);
    }

    if(pattern[base_to_write_val] == gameshark_code_write_values[0])
        printf("Confirmed gameshark code write byte 1: %X in: %s\n", gameshark_code_write_values[0], argv[3]);
    if(pattern[base_to_write_val + 1] == gameshark_code_write_values[1])
        printf("Confirmed gameshark code write byte 2: %X in: %s\n", gameshark_code_write_values[1], argv[3]);

    for(current_fpos = 0; current_fpos < valid_mem_dump_size; current_fpos++)
    {
        for(int i=0; i < 16; i++)
            match_pattern[i] = mem_dump_2_buf[current_fpos + i];

        bool match = true;
        for(int i=0; i < 16; i++)
        {
            if(match_pattern[i] != pattern[i])
                match = false;
        }

        if(match)
        {
            printf("\nGot pattern match in %s starting at base address: %08X\n", argv[4], current_fpos);
            printf("Got new write val offset at address: %08X\n", current_fpos + base_to_write_val);
            gameshark_code_address = (current_fpos + base_to_write_val);
            bytes=(unsigned char *)&gameshark_code_address;
            bytes[3] = gameshark_prefix; // the 80 or D0 is a prefix for the gameshark code type, the actual memory location is 00 in this part of the address
            gameshark_code_address = bytes[0] + (bytes[1] << 8) + (bytes[2] << 16) + (bytes[3] << 24); // NOT BIG-ENDIAN SAFE
            printf("Got new game ver gameshark code: %08X %02X%02X\n", gameshark_code_address, gameshark_code_write_values[1], gameshark_code_write_values[0]);
        }
    }

    fclose(mem_dump_1);
    fclose(mem_dump_2);
    free(mem_dump_1_buf);
    free(mem_dump_2_buf);
}

int main (int argc, const char * argv[]) 
{
    printf("APrip v%s By Alex Free (C)2022-2023 (3-BSD)\nhttps://alex-free.github.io/aprip\n\n", VER);

   if(argc == 3)
    {
        if((strcmp("-b", argv[1])) == 0) {
            printf("Mode: BIN patcher (APv2)\n");
            if((bin = fopen(argv[2], "rb+")) != NULL)
            {
                bin_patch(argv);
            } else {
                printf("Error: Cannot open the BIN file: %s\n", argv[2]);
        	   return(1);
            }
        } else if((strcmp("-gs", argv[1])) == 0) {
            printf("Mode: gameShark code generation (APv2)\n");
            if((mem_dump_1 = fopen(argv[2], "rb")) != NULL)
            {
                gameshark_gen(argv);
            } else {
                printf("Error: Cannot open the RAM dump file: %s\n", argv[2]);
                return(1);
            }
        } else {
            printf("Error: The first argument should be either -gs or -b if you want to use a 2 argument function\n");
            return(1);
        }
    } else if (argc == 4) {
        if((strcmp("-b", argv[1])) == 0) {
        printf("Mode: BIN patcher (LibCrypt v1/LibCrypt v2)\n");
            if((bin = fopen(argv[3], "rb+")) != NULL)
            {
                bin_patch_libcrypt(argv);
            } else {
                printf("Error: Cannot open the BIN file: %s\n", argv[3]);
        	   return(1);
            }
        }
    } else if (argc == 5) {
        printf("Mode: GameShark code converter\n");
        sharkconv(argv);
    } else {
        printf("Error: Incorrect number of arguments\nUsage:\n\naprip -b <.bin file>\n(Patch BIN file directly)\n\naprip -b <magic word> <.bin file>\n(Patch BIN file containing LibCrypt 2 protection directly)\n\naprip -gs <unpatched game Duckstation RAM dump>\n(Create GameShark anti-piracy bypass code)\n\naprip <old game ver code address (80XXXXXX or D0XXXXXX)> <old game ver code 16-bit write or compare value> <unpatched old game ver Duckstation memory dump> <unpatched new game ver Duckstation memory dump>\n(Convert an existing GameShark code from one revision/version to another of the same game)\n");
        return(1);
    }  
}