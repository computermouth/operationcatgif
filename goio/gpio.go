
package main

import (
	"fmt"
	"os"
	"io/ioutil"
	"time"
)

var (
	CHIPPRO_GPIO_ROOT = "/sys/class/gpio"
	CHIPPRO_GPIO_EXPO = "/sys/class/gpio/export"
	CHIPPRO_GPIO_P_NO = "132"
	CHIPPRO_GPIO_P_D0 = "/sys/class/gpio/gpio132"
	CHIPPRO_GPIO_DIRE = "/sys/class/gpio/gpio132/direction"
	CHIPPRO_GPIO_VALU = "/sys/class/gpio/gpio132/value"
)

func pathExists(path string) (bool, error) {
	_, err := os.Stat(path)
	if err == nil {
		return true, nil
	}
	if os.IsNotExist(err) {
		return false, nil
	}
	return false, err
}

func main() {
	
	// check for the gpio directory
	exists, err := pathExists(CHIPPRO_GPIO_ROOT)
	if err != nil || exists == false {
		fmt.Fprintf( os.Stderr, 
			"%s does not exist, or couldn't be accessed\n", 
			CHIPPRO_GPIO_ROOT)
		os.Exit(1)
	}
	
	// see if the pin needs to be exported
	exists, err = pathExists(CHIPPRO_GPIO_P_D0)
	if err != nil {
		fmt.Fprintf( os.Stderr, 
			"%s does not exist, or couldn't be accessed\n", 
			CHIPPRO_GPIO_ROOT)
		os.Exit(1)
	}
	
	if exists != true {
		// check if export file exists
		exists, err = pathExists(CHIPPRO_GPIO_EXPO)
		if err != nil || exists == false{
			fmt.Fprintf( os.Stderr, 
				"%s does not exist, or couldn't be accessed\n", 
				CHIPPRO_GPIO_EXPO)
			os.Exit(1)
		}
		
		// export the pin
		err = ioutil.WriteFile(CHIPPRO_GPIO_EXPO, []byte(CHIPPRO_GPIO_P_NO), 0200)
		if err != nil {
			fmt.Fprintf( os.Stderr, 
				"%s does not exist, or couldn't be accessed\n", 
				CHIPPRO_GPIO_EXPO)
			os.Exit(1)
		}
		
		fmt.Fprintf( os.Stdout, 
			"pin %s was exported\n", 
			CHIPPRO_GPIO_P_NO)
	} else {
		fmt.Fprintf( os.Stdout, 
			"pin %s was found to have been previously exported\n", 
			CHIPPRO_GPIO_P_NO)
	}
	
	// check if direction file exists
	exists, err = pathExists(CHIPPRO_GPIO_DIRE)
	if err != nil || exists == false{
		fmt.Fprintf( os.Stderr, 
			"%s does not exist, or couldn't be accessed\n", 
			CHIPPRO_GPIO_DIRE)
		os.Exit(1)
	}
	
	// set direction to 'out'
	err = ioutil.WriteFile(CHIPPRO_GPIO_DIRE, []byte("out"), 0644)
	if err != nil {
		fmt.Fprintf( os.Stderr, 
			"%s does not exist, or couldn't be accessed\n", 
			CHIPPRO_GPIO_DIRE)
		os.Exit(1)
	}
	
	value := "1"
	for {
		
		// check if value file exists
		exists, err = pathExists(CHIPPRO_GPIO_VALU)
		if err != nil || exists == false{
			fmt.Fprintf( os.Stderr, 
				"%s does not exist, or couldn't be accessed\n", 
				CHIPPRO_GPIO_VALU)
			os.Exit(1)
		}
		
		err = ioutil.WriteFile(CHIPPRO_GPIO_VALU, []byte(value), 0644)
		if err != nil {
			fmt.Fprintf( os.Stderr, 
				"%s does not exist, or couldn't be accessed\n", 
				CHIPPRO_GPIO_DIRE)
			os.Exit(1)
		}
		
		fmt.Fprintf( os.Stdout, 
			"%s was set to '%s'\n", 
			CHIPPRO_GPIO_VALU, value)
		
		if value == "1" {
			value = "0"
		} else {
			value = "1"
		}
		
		time.Sleep(1000 * time.Millisecond)
		
	}
	
	os.Exit(0)
}
