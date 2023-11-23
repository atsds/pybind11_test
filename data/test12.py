
class test_class:
  def __init__(self):
    print('constructor.')
    self.msg = 'xxx'

  def hello(self):
    print('hello')

  def show_msg(self):
    print(self.msg)

  @classmethod
  def classmethod_test(cls):
    print('classmethod')
