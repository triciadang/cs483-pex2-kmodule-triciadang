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

	//opens the device, r/w access
	fd = open("/dev/cs483driver", O_RDWR);

	//error checking
	if (fd<0){
		perror("Failed to open the device...");
		return errno;
	}

	//initializes str variable
	char str[BUFFER_LENGTH] = "";
	
	//prompts user for input
	printf("Type in a short string to send to the kernel module: ");

	//gets string of 256 characters
	fgets(str, BUFFER_LENGTH, stdin);

	//writes input to device
	printf("Writing to the device...\n");
	ret = write(fd, str, BUFFER_LENGTH);

	//error checking
	if (ret < 0){
		perror("Failed to write message to the device.");
		return errno;
	}

	//initializes receive variable
	char receive[BUFFER_LENGTH] = "";
	printf("Reading from the device...\n");

	//reads the response from the LKM
	ret = read(fd, receive, BUFFER_LENGTH);

	//error checking
	if (ret < 0){
		perror("Failed to read message from the device.");
		return errno;
	}
	else{
		printf("String read from the device: ");
		printf("%s", receive);
	}

	//closes the device
	close(fd);

	return 0;
}
