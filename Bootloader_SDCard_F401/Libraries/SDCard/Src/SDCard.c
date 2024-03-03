/*
 * SDCard.c
 *
 *  Created on: 22-Jun-2022
 *      Author: Lakshay
 */

#include "SDCard.h"

//=======================================================================================//
//---------------------------------------------------------------------------------------//
/*
 * FA_OPEN_EXISTING (0x00):
 * Opens the file if it exists.
 * Returns an error if the file does not exist.
 * FA_CREATE_NEW (0x04):
 * Creates a new file.
 * Returns an error if the file already exists.
 * FA_CREATE_ALWAYS (0x08):
 * Creates a new file.
 * If the file already exists, it truncates the file to zero length.
 * FA_OPEN_ALWAYS (0x10):
 * Opens the file if it exists.
 * If the file does not exist, it creates a new file.
 * FA_OPEN_APPEND (0x30):
 * Opens the file if it exists.
 * If the file does not exist, it creates a new file.
 * The file pointer is set to the end of the file before each write operation.
 */
//---------------------------------------------------------------------------------------//
//=======================================================================================//
uint8_t sd_mount(sdcard_t *sdcard_type, const TCHAR parentPath[10]) {
	//Open the file system
	snprintf(sdcard_type->parentPath, 10, parentPath);
	strcpy(sdcard_type->currentPath, sdcard_type->parentPath);

	sdcard_type->fres = f_mount(&sdcard_type->FatFs, sdcard_type->parentPath,
			1); //1=mount now
	return (sdcard_type->fres == FR_OK) ? 1 : 0;
}

uint8_t sd_unMount(sdcard_t *sdcard_type) {
	//We're done, so de-mount the drive
	sdcard_type->fres = f_mount(NULL, "", 0);
	return (sdcard_type->fres == FR_OK) ? 1 : 0;
}

uint8_t sd_space(sdcard_t *sdcard_type) {
	//Let's get some statistics from the SD card
	FATFS *getFreeFs;
	sdcard_type->fres = f_getfree(sdcard_type->parentPath,
			&sdcard_type->free_clusters, &getFreeFs);
	if (sdcard_type->fres != FR_OK) {
		sdcard_type->free_clusters = 0;
		sdcard_type->free_sectors = 0;
		sdcard_type->total_sectors = 0;
	} else {
		//Formula comes from ChaN's documentation
		sdcard_type->total_sectors = ((getFreeFs->n_fatent - 2)
				* getFreeFs->csize) / 2;
		sdcard_type->free_sectors = (sdcard_type->free_clusters
				* getFreeFs->csize) / 2;
	}
	return (sdcard_type->fres == FR_OK) ? 1 : 0;
}

uint8_t sd_fileExists(sdcard_t *sdcard_type, char *filename) {
	//If your file exists
	sdcard_type->fres = f_stat(filename, &sdcard_type->fno);
	return (sdcard_type->fres == FR_OK) ? 1 : 0;
}

uint8_t sd_removeFile(sdcard_t *sdcard_type, char *filename) {
	if (sd_fileExists(sdcard_type, filename)) {
		sdcard_type->fres = f_unlink(filename);
	}
	return (sdcard_type->fres == FR_OK) ? 1 : 0;
}

static uint8_t sd_open(sdcard_t *sdcard_type, char *filename, BYTE mode) {
	sdcard_type->fres = f_open(&sdcard_type->fil, filename, mode);
	return (sdcard_type->fres == FR_OK) ? 1 : 0;
}

static uint8_t sd_close(sdcard_t *sdcard_type) {
	sdcard_type->fres = f_close(&sdcard_type->fil);
	return (sdcard_type->fres == FR_OK) ? 1 : 0;
}

static uint8_t sd_read(sdcard_t *sdcard_type, char *buf, UINT btr) {
	sdcard_type->fres = f_read(&sdcard_type->fil, buf, btr, &sdcard_type->br);
	return (sdcard_type->fres == FR_OK) ? 1 : 0;
}

static uint8_t sd_write(sdcard_t *sdcard_type, char *data) {
	sdcard_type->fres = f_write(&sdcard_type->fil, data, strlen(data),
			&sdcard_type->bw);
	return (sdcard_type->fres == FR_OK) ? 1 : 0;
}

static uint8_t sd_seek(sdcard_t *sdcard_type, DWORD offset) {
	sdcard_type->fres = f_lseek(&sdcard_type->fil, offset);
	return (sdcard_type->fres == FR_OK) ? 1 : 0;
}

/*
 * It will create a new file and if file exists then delete it to make new.
 */
uint8_t sd_createFile(sdcard_t *sdcard_type, char *filename) {
	uint8_t fileLoc[100] = { 0 };
	sd_updatefileLoc(sdcard_type, filename, fileLoc);
	if (sd_open(sdcard_type, fileLoc, FA_CREATE_ALWAYS | FA_READ | FA_WRITE)) {
		if (sd_close(sdcard_type)) {
			return true;
		}
	}
	return false;
}

/*
 * Checks if file exists
 */
uint8_t sd_writeFile(sdcard_t *sdcard_type, char *filename, char *data,
		uint16_t dataLen) {
	uint8_t fileLoc[100] = { 0 };
	sd_updatefileLoc(sdcard_type, filename, fileLoc);

	if (sd_fileExists(sdcard_type, fileLoc)) {
		if (sd_open(sdcard_type, fileLoc, FA_OPEN_EXISTING | FA_WRITE)) {
			if (sd_write(sdcard_type, data)) {
				if (sd_close(sdcard_type)) {
					return true;
				}
			}
		}
	}
	return false;
}

