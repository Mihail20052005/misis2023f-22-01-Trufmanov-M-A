# Вопрос по выбору
## "Библиотека std::tuple"
### Выполнил
Студент группы БПМ-22-1 Труфманов Михаил

## Кортежи в программировании
Кортеж (tuple) - это структура данных, представляющая собой 
упорядоченный набор элементов различных типов. Каждый элемент кортежа может быть доступен по индексу.
Кортежи обычно используются для группировки связанных данных в единое целое.
Различные языки программирования предоставляют свои
собственные реализации кортежей с различными возможностями и синтаксисом.

## Основной синтаксис
### Создание кортежа
```c++
std::tuple<int, double, const char*> tup { 10, 42.42, “Hello” }; 
```
### Получение элемента по индексу
```c++
std::cout << std::get<0>(tup) << '\n';
```
### std::swap
```c++
#include <tuple>
int main(){
std::tuple<int, double, char> tuple1(1, 1.1, 'Misha');
std::tuple‹int, double, char> tuple2(2, 2.2, 'Misha2');
std:: swap(tuple1, tuple2);
}
```
### std::tie
```c++
#include <tuple›
int main(){
 
std::tuple<std::string, int, double> personTuple("Misha", 86, 187.2);
std::string name;
int age;
double height;

std::tie(name, age, height) = personTuple;
}
```

## Примеры использования std::tuple
### Согласно Липпману (книга “The C++ Primer” стр. 721) основное применение кортежей в C++ является возврат множественных значений из функции.
```c++
typedef tuple<vector<Sales_data>::size_type,
vector<Sales_data>::const_iterator,
vector<Sales_data>::const_iterator> matches;
vector<matches>
findBook(const vector<vector<Sales_data>> &files,
const string &book)
{
vector<matches> ret;
for (auto it = files.cbegin(); it != files.cend(); ++it) {
auto found = equal_range(it->cbegin(), it->cend(),
book, compareIsbn);
if (found.first != found.second)
ret.push_back(make_tuple(it - files.cbegin(),
found.first, found.second));
}
return ret;
}
```
```c++
void reportResults(istream &in, ostream &os,
const vector<vector<Sales_data>> &files)
{
string s; 
while (in >> s) {
auto trans = findBook(files, s);
if (trans.empty()) {
cout << s << " not found in any stores" << endl;
continue; 
}
for (const auto &store : trans)
os << "store " << get<0>(store) << " sales: "
<< accumulate(get<1>(store), get<2>(store),
Sales_data(s))
<< endl;
}
}
```
### В данном примере мы можем увидеть как используется tuples в качестве типа возвращаемых и принимаемых данных 

### Structured binding (позволяет быстро распаковывать данные)
```c++
#include <tuple>
#include <iostream>

std::tuple<int, double, std::string> getTuple() {
    return std::make_tuple(42, 3.14, "Hello");
}

int main() {
    auto [intValue, doubleValue, stringValue] = getTuple();

    std::cout << intValue << ", " << doubleValue << ", " << stringValue << std::endl;

    return 0;
}
```

### std::apply
#### std::apply, появившаяся в C++17, является удобной вспомогательной функцией для std::tuple. Она принимает кортеж и callable-объект, а затем вызывает этот callable-объект с параметрами, полученными из кортежа. (пример взят из https://habr.com/ru/companies/otus/articles/656363/)

```c++
#include <iostream>
#include <tuple>
int sum(int a, int b, int c);
{
    return a + b + c;
}
void print(std::string_view a, std::string_view b) {
std::cout << "(" << a << ", " << b << ")\n";
}
int main(){
std::tuple numbers {1, 2, 3};
std::cout « std::apply(sum, numbers) « '\n';
std::tuple strs {"Hello", "world"};
std::apply(print, strs);
```

## Список литературы
1.	https://chenweixiang.github.io/docs/The_C++_Programming_Language_4th_Edition_Bjarne_Stroustrup.pdf
2.	https://habr.com/ru/articles/276871/
3.	https://www.appsloveworld.com/cplus/100/4/c-tuple-vs-struct
4.	https://en.cppreference.com/w/cpp/utility/tuple
5.	https://habr.com/ru/companies/otus/articles/655715/
6.	https://moodle.ufsc.br/pluginfile.php/2377667/mod_resource/content/0/Effective_Modern_C__.pdf

