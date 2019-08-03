import assert from 'assert'

try {
  assert.equal(3, 4)
} catch (err) {
  console.log('test failed.')
}
