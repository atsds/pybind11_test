import my_module07

def child_func():
  t3 = my_module07.Test(3)
  print(str(t3))
  
def test():
  t = my_module07.Test(1)
  t.hello()
  del t
  print('---')
  t2 = my_module07.Test(2)
  with t2:
    t2.hello()
  print('---')
  child_func()
  print('*** FUNCTION END ***')