uint8_t sd_readFile(sdcard_t *sdcard_type, char *filename, char *buf, UINT btr) {
	uint8_t fileLoc[100] = { 0 };
	sd_updatefileLoc(sdcard_type, filename, fileLoc);
	if (sd_fileExists(sdcard_type, fileLoc)) {
		if (sd_open(sdcard_type, fileLoc, FA_READ)) {
			if (sd_read(sdcard_type, buf, btr)) {
				if (sd_close(sdcard_type)) {
					return true;
				}
			}
		}
	}
	return false;
}

uint8_t sd_updatefile(sdcard_t *sdcard_type, char *filename, char *data,
		uint16_t dataLen) {
	uint8_t fileLoc[100] = { 0 };
	sd_updatefileLoc(sdcard_type, filename, fileLoc);
	if (sd_fileExists(sdcard_type, fileLoc)) {
		if (sd_open(sdcard_type, fileLoc, FA_OPEN_APPEND | FA_WRITE)) {
			if (sd_write(sdcard_type, data)) {
				if (sd_close(sdcard_type)) {
					return true;
				}
			}
		}
	}
	return false;
}

uint8_t sd_fileseekread(sdcard_t *sdcard_type, char *filename, DWORD offset,
		char *buf, UINT btr) {
	uint8_t fileLoc[100] = { 0 };
	sd_updatefileLoc(sdcard_type, filename, fileLoc);
	if (sd_fileExists(sdcard_type, filename)) {
		if (sd_open(sdcard_type, filename, FA_READ)) {
			if (sd_seek(sdcard_type, offset)) {
				if (sd_read(sdcard_type, buf, btr)) {
					if (sd_close(sdcard_type)) {
						return true;
					}
				}
			}
		}
	}
	return false;
}

uint8_t sd_getFileInfo(sdcard_t *sdcard_type, char *filename){
	uint8_t fileLoc[100] = { 0 };
	sd_updatefileLoc(sdcard_type, filename, fileLoc);
	sdcard_type->fres = f_stat(filename, &sdcard_type->fno);
	return (sdcard_type->fres == FR_OK) ? 1 : 0;
}
/*Original one*/
uint8_t sd_createDir(sdcard_t *sdcard_type) {
	sdcard_type->fres = f_mkdir(sdcard_type->currentPath);
	return (sdcard_type->fres == FR_OK) ? 1 : 0;
}

uint8_t sd_openDir(sdcard_t *sdcard_type) {
	if (sd_dirExists(sdcard_type)) {
		sdcard_type->fres = f_opendir(&sdcard_type->dir,
				sdcard_type->currentPath);
		return (sdcard_type->fres == FR_OK) ? 1 : 0;
	}
	return 0;
}

uint8_t sd_dirExists(sdcard_t *sdcard_type) {
	sdcard_type->fres = f_stat(sdcard_type->currentPath, &sdcard_type->fno);
	return (sdcard_type->fres == FR_OK) ? 1 : 0;
}

uint8_t sd_removeDir(sdcard_t *sdcard_type) {
	if (sd_dirExists(sdcard_type)) {
		sdcard_type->fres = f_unlink(sdcard_type->currentPath);
		if (sdcard_type->fres == FR_OK) {
			sd_dirGoBack(sdcard_type);
			return 1;
		}
	}
	return 0;
}

void sd_closeDir(sdcard_t *sdcard_type) {
	sdcard_type->fres = f_closedir(&sdcard_type->dir);
	return (sdcard_type->fres == FR_OK) ? 1 : 0;
}

void sd_changeDir(sdcard_t *sdcard_type, const char *newDir) {
    // Update the current directory path
	int result = strcmp(sdcard_type->parentPath, sdcard_type->currentPath);
	if (!result) {
		sprintf(sdcard_type->currentPath, "%s%s", sdcard_type->currentPath,
				newDir);

	} else {
		sprintf(sdcard_type->currentPath, "%s/%s", sdcard_type->currentPath, newDir);
	}

}

void sd_resetDir(sdcard_t *sdcard_type) {
    // Reset the current directory path to the parent path
    strcpy(sdcard_type->currentPath, sdcard_type->parentPath);
}

void sd_dirGoBack(sdcard_t *sdcard_type){
	int rec = strcmp(sdcard_type->parentPath, sdcard_type->currentPath);
	if (!rec)
		return;
	char *lastSlash = strrchr(sdcard_type->currentPath, '/');
	if (lastSlash != NULL) {
		if (lastSlash != sdcard_type->currentPath) {
			*lastSlash = '\0';
		} else {
			sdcard_type->currentPath[1] = '\0'; // Keep only the '/' character
		}
	}
}

void sd_updatefileLoc(sdcard_t *sdcard_type, char *filename, char *buf) {

	int rec = strcmp(sdcard_type->parentPath, sdcard_type->currentPath);
	if (!rec) {
		sprintf(buf, "%s%s", sdcard_type->currentPath, filename);
	} else {
		sprintf(buf, "%s/%s", sdcard_type->currentPath, filename);
	}
}

