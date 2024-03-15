#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Usage: %s <filename>\n", argv[0]);
		return 1;
	}

	char *filename = argv[1];
	struct stat file_stat;

	if (stat(filename, &file_stat) == -1) {
		perror("Error");
		return 1;
	}

	printf("File: %s\n", filename);
	printf("Size: %ld bytes\n", file_stat.st_size);
	printf("Permissions: %o\n", file_stat.st_mode & 0777);
	printf("Owner UID: %d\n", file_stat.st_uid);
	printf("Group GID: %d\n", file_stat.st_gid);
	printf("Last access time: %ld\n", file_stat.st_atime);
	printf("Last modification time: %ld\n", file_stat.st_mtime);
	printf("Last status change time: %ld\n", file_stat.st_ctime);

	return 0;
}
