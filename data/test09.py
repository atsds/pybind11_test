import sys, importlib

def test1(module_name):
  if 'data/subdir' not in sys.path:
    sys.path.append('data/subdir')
  module = importlib.import_module(module_name)
  effect_cls = getattr(module, module_name)
  try:
    effect = effect_cls()
    effect.hello()
  except:
    print('getattr failed?')
