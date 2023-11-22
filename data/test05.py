import my_module05

def from_cpp():
  obj = my_module05.create()
  print(obj.hello())

def to_cpp():
  obj = my_module05.Test()
  return obj
