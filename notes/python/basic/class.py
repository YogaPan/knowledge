class Person(object):
    people = []

    def __init__(self, *, name, age):
        self.name = name
        self.age = age
        self.__class__.people.append(self)

    def say(self):
        print(self.name, self.age)

    def __repr__(self):
        return "<{0} {1}>".format(self.name, self.age)

    @classmethod
    def count(cls):
        print(cls.people)

def main():
    yoga = Person(name='yoga', age=20)
    husky = Person(name='husky', age=0)
    Person.count()

if __name__ == '__main__':
    main()
