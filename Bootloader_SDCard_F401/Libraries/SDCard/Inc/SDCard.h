#ifndef SDCARD_INC_SDCARD_H_
#define SDCARD_INC_SDCARD_H_

#include "fatfs.h"
//#include "BML_DRIVER.h"
#include "stdbool.h"

typedef struct{
	//some variables for FatFs
	uint8_t mounted;
	const TCHAR parentPath[10];
	TCHAR currentPath[100];
	FATFS FatFs; 	//Fatfs handle
	FIL fil; 		//File handle
	FRESULT fres; //Result after operations
	FILINFO fno;
	UINT br, bw;  // File read/write count
	DWORD free_sectors;
	DWORD total_sectors;
	DWORD free_clusters;
	DIR dir;
}sdcard_t;
/*
 * Raw file operation fnctions. Do not use.
 */
static uint8_t sd_open(sdcard_t *sdcard_type, char* filename, BYTE mode);
static uint8_t sd_close(sdcard_t *sdcard_type);
static uint8_t sd_read(sdcard_t *sdcard_type, char *buf, UINT btr);
static uint8_t sd_write(sdcard_t *sdcard_type, char *data);
static uint8_t sd_seek(sdcard_t *sdcard_type, DWORD offset);

/*
 * SD Card Info Functions.
 */
uint8_t sd_mount(sdcard_t *sdcard_type, const TCHAR parentPath[10]);
uint8_t sd_unMount(sdcard_t* sdcard_type);
uint8_t sd_space(sdcard_t *sdcard_type);

/*
 * SD Card file operation functions to use.
 */
uint8_t sd_fileExists(sdcard_t *sdcard_type, char* filename);
uint8_t sd_removeFile(sdcard_t *sdcard_type, char* filename);
uint8_t sd_writeFile(sdcard_t *sdcard_type, char* filename, char *data, uint16_t dataLen);
uint8_t sd_createFile(sdcard_t *sdcard_type, char* filename);
uint8_t sd_readFile(sdcard_t *sdcard_type, char* filename, char *buf, UINT btr);
uint8_t sd_fileseekread(sdcard_t *sdcard_type, char *filename, DWORD offset,char *buf, UINT btr);
uint8_t sd_updatefile(sdcard_t *sdcard_type, char *filename, char *data,uint16_t dataLen);
uint8_t sd_getFileInfo(sdcard_t *sdcard_type, char *filename);
void sd_updatefileLoc(sdcard_t *sdcard_type, char *filename, char* buf);

/*
 * SD Card Directory operation functions.
 */
uint8_t sd_removeDir(sdcard_t *sdcard_type);
uint8_t sd_createDir(sdcard_t *sdcard_type);
uint8_t sd_openDir(sdcard_t *sdcard_type);
uint8_t sd_dirExists(sdcard_t *sdcard_type);
void sd_closeDir(sdcard_t *sdcard_type);
void sd_changeDir(sdcard_t *sdcard_type, const char *newDir);
void sd_resetDir(sdcard_t *sdcard_type);
void sd_dirGoBack(sdcard_t *sdcard_type);

#endif /* SDCARD_INC_SDCARD_H_ */
