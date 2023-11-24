import my_module14

class test_class_py:
  def __init__(self, a):
    print('a.value =', a.value)

  def hello(self, a):
    print('hello')

def test_unique_ptr():
  var = my_module14.create_unique()
  print('test_unique_ptr', var.value)
  
def test_bad_unique_ptr():
  var = my_module14.create_bad_unique()
  print('test_bad_unique_ptr', var.value)
  
def test_shared_ptr():
  var = my_module14.create_shared()
  print('test_shared_ptr', var.value)
