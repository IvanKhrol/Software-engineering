# First task on qt

## Setup build environment and build 

Сборка и запуск производятся в Qt Creator для правильной запуска релиза и дебага используется CMakeLists.txt.user

## Отличия от стандартной библиотеки C++:

* Сигналы и слоты: В Qt используется механизм сигналов и слотов для реализации взаимодействия между объектами, что является альтернативой стандартным обработчикам событий C++.
* QDebug: Qt предоставляет объект QDebug для вывода отладочной информации, предлагающий дополнительные возможности по сравнению с стандартными функциями вывода.
* QString: Класс QString предоставляет более удобные и безопасные методы для работы со строками по сравнению с стандартным типом std::string:
  1. C++ не содержит класса String, а STL содержит.
  2. STL String основана на 8 битах, в то время как QString основана на Unicode, поэтому мы можем выразить с помощью QString вещи, которые мы не смогли бы выразить с помощью std::string
  3. QString во многих отношениях быстрее, чем std::string
  4. QString обладает многими функциональными возможностями, которых нет у std::string
  5. QString обладает практически всеми полезными функциями std::string