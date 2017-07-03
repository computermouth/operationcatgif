
use std::path::Path;
use std::io::Write;
use std::process;
use std::fs::File;
use std::{thread, time};

static CHIPPRO_GPIO_ROOT: &'static str = "/sys/class/gpio";
static CHIPPRO_GPIO_EXPO: &'static str = "/sys/class/gpio/export";
static CHIPPRO_GPIO_P_NO: &'static str = "132";
static CHIPPRO_GPIO_P_D0: &'static str = "/sys/class/gpio/gpio132";
static CHIPPRO_GPIO_DIRE: &'static str = "/sys/class/gpio/gpio132/direction";
static CHIPPRO_GPIO_VALU: &'static str = "/sys/class/gpio/gpio132/value";

fn main() {
	
	// check if gpio directory exists
	if ! Path::new(CHIPPRO_GPIO_ROOT).exists(){
		let _  = write!(&mut std::io::stderr(),
			"{} does not exist, or couldn't be accessed\n", 
			CHIPPRO_GPIO_ROOT);
		process::exit(1);
	}
	
	// check if pin needs to be exported
	if Path::new(CHIPPRO_GPIO_P_D0).exists(){
		let _  = write!(&mut std::io::stdout(),
			"{} was found previously exported\n", 
			CHIPPRO_GPIO_P_D0);
	} else {
		// open the export file
		let mut file = match File::create(&CHIPPRO_GPIO_EXPO) {
			Ok(file) => file,
			Err(_) => panic!( "{} does not exist, or couldn't be accessed\n", 
				CHIPPRO_GPIO_EXPO),
		};

		// write the pin value to the export file
		match file.write_all(CHIPPRO_GPIO_P_NO.as_bytes()) {
			Err(_) => panic!( "{} does not exist, or couldn't be accessed\n", 
				CHIPPRO_GPIO_EXPO),
			Ok(_) => println!( "successfully exported {}\n", 
				CHIPPRO_GPIO_P_D0),
		}
	}
	
	// check if direction file exists
	if ! Path::new(CHIPPRO_GPIO_DIRE).exists(){
		let _  = write!(&mut std::io::stderr(),
			"{} does not exist, or couldn't be accessed\n", 
			CHIPPRO_GPIO_DIRE);
		process::exit(1);
	} else {
		// open the direction file
		let mut file = match File::create(&CHIPPRO_GPIO_DIRE) {
			Ok(file) => file,
			Err(_) => panic!( "{} does not exist, or couldn't be accessed\n", 
				CHIPPRO_GPIO_DIRE),
		};

		// write 'out' to direction file
		match file.write_all("out".as_bytes()) {
			Err(_) => panic!( "{} does not exist, or couldn't be accessed\n", 
				CHIPPRO_GPIO_DIRE),
			Ok(_) => println!( "successfully set direction to '{}'\n", 
				CHIPPRO_GPIO_DIRE),
		}
	}
	
	let mut value = "1";
	let delay = time::Duration::from_millis(1000);
	
	loop {
		
		// check if direction file exists
		if ! Path::new(CHIPPRO_GPIO_VALU).exists(){
			let _  = write!(&mut std::io::stderr(),
				"{} does not exist, or couldn't be accessed\n", 
				CHIPPRO_GPIO_VALU);
			process::exit(1);
		} else {
			// open the direction file
			let mut file = match File::create(&CHIPPRO_GPIO_VALU) {
				Ok(file) => file,
				Err(_) => panic!( "{} does not exist, or couldn't be accessed\n", 
					CHIPPRO_GPIO_VALU),
			};

			// write 'out' to direction file
			match file.write_all(value.as_bytes()) {
				Err(_) => panic!( "{} does not exist, or couldn't be accessed\n", 
					CHIPPRO_GPIO_DIRE),
				Ok(_) => println!( "successfully set value to '{}'\n", 
					value),
			}
		}
		
		thread::sleep(delay);
		
		if value == "1" {
			value = "0"
		} else {
			value = "1"
		}
		
	}
	
}
