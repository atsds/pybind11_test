import my_module15

def test_copy():
  tmp = my_module15.get()
  print('addr(py)=', tmp.id())
  
def test_take_ownership():
  tmp = my_module15.get_take_ownership()
  print('addr(py)=', tmp.id())
  
def test_move():
  tmp = my_module15.get_move()
  print('addr(py)=', tmp.id())
  
def test_reference():
  tmp = my_module15.get_reference()
  print('addr(py)=', tmp.id())
  
def test_reference_internal_ng():
  tmp = my_module15.get_reference_internal_ng()
  print('addr(py)=', tmp.id())
  
def test_reference_internal1():
  def sub():
    get_cls = my_module15.get_class()
    return get_cls.get_reference_internal()
  sub()
  print('addr(py)=')
  
def test_reference_internal2():
  def sub():
    get_cls = my_module15.get_class()
    return get_cls.get_reference_internal()
  tmp = sub()
  print('addr(py)=', tmp.id())

def test_automatic1():
  get_cls = my_module15.get_class()
  tmp = get_cls.get_automatic()
  print('addr(py)=', tmp.id())

def test_automatic2():
  get_cls = my_module15.get_class()
  tmp = get_cls.get()
  print('addr(py)=', tmp.id())
