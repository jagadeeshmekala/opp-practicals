# Object Oriented Programming (C++) - Practicals

Lab practicals for the Object Oriented Programming subject, written in C++.
Every program was compiled with `g++ -std=c++17 -Wall` and tested.
Output of each program is in the [`outputs`](outputs) folder.

## Practical List

| No. | Topic | Source file | Output |
|-----|-------|-------------|--------|
| 1 | Data types, constants, variables, operators and I/O | `exp1_datatypes_io_operators.cpp` | `outputs/exp1_datatypes_io_operators_output.txt` |
| 2 | Class hierarchy, access specifiers and member functions | `exp2_class_hierarchy_access_specifiers.cpp` | `outputs/exp2_class_hierarchy_access_specifiers_output.txt` |
| 3 | All constructor types, Rule of 5 and memory leak check | `exp3_constructors_rule_of_5.cpp`, `exp3_memory_leak_demo.cpp` | `outputs/exp3_constructors_rule_of_5_output.txt`, `outputs/exp3_leak_check_asan.txt` |
| 4 | Single and multilevel inheritance (Person, Student, GraduateStudent) | `exp4_inheritance_university.cpp` | `outputs/exp4_inheritance_university_output.txt` |
| 5 | Runtime polymorphism (virtual functions, abstract class, Shape) | `exp5_runtime_polymorphism.cpp` | `outputs/exp5_runtime_polymorphism_output.txt` |
| 6 | Compile-time polymorphism (function and operator overloading, Complex) | `exp6_compile_time_polymorphism.cpp` | `outputs/exp6_compile_time_polymorphism_output.txt` |
| 7 | Generic Stack class using templates (int, float, string) | `exp7_template_stack.cpp` | `outputs/exp7_template_stack_output.txt` |
| 8 | STL containers and algorithms on student marks | `exp8_stl_student_marks.cpp` | `outputs/exp8_stl_student_marks_output.txt` |
| 9 | Custom exception hierarchy for banking | `exp9_banking_exceptions.cpp` | `outputs/exp9_banking_exceptions_output.txt` |
| 10 | CSV reader/writer with fstream and file pointers | `exp10_csv_file_io.cpp` | `outputs/exp10_csv_file_io_output.txt` |
| 11 | Mini project | _to be added_ | |

## How to Compile and Run

```bash
g++ -std=c++17 exp1_datatypes_io_operators.cpp -o exp1
./exp1
```

## Memory Leak Check (Experiment 3)

```bash
g++ -g exp3_constructors_rule_of_5.cpp -o exp3
valgrind --leak-check=full ./exp3
```

The leak demo can also be checked with AddressSanitizer:

```bash
g++ -g -fsanitize=address exp3_memory_leak_demo.cpp -o leak && ./leak
```

## Author

Name: _your name_
Roll No: _your roll number_
