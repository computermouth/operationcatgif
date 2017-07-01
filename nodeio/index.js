'use strict'

const fs = require('fs')

const CHIPPRO_GPIO_ROOT = '/sys/class/gpio'
const CHIPPRO_GPIO_EXPO = '/sys/class/gpio/export'
const CHIPPRO_GPIO_P_NO = '132'
const CHIPPRO_GPIO_P_D0 = '/sys/class/gpio/gpio132'
const CHIPPRO_GPIO_DIRE = '/sys/class/gpio/gpio132/direction'
const CHIPPRO_GPIO_VALU = '/sys/class/gpio/gpio132/value'
const FILE_NOT_FOUND_CODE = 'ENOENT'


// check for the gpio directory
fs.readdir(CHIPPRO_GPIO_ROOT, (err, files) => {
  if (err) logAndExit(err.message)
  
  // see if the pin needs to be exported
  fs.readdir(CHIPPRO_GPIO_P_D0, (err, files) => {
    if (err && err !== FILE_NOT_FOUND_CODE) logAndExit(err.message)
    if (err === FILE_NOT_FOUND_CODE) {
      
      // check if export file exists
      if (fs.existsSync(CHIPPRO_GPIO_EXPO)) {
        
        // export the pin
        fs.writeFileSync(CHIPPRO_GPIO_EXPO, CHIPPRO_GPIO_P_NO)
        console.log(`pin ${CHIPPRO_GPIO_P_NO} was exported`)
      } else {
        logAndExit(`${CHIPPRO_GPIO_EXPO} does not exist, or couldn't be accessed`)
      }
    } else {
      console.log(`pin ${CHIPPRO_GPIO_EXPO} was found to have been previously exported`)
    }
    
    // check if direction file exists
    if (fs.existsSync(CHIPPRO_GPIO_DIRE)) {
      
      // set direction to 'out'
      fs.writeFileSync(CHIPPRO_GPIO_DIRE, "out")
    } else {
      logAndExit(`${CHIPPRO_GPIO_DIRE} does not exist`)
    }
    
    
    let value = 1
    setInterval(() => {
      
      // check if value file exists
      if (fs.existsSync(CHIPPRO_GPIO_VALU)) {
        fs.writeFileSync(CHIPPRO_GPIO_VALU, value)
        
        if (value === 1) {
          value = 0
        } else {
          value = 1
        }
        
        console.log(`${CHIPPRO_GPIO_VALU} was set to ${value}`)
      } else {
        logAndExit(`${CHIPPRO_GPIO_VALU} does not exist, or couldn't be accessed`)
      }
    }, 1000)
  })
})

function logAndExit(message) {
  console.error(message)
  process.exit(1)
}
