// =================================================================================================
// includes
#include "pch.h"

// =================================================================================================
// using
using namespace std;

// =================================================================================================
// member functions

// -----------------------------------------------------------------------------------------------
void hello() {
  printf("---------------------------------------------------------------------" __FUNCTION__ "\n");
  py::scoped_interpreter guard{};
  py::print("Hello, World!");
}

// -----------------------------------------------------------------------------------------------
void embed_test01_py_to_cpp() {
  printf("---------------------------------------------------------------------" __FUNCTION__ "\n");
  py::scoped_interpreter guard{};
  py::module sys = py::module::import("sys");
  py::cast<py::list>(sys.attr("path")).append("./data");
  py::module_ m = py::module_::import("test01");
  // ---------------------------------------------------------------------------
  py::object r_int = m.attr("output_int")();
  printf("%d\n", r_int.cast<int>());
  // ---------------------------------------------------------------------------
  py::object r_str = m.attr("output_str")();
  printf("%s\n", r_str.cast<string>().c_str());
  // ---------------------------------------------------------------------------
  py::list r_li = m.attr("output_listint")();
  for (auto x : r_li) printf("%d ", py::cast<int>(x)); // 直接ループ回せる
  auto r_li2 = py::cast<std::vector<int> >(r_li);
  for (auto x : r_li2) printf("%d ", x);
  printf("\n");
  // ---------------------------------------------------------------------------
  py::dict r_di = m.attr("output_dictint")();
  for (auto x : r_di) {
    printf("%s=%d ", py::cast<string>(x.first).c_str(), py::cast<int>(x.second));
  }
  auto r_di2 = py::cast<std::unordered_map<string, int> >(r_di);
  for (auto x : r_di2) {
    printf("%s=%d ", x.first.c_str(), x.second);
  }
  printf("\n");
}

// -----------------------------------------------------------------------------------------------
void embed_test02_cpp_to_py() {
  printf("---------------------------------------------------------------------" __FUNCTION__ "\n");
  py::scoped_interpreter guard{};
  py::module sys = py::module::import("sys");
  py::cast<py::list>(sys.attr("path")).append("./data");
  py::module_ m = py::module_::import("test02");
  // ---------------------------------------------------------------------------
  py::object r_int = m.attr("input_int")(1, 2);
  printf("r_int=%d\n", r_int.cast<int>());
  // ---------------------------------------------------------------------------
  py::object r_str = m.attr("input_str")("1", "2");
  printf("r_str=%d\n", r_str.cast<int>());
  // ---------------------------------------------------------------------------
  py::object r_li = m.attr("input_listint")(vector<int>{ 1, 2, 3 });
  printf("li=%d\n", r_li.cast<int>());
  // ---------------------------------------------------------------------------
  py::object r_di = m.attr("input_dictint")(unordered_map<string, int>{ {"a", 1}, {"b", 2} });
  printf("di=%d\n", r_di.cast<int>());
}

// -----------------------------------------------------------------------------------------------
int cppadd(int a, int b) {
  return a + b;
}

string cppadd_str(string a, string b) {
  return a + b;
}

PYBIND11_EMBEDDED_MODULE(my_module, m) {
  using namespace pybind11::literals;
  m.doc() = "pybind11 example for test03";
  m.def("cppadd", &cppadd);
  m.def("cppadd", &cppadd, py::arg("a")=3, py::arg("b")=4);
  m.def("cppadd2", &cppadd, "a"_a=33, "b"_a=44);
  m.def("cppadd_str", &cppadd_str, "a"_a="xxx", "b"_a="yyy");
}

void embed_test03_myfunc() {
  printf("---------------------------------------------------------------------" __FUNCTION__ "\n");
  py::scoped_interpreter guard{};
  py::module sys = py::module::import("sys");
  py::cast<py::list>(sys.attr("path")).append("./data");
  py::module_ m = py::module_::import("test03");
  printf("func01=%d\n", m.attr("func01")().cast<int>());
  printf("func02=%d\n", m.attr("func02")().cast<int>());
  printf("func03=%d\n", m.attr("func03")().cast<int>());
  printf("func04=%s\n", m.attr("func04")().cast<string>().c_str());
}

