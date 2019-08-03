## Basic syntax and library

### List
```py
a.insert()
a.append()
a.extend()
a.pop()
a.remove()
a.index()
a.sort(hey=function, reverse=True)
a.reverse()
```

### Dictionary
```py
d.update()
d.items()
d.keys()
d.values()
d.pop()
```

### String
```py
```

### Open File
```py
f = open('filename')
for line in f:
    print(line.strip())
```

### JSON
```py
import json

people = json.loads(dateString)
print(date['Yoga'])

a = ['name': 'Yoga']
b = json.dumps(a, indent=4);
```

### XML
```py
import xml.etree.ElementTree as ET

tree = ET.fromString(date)   # Give a string
tree = ET.parse(filename)    # Give a filename

dict = tree.findall('count/dict')
for key in dict:
    print(key.tag)
    print(key.text)
```

### Hash
```py
import hashlib

m = hashlib.md5()
m.update(SALT + word.decode('ascii'))
m.hexdigest()
```

### decorator
- http://www.imooc.com/article/1257
- http://ot-note.logdown.com/posts/67571/-decorator-with-without-arguments-in-function-class-form
