/**Name: Tricia Dang
 * Documentation: I used this website https://linux.die.net/man/2/write to figure out
 * how to use the write command.
 */

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
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

	int validInput = 0;
    	char str[500] = "";


	//ensures input is within 256 characters
	while (validInput == 0){
		//initializes str variable;
		strcpy(str, "");

		//prompts user for input
		printf("Type in a short string to send to the kernel module: ");

		//gets string of 500 characters
		fgets(str, 500, stdin);

		if (strlen(str) >= 256){
			printf("%s", "Invalid Input. Input a message of 256 characters or less.\n");

		}
		else{
			validInput = 1;
		}

	}


	//writes input to device
	printf("%s", "Writing to the device this message: ");
	printf("%s", str);
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
		printf("The received message is: ");
		printf("%s", receive);
	}

	printf("%s", "End of the program\n");

	//closes the device
	close(fd);

	return 0;
}