// -----------------------------------------------------------------------------------------------
class Animal {
public:
  virtual ~Animal() {}
  virtual string go(int p_times) = 0;
};
// PyAnimalはPython側でAnimalを基底とした派生クラスCatを作る時に必要となる
// (普通に渡すとgoが純粋仮想関数なのでAnimalをインスタンス化できない)
class PyAnimal : public Animal {
  string go(int p_times) override { PYBIND11_OVERRIDE_PURE(std::string, Animal, go, p_times); }
};

class Dog : public Animal {
public:
  string go(int p_times) override {
    string result = "";
    for (int i = 0; i < p_times; i++) {
      result += "woof! ";
    }
    return result;
  }
  string ote() { return "ote"; }
};

string call_go(Animal *p_animal) { return p_animal->go(3); }

PYBIND11_EMBEDDED_MODULE(my_module04, m) {
  using namespace pybind11::literals;
  m.doc() = "pybind11 example for test04";
  py::class_<Animal, PyAnimal>(m, "Animal")
    .def(py::init<>())
    .def("go", &Animal::go);
  py::class_<Dog, Animal>(m, "Dog")
    .def(py::init<>())
    .def("ote", &Dog::ote);
  m.def("call_go", &call_go);
}

void embed_test04_class() {
  printf("---------------------------------------------------------------------" __FUNCTION__ "\n");
  py::scoped_interpreter guard{};
  py::module sys = py::module::import("sys");
  py::cast<py::list>(sys.attr("path")).append("./data");
  py::module_ m = py::module_::import("test04");
  printf("call_go_dog=%s\n", m.attr("call_go_dog")().cast<string>().c_str());
  printf("call_go_cat=%s\n", m.attr("call_go_cat")().cast<string>().c_str());
  printf("call_ote_dog=%s\n", m.attr("call_ote_dog")().cast<string>().c_str());
  try {
    m.attr("call_ote_cat")();
  } catch (py::error_already_set &e) {
    py::print(string(e.what()) + "\n");
  }
}

// -----------------------------------------------------------------------------------------------
class Test {
public:
  Test() {
  }
  string hello() { return "hello."; }
  static Test* create() { return new Test(); }
};

PYBIND11_EMBEDDED_MODULE(my_module05, m) {
  using namespace pybind11::literals;
  m.doc() = "pybind11 example for test05";
  py::class_<Test>(m, "Test")
    .def(py::init<>())
    .def("hello", &Test::hello);
  m.def("create", &Test::create);
}

void embed_test05_pass_obj_bidirectional() {
  printf("---------------------------------------------------------------------" __FUNCTION__ "\n");
  py::scoped_interpreter guard{};
  py::module sys = py::module::import("sys");
  py::cast<py::list>(sys.attr("path")).append("./data");
  py::module_ m = py::module_::import("test05");
  m.attr("from_cpp")();
  py::object obj = m.attr("to_cpp")();
  printf("%s\n", obj.cast<Test>().hello().c_str());
}

// -----------------------------------------------------------------------------------------------
enum EnumTest {
  ON = 0,
  OFF,
  Unknown,
};

PYBIND11_EMBEDDED_MODULE(my_module06, m) {
  using namespace pybind11::literals;
  m.doc() = "pybind11 example for test06";
  py::enum_<EnumTest>(m, "EnumTest")
    .value("On", EnumTest::ON)
    .value("Off", EnumTest::OFF);
}

void embed_test06_enum() {
  printf("---------------------------------------------------------------------" __FUNCTION__ "\n");
  py::scoped_interpreter guard{};
  py::module sys = py::module::import("sys");
  py::cast<py::list>(sys.attr("path")).append("./data");
  py::module_ m = py::module_::import("test06");
  printf("toggle(on)=%d\n", m.attr("toggle")(EnumTest::ON).cast<EnumTest>() == EnumTest::OFF);
  printf("toggle(off)=%d\n", m.attr("toggle")(EnumTest::OFF).cast<EnumTest>() == EnumTest::ON);
}

