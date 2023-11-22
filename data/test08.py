import my_module08

def test():
  v = my_module08.Vector2(1.2, 1.3)
  (v + my_module08.Vector2(2.2, 2.3)).out()
  
def test_modify_ok():
  v = my_module08.Vector2.one
  v.x = 2.0
  v.out()

def test_modify_ng():
  v = my_module08.Vector2.one
  v.y = 2.0 # 書き換え不能
  v.out()

def test_modify_ng2():
  my_module08.Vector2.one.x = 2.0 # エラーにはならないがoneは書き換えされない
  my_module08.Vector2.one.out()

def test_modify_ng3():
  my_module08.Vector2.one = my_module08.Vector2(2.0, 2.0) # 置き換え不可
  
def test_modify_ng4():
  my_module08.Vector2.cmn.x = 1.5 # 書き換え可能
  my_module08.Vector2.cmn.out()
