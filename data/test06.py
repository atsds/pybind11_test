import my_module06

def toggle(evalue):
  if evalue == my_module06.EnumTest.Off:
    new_evalue = my_module06.EnumTest.On
  else:
    new_evalue = my_module06.EnumTest.Off
  print('{0} > {1}'.format(evalue.name, new_evalue.name))
  return new_evalue
