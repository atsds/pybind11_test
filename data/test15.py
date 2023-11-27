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
  
def test_reference_internal():
  def sub():
    get_cls = my_module15.GetClass()
    return get_cls.get_reference_internal()
  sub()
  print('-----')
  tmp = sub()
  print('addr(py)=', tmp.id())
  
def test_automatic():
  get_cls = my_module15.GetClass()
  print('--- pointer')
  tmp = get_cls.get_auto()
  print('addr(py)=', tmp.id())
  del tmp
  print('--- lvalue')
  tmp = get_cls.lvalue()
  print('addr(py)=', tmp.id())
  del tmp
  print('--- rvalue')
  tmp = get_cls.rvalue()
  print('addr(py)=', tmp.id())
  del tmp
  print('----- ')
  
def test_dupli():
  get_cls = my_module15.GetClass()
  tmp3 = get_cls.get_ref()
  print('get_auto addr(py)=', tmp3.id())
  # 以下をコメントアウトするとオブジェクトが残り、以後のcopyとmoveが行われなくなる
  del tmp3
  print('----- ')
  tmp2 = get_cls.get_copy()
  print('get_copy addr(py)=', tmp2.id())
  del tmp2
  print('----- ')
  tmp1 = get_cls.get_move()
  print('get_move addr(py)=', tmp1.id())
  del tmp1
  print('----- ')
