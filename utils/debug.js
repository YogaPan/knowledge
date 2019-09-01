const tapCreator = () => {
  const counter = {}
  return (value, { color = 'BLUE', topic = 'INFO' } = {}) => {
    topic = topic.toUpperCase()
    color = color.toUpperCase()
    counter[topic] ? counter[topic]++ : (counter[topic] = 1)
    const PALETTE = {
      RED: {
        fontColor: '#fff',
        backgroundColor: '#F44336'
      },
      GREEN: {
        fontColor: '#fff',
        backgroundColor: '#4CAF50'
      },
      BLUE: {
        fontColor: '#fff',
        backgroundColor: '#03A9F4'
      },
      ORANGE: {
        fontColor: '#fff',
        backgroundColor: '#FF9800'
      }
    }
    const style = `
      color: ${PALETTE[color].fontColor};
      background-color: ${PALETTE[color].backgroundColor};
      border-radius: 20px;
      padding: 3px 6px;
      margin: 6px 0;
    `
    console.log('%c' + topic + ` #${counter[topic]}`, style, value)
    return value
  }
}

const tap = tapCreator()

const sleep = ms => new Promise(resolve => setTimeout(resolve, ms))
