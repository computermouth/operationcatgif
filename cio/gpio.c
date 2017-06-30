#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define CHIPPRO_GPIO_ROOT "/sys/class/gpio"
#define CHIPPRO_GPIO_EXPO "/sys/class/gpio/export"
#define CHIPPRO_GPIO_P_NO "132"
#define CHIPPRO_GPIO_P_D0 "/sys/class/gpio/gpio132"
#define CHIPPRO_GPIO_DIRE "/sys/class/gpio/gpio132/direction"
#define CHIPPRO_GPIO_VALU "/sys/class/gpio/gpio132/value"

int dir_exists(DIR* test_dir){
	
	if (test_dir) {
		closedir(test_dir);
		return 1;
	}
	
	return 0;
}

int main(void){
	
	printf("Begin GPIO control in C\n");
	
	// check for the gpio directory
	DIR* root_dir = opendir(CHIPPRO_GPIO_ROOT);
	if ( ! dir_exists(root_dir) ){
		fprintf( stderr, 
			"%s does not exist, or couldn't be accessed\n", 
			CHIPPRO_GPIO_ROOT);
		return 1;
	}
	
	// see if the pin needs to be exported
	DIR* p_d0_dir = opendir(CHIPPRO_GPIO_P_D0);
	if ( dir_exists(p_d0_dir) == 0 ){
		// export the pin
		FILE *export_fp = NULL;
		export_fp = fopen(CHIPPRO_GPIO_EXPO, "w");
		if(export_fp == NULL){
			fprintf( stderr, 
				"%s does not exist, or couldn't be accessed\n", 
				CHIPPRO_GPIO_EXPO);
			return 1;
		}
		// write the pin number to export
		if ( fprintf(export_fp, CHIPPRO_GPIO_P_NO) != (sizeof(CHIPPRO_GPIO_P_NO) / sizeof(char)) - 1) {
			fprintf( stderr, 
				"failed to write '%s'[%ld] to %s\n", 
				CHIPPRO_GPIO_P_NO, sizeof(CHIPPRO_GPIO_P_NO), CHIPPRO_GPIO_EXPO);
			return 1;
		}
		// (flush && close) or failure
		if ( fflush(export_fp) != 0 || fclose(export_fp) ){
			fprintf( stderr, 
				"failed to flush and close %s\n", 
				CHIPPRO_GPIO_P_NO);
			return 1;
		}
		
		fprintf(stdout, "successfully exported %s\n", CHIPPRO_GPIO_P_NO);
	} else {
		fprintf(stdout, "%s was found already exported\n", CHIPPRO_GPIO_P_NO);
	}
	
	// set the direction of the pin
	FILE *direction_fp = NULL;

	direction_fp = fopen(CHIPPRO_GPIO_DIRE, "w");
	if(direction_fp == NULL){
		fprintf( stderr, 
			"%s does not exist, or couldn't be accessed\n", 
			CHIPPRO_GPIO_DIRE);
		return 1;
	}
	
	if ( fprintf(direction_fp, "out") != (sizeof("out") - 1) ) {
		fprintf( stderr, 
			"failed to write 'out'[%ld] to %s\n", 
			sizeof("out"), CHIPPRO_GPIO_DIRE);
		return 1;
	}
	// (flush && close) or failure
	if ( fflush(direction_fp) != 0 || fclose(direction_fp) ){
		fprintf( stderr, 
			"failed to flush and close %s\n", 
			CHIPPRO_GPIO_DIRE);
		return 1;
	}
	
	fprintf(stdout, "%s direction set to 'out'\n", CHIPPRO_GPIO_P_NO);
	
	char value[] = "1";
	
	while( 1 ){
		// open the pin file
		FILE *value_fp = NULL;
		value_fp = fopen(CHIPPRO_GPIO_VALU, "w");
		if(value_fp == NULL){
			fprintf( stderr, 
				"%s does not exist, or couldn't be accessed\n", 
				CHIPPRO_GPIO_VALU);
			return 1;
		}
		
		// set the pin value
		if ( fprintf(value_fp, value) != (sizeof(value[0])) ) {
			fprintf( stderr, 
				"failed to write '%c'[%ld] to %s\n", 
				value[0], sizeof("0"), CHIPPRO_GPIO_VALU);
			printf("fpf: %d\n", fprintf(value_fp, value));
			return 1;
		}
		
		// (flush && close) or failure
		if ( fflush(value_fp) != 0 || fclose(value_fp) ){
			fprintf( stderr, 
				"failed to flush and close %s\n", 
				CHIPPRO_GPIO_VALU);
			return 1;
		}
		
		fprintf(stdout, "%s set to '%c'\n", CHIPPRO_GPIO_P_NO, value[0]);
		
		if( value[0] == '0')
			value[0] = '1';
		else
			value[0] = '0';
		
		usleep(1000000);
		
	}
	
	return 0;
}