// -----------------------------------------------------------------------------------------------
class Test07 {
public:
  Test07(int no) { no_ = no; }
  virtual ~Test07() { printf("desctructor called. no=%d\n", no_); }
  void hello() { printf("hello\n"); }
  string to_string() { return "no=" + std::to_string(no_); }
  Test07& _enter() { printf("with enter.\n"); return *this; }
  bool   _exit(py::args) { printf("with exit.\n"); return false; }
  int no_;
};

PYBIND11_EMBEDDED_MODULE(my_module07, m) {
  using namespace pybind11::literals;
  py::class_<Test07>(m, "Test")
    .def(py::init<int>())
    .def("hello", &Test07::hello)
    .def("__str__", &Test07::to_string)
    //.def("__enter__", [](Test07& self) -> Test07& {
    //  printf("with enter called.\n"); return self; }, py::return_value_policy::reference)
    //.def("__exit__", [](Test07& self, py::args) {
    //  printf("with exit called.\n"); return false; });
    .def("__enter__", &Test07::_enter, py::return_value_policy::reference)
    .def("__exit__", &Test07::_exit);
}

void embed_test07_destructor() {
  printf("---------------------------------------------------------------------" __FUNCTION__ "\n");
  py::scoped_interpreter guard{};
  py::module sys = py::module::import("sys");
  py::cast<py::list>(sys.attr("path")).append("./data");
  py::module_ m = py::module_::import("test07");
  try {
    m.attr("test")();
  } catch (py::error_already_set &e) {
    py::print(string(e.what()) + "\n");
  }
}

// -----------------------------------------------------------------------------------------------
class Vector2 {
public:
  Vector2(float x, float y) { x_ = x; y_ = y; }
  Vector2 operator+(const Vector2& p) const { return Vector2(x_ + p.x_, y_ + p.y_); }
  void out() const { printf("%.3f, %.3f\n", x_, y_); }
  float x_;
  float y_;
  static const Vector2 one;
  static Vector2 cmn;
};
const Vector2 Vector2::one(1.0f, 1.0f);
Vector2 Vector2::cmn(0.0f, 0.0f);

PYBIND11_EMBEDDED_MODULE(my_module08, m) {
  using namespace pybind11::literals;
  py::class_<Vector2>(m, "Vector2")
    .def(py::init<float, float>())
    .def("out", &Vector2::out)
    .def("__add__", &Vector2::operator+)
    .def_readwrite("x", &Vector2::x_)
    .def_readonly("y", &Vector2::x_)
    .def_property_readonly_static("one", [](py::object) { return Vector2::one; })
    .def_property_static("cmn", [](py::object) -> Vector2& { return Vector2::cmn; },
                                [](py::object, const Vector2& a) { Vector2::cmn = a; });
}

void embed_test08_operator() {
  printf("---------------------------------------------------------------------" __FUNCTION__ "\n");
  py::scoped_interpreter guard{};
  py::module sys = py::module::import("sys");
  py::cast<py::list>(sys.attr("path")).append("./data");
  py::module_ m = py::module_::import("test08");
  try {
    m.attr("test")();
  } catch (py::error_already_set &e) {
    py::print(string(e.what()) + "\n");
  }
  try {
    m.attr("test_modify_ok")();
  } catch (py::error_already_set &e) {
    py::print(string(e.what()) + "\n");
  }
  try {
    m.attr("test_modify_ng")();
  } catch (py::error_already_set &e) {
    py::print("test_modify_ng=" + string(e.what()) + "\n");
  }
  try {
    m.attr("test_modify_ng2")();
  } catch (py::error_already_set &e) {
    py::print("test_modify_ng2=" + string(e.what()) + "\n");
  }
  try {
    m.attr("test_modify_ng3")();
  } catch (py::error_already_set &e) {
    py::print("test_modify_ng3=" + string(e.what()) + "\n");
  }
  try {
    m.attr("test_modify_ng4")();
  } catch (py::error_already_set &e) {
    py::print("test_modify_ng4=" + string(e.what()) + "\n");
  }
}

