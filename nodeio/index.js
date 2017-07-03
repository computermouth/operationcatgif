'use strict'

const fs = require('fs')

const CHIPPRO_GPIO_ROOT = '/sys/class/gpio'
const CHIPPRO_GPIO_EXPO = '/sys/class/gpio/export'
const CHIPPRO_GPIO_P_NO = '132'
const CHIPPRO_GPIO_P_D0 = '/sys/class/gpio/gpio132'
const CHIPPRO_GPIO_DIRE = '/sys/class/gpio/gpio132/direction'
const CHIPPRO_GPIO_VALU = '/sys/class/gpio/gpio132/value'

// check if gpio root exists
fs.readdir(CHIPPRO_GPIO_ROOT, (err, files) => {
  if (err) logAndExit(err.message)
})

// check if pin directory exists
if (fs.existsSync(CHIPPRO_GPIO_P_NO)) {
  console.log(`pin ${CHIPPRO_GPIO_EXPO} was found to have been previously exported`)
} else {
    // pin not exported, check if export file exists
    if (fs.existsSync(CHIPPRO_GPIO_EXPO)) {
      // export the pin
      fs.writeFileSync(CHIPPRO_GPIO_EXPO, CHIPPRO_GPIO_P_NO)
    } else {
      logAndExit(`${CHIPPRO_GPIO_EXPO} does not exist`)
    }
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
    logAndExit(`${CHIPPRO_GPIO_VALU} does not exist, or couldnt be accessed`)
  }
}, 1000)

function logAndExit(message) {
  console.error(message)
  process.exit(1)
}
