import my_module04

def call_go_dog():
  dog = my_module04.Dog()
  return my_module04.call_go(dog)

class Cat(my_module04.Animal):
  def go(self, n_times):
    return "meow! " * n_times

def call_go_cat():
  cat = Cat()
  return my_module04.call_go(cat)

def call_ote_dog():
  dog = my_module04.Dog()
  return dog.ote()

def call_ote_cat():
  cat = Cat()
  return cat.ote() # raise exception!