// -----------------------------------------------------------------------------------------------
void embed_test09() {
  printf("---------------------------------------------------------------------" __FUNCTION__ "\n");
  py::scoped_interpreter guard{};
  py::module sys = py::module::import("sys");
  py::cast<py::list>(sys.attr("path")).append("./data");
  py::module_ m = py::module_::import("test09");
  try {
    m.attr("test1")("sub01");
  } catch (py::error_already_set &e) {
    py::print(string(e.what()) + "\n");
  }
}

// -----------------------------------------------------------------------------------------------
class inty {
public:
  long long_value;
};

void printx(inty s) {
  printf("%d\n", s.long_value);
}

PYBIND11_EMBEDDED_MODULE(my_module10, m) {
  using namespace pybind11::literals;
  m.def("printx", &printx);
}

namespace PYBIND11_NAMESPACE { namespace detail {
  template <> struct type_caster<inty> {
  public:
    PYBIND11_TYPE_CASTER(inty, const_name("inty"));

    bool load(handle src, bool) {
      PyObject *source = src.ptr();
      printf("%s(python) to inty(c++)\n", source->ob_type->tp_name);
      PyObject *tmp = PyNumber_Long(source);
      if (!tmp) return false;
      value.long_value = PyLong_AsLong(tmp);
      Py_DECREF(tmp);
      return !(value.long_value == -1 && !PyErr_Occurred());
    }

    static handle cast(inty src, return_value_policy a, handle z) {
      printf("inty(c++) to int(python)\n");
      return PyLong_FromLong(src.long_value);
    }
  };
}}

void embed_test10_implicit_type_convert() {
  printf("---------------------------------------------------------------------" __FUNCTION__ "\n");
  py::scoped_interpreter guard{};
  py::module sys = py::module::import("sys");
  py::cast<py::list>(sys.attr("path")).append("./data");
  py::module_ m = py::module_::import("test10");
  try {
    m.attr("test1")();
  } catch (py::error_already_set &e) {
    py::print(string(e.what()) + "\n");
  }
  try {
    inty n;
    n.long_value = 456;
    m.attr("test2")(n);
  } catch (py::error_already_set &e) {
    py::print(string(e.what()) + "\n");
  }
}

// -----------------------------------------------------------------------------------------------
void embed_test11_manual_interpreter() {
  printf("---------------------------------------------------------------------" __FUNCTION__ "\n");
  py::initialize_interpreter();
  {
    py::module sys = py::module::import("sys");
    py::cast<py::list>(sys.attr("path")).append("./data");
    py::module_ m = py::module_::import("test11");
    m.attr("test")();
  }
  py::finalize_interpreter(); // モジュール類が解放済であること！
}

// -----------------------------------------------------------------------------------------------
void embed_test12_python_class() {
  printf("---------------------------------------------------------------------" __FUNCTION__ "\n");
  py::scoped_interpreter guard{};
  py::module sys = py::module::import("sys");
  py::cast<py::list>(sys.attr("path")).append("./data");
  py::module_ m = py::module_::import("test12");
  py::object cls = m.attr("test_class");
  py::object obj = cls();
  obj.attr("hello")();
  obj.attr("show_msg")();
  cls.attr("classmethod_test")();
}

