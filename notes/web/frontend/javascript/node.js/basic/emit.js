import { EventEmitter } from 'events'

class MyEmitter extends EventEmitter {}

const myEmitter = new MyEmitter()

myEmitter.on('event', () => {
  console.log('an event occured!')
})

process.on('exit', () => {
  console.log('fuck')
})

myEmitter.emit('event')
