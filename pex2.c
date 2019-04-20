/**Name: Tricia Dang
 * Documentation: I used this website https://linux.die.net/man/2/write to figure out
 * how to use the write command.
 */



#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#define BUFFER_LENGTH 256

int main(){
	int fd;
	ssize_t ret;

	printf("%s", "Starting device test code...\n");

	fd = open("/dev/cs483driver", O_RDWR);
	if (fd<0){
		perror("Failed to open the device...");
		return errno;
	}

	char str[BUFFER_LENGTH];
	printf("Type in a short string to send to the kernel module: ");
	fgets(str, BUFFER_LENGTH, stdin);

	printf("Writing to the device...\n");
	ret = write(fd, str, 256);
	if (ret < 0){
		perror("Failed to write message to the device.");
		return errno;
	}

	char receive[BUFFER_LENGTH];
	printf("Reading from the device...\n");
	ret = read(fd, receive, BUFFER_LENGTH);
	if (ret < 0){
		perror("Failed to read message from the device.");
		return errno;
	}
	else{
		printf("String read from the device: ");
		printf("%s", receive);
	}
	close(fd);

	return 0;
}