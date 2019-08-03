const EventEmitter = require('events').EventEmitter

class MyEmitter extends EventEmitter {}

const myEmitter = new MyEmitter()

myEmitter.on('event', () => {
  console.log('an event occured!')
})

process.on('exit', () => {
  console.log('Good Bye!')
})

myEmitter.emit('event')
