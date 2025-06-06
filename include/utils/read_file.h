#ifndef READ_FILE_H
#define READ_FILE_H

/**
 * Reads the full contents of a file and returns it as a string.
 * Returns NULL if the file cannot be opened.
 */
char *read_file_content(const char *filename);

#endif
