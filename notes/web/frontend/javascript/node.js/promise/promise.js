const fuck = str => {
  return new Promise((resolve, reject) => {
    if (str !== 'fuck') return reject('Wrong!! You have to talk dirty word!')
    console.log(str)
    return str.length
  })
}

fuck()
  .then(len => {
    console.log(len)
  })
  .catch(err => {
    console.log(err)
  })