// -----------------------------------------------------------------------------------------------
void embed_test13_callable_check() {
  printf("---------------------------------------------------------------------" __FUNCTION__ "\n");
  py::scoped_interpreter guard{};
  py::module sys = py::module::import("sys");
  py::cast<py::list>(sys.attr("path")).append("./data");
  py::module_ m = py::module_::import("test13");
  py::object cls = m.attr("test_class");
  py::object obj = cls();
  py::object func = m.attr("func");
  printf("hello callable : %s\n", PyCallable_Check(obj.attr("hello").ptr()) ? "ok" : "ng");
  printf("var   callable : %s\n", PyCallable_Check(obj.attr("var").ptr()) ? "ok" : "ng");
  printf("hello callable : %s\n", PyCallable_Check(func.ptr()) ? "ok" : "ng");
}

// -----------------------------------------------------------------------------------------------
class test_class_cpp {
public:
  test_class_cpp(int p_value) { value = p_value; }
  virtual ~test_class_cpp() { printf("destructor test_class_cpp\n"); }
  int value;
};

class test_class_cpp_hidden {
public:
  test_class_cpp_hidden(int p_value) { value = p_value; }
  virtual ~test_class_cpp_hidden() { printf("destructor test_class_cpp_hidden\n"); }
  int value;
};

test_class_cpp* create_unique() { return new test_class_cpp(567); }

test_class_cpp* raw_obj = new test_class_cpp(345);
test_class_cpp* create_bad_unique() { return raw_obj; }

shared_ptr<test_class_cpp> shared_obj;
shared_ptr<test_class_cpp> create_shared() {
  return shared_obj;
}

void embed_test14() {
  printf("---------------------------------------------------------------------" __FUNCTION__ "\n");
  py::scoped_interpreter guard{};
  py::module sys = py::module::import("sys");
  py::cast<py::list>(sys.attr("path")).append("./data");
  py::module_ m = py::module_::import("test14");
  py::object cls = m.attr("test_class_py");
  auto* v = new test_class_cpp(123);
  // 登録済クラスのポインタの受け渡しはそのままでOK
  printf("************************* CASE 1\n");
  py::object obj = cls(v);
  auto* v2 = new test_class_cpp_hidden(234);
  // 未登録クラスのポインタの受け渡しはNG
  printf("************************* CASE 2\n");
  try {
    obj.attr("hello")(v2);
  } catch (...) {
    printf("cast error occured.\n");
  }
  printf(".\n");
  delete v;
  delete v2;
  // unique_ptr(生ポインタも同様)を返すC++関数はunique_ptrとして扱われる
  printf("************************* CASE 3\n");
  {
    m.attr("test_unique_ptr")();
    // ここでデストラクタが走る
    printf(".\n");
    m.attr("test_bad_unique_ptr")();
    // ここもデストラクタが走るのでraw_objの中身はVSのデバッグビルドによる解放済メモリとなっている
    assert(raw_obj->value == 0xdddddddd);
    printf(".\n");
  }
  // shared_ptr
  printf("************************* CASE 3\n");
  {
    {
      shared_obj = make_shared<test_class_cpp>(678);
      m.attr("test_shared_ptr")();
    printf(".\n");
    }
    // ここでデストラクタが走る
  }
}

PYBIND11_EMBEDDED_MODULE(my_module14, m) {
  using namespace pybind11::literals;
  py::class_<test_class_cpp, std::shared_ptr<test_class_cpp> >(m, "test_class_cpp")
    .def_readwrite("value", &test_class_cpp::value);
  m.def("create_unique", &create_unique);
  m.def("create_bad_unique", &create_bad_unique);
  m.def("create_shared", &create_shared);
}

// -----------------------------------------------------------------------------------------------
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {
int main(int argc, char* argv[]) {
  hello();
  embed_test01_py_to_cpp();
  embed_test02_cpp_to_py();
  embed_test03_myfunc();
  embed_test04_class();
  embed_test05_pass_obj_bidirectional();
  embed_test06_enum();
  embed_test07_destructor();
  embed_test08_operator();
  embed_test09();
  embed_test10_implicit_type_convert();
  embed_test11_manual_interpreter();
  embed_test12_python_class();
  embed_test13_callable_check();
  embed_test14();
  return 0;
}
