# Конфигурация C++ проeкта на Bazel в VS Code (под ОС Linux)

## 1. Установка дополнительных пакетов

Сперва необходимо обновить пакетный менеджер `apt` и установить компиляторы `gcc`, `g++`, `clang`:

```sh
sudo apt update && sudo apt install gcc g++ clang -y
```

Также установим утилиты `curl`, `apt-transport-https`, `gnupg` для работы с сетью:

```sh
sudo apt install curl apt-transport-https gnupg -y
```

## 2. Установка Bazel

Приступим к установке `bazel`.

Так как **Bazel** не включен в стандартные репозитории большинства дистрибутивов Linux, сразу при помощи пакетного менеджера его установить не получится, нужно добавить его вручную.

### Подготовка к установке

Добавьте **ключ GPG** (ключевое кольцо) официального репозитория **Bazel**:

```sh
curl -fsSL https://bazel.build/bazel-release.pub.gpg | gpg --dearmor >bazel-archive-keyring.gpg
```

Переместите **ключевое кольцо** в директорию системных ключевых колец, где `apt` хранит доверенные ключи для верификации пакетов и репозиториев:

```sh
sudo mv bazel-archive-keyring.gpg /usr/share/keyrings
```

Добавьте репозиторий **Bazel** в список источников `apt`:

```sh
echo "deb [arch=amd64 signed-by=/usr/share/keyrings/bazel-archive-keyring.gpg] https://storage.googleapis.com/bazel-apt stable jdk1.8" | sudo tee /etc/apt/sources.list.d/bazel.list
```

### Установка и обновление

Наконец, можно приступить к непосредственной установке через `apt`

```sh
sudo apt update && sudo apt install bazel
```

Для надёжности можно обновить и остальные системные пакеты следующей командой

*(этот шаг можно пропустить, может потребоваться немалое кол-во свободного места на диске. Перед тем, как ввести **'y'** внимательно прочитайте какие пакеты будут обновлены и сколько свободного места займёт обновление)*

```sh
sudo apt update && sudo apt full-upgrade
```

Для проверки успешности установки пропишите стандартную команду

```sh
bazel --version
```

## 3. Архитектура Bazel проекта

_(Все файлы, о которых пойдёт речь, создаются вручную. Сделать это можно с помощью команд `touch`, `nano` или при помощи графического интерфейса ОС)_

### WORKSPACE

В **Bazel** для определения корня проекта используется файл **WORKSPACE**, в котором раньше прописывались зависимости и некоторые настройки. На момент написания этого туториала Bazel всё ещё поддерживает подтягивание зависимостей через файл **WORKSPACE**, однако в Google документации по **Bazel** указано, что с новыми версиями эта поддержка пропадёт, она полностью мигрирует на `bzlmod` архитектуру, которую мы и будем использовать. А **WORKSPACE** принято оставлять пустым, можно разве что написать поясняющий комментаний:

```sh
## WORKSPACE


# This file marks the root of the Bazel workspace.
# See MODULE.bazel for external dependencies setup.
```

*(P.S. первая строка, начинающаяся с "##" показывает о каком файле идёт речь, её не нужно воспринимать как содержимое файла)*

 Подробнее о миграции с **WORKSPACE** на **Bzlmod**: [Bzlmod Migration Guide](https://bazel.build/external/migration).

### .bazelrc

Ещё одним ключевым файлом в Bazel-проекте является **.bazelrc** (помещается в корневой директории). Там прописываются используемые при сборке компиляторы, стандарты языка, некоторые настройки обработчика ошибок, настройки разных пользовательских типов сборок (да, он и такое умеет). 

Так вот для перехода на ранее упомянутый **bzlmod** необходимо в **.bazelrc**  прописать:

```sh
## .bazelrc

common --enable_bzlmod
```

### MODULE.bazel

Теперь управление зависимостями происходит через файл **MODULE.bazel** (помещается в корневой директории), который инициализируется следующим:

```sh
## MODULE.bazel

module(
    name = "cpp_app",
    repo_name = "cpp_app",
    version = "1.0",
    compatibility_level = 1
)
```

Рассмотрим подключение внешних зависимостей на примере библиотеки тестирования `googletest`. В **bzlmod** есть одна интересная особенность: для него был написан **Bazel Central Registry** ([BCR](https://registry.bazel.build/)) - реестр, содержащий проверенные репозитории популярных библиотек, которые можно подтягивать в **MODULE.bazel** с указанием только названия и версии модуля:

```sh
## MODULE.bazel

bazel_dep(name = "googletest", version = "1.14.0")
```

Для того, чтобы подтянуть библиотеку, которой нет в **BCR** (какую-нибудь [`bee2`](https://github.com/agievich/bee2) *С.В. Агиевича*), можно воспользоваться синтаксисом, который использовался и в старых версиях в **WORKSPACE**:

```sh
## MODULE.bazel

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
http_archive(
    name = "foo",
    urls = ["https://example.com/foo.zip"],
    sha256 = "c9526390a7cd420fdcec2988b4f3626fe9c5b51e2959f685e8f4d170d1a9bd96"
)
```

где поле `sha256` - это хэш скачиваемого архива (очевидно, хеш-функции **SHA256**), который нужно указать заранее.


Подробнее о **bzlmod**: [External dependencies overview](https://bazel.build/external/overview#bzlmod)

### MODULE.bazel.lock

После первого запуска сборки **Bazel** сгенерирует ещё один файл - **MODULE.bazel.lock**. Это системный файл, который хранит формальное описание подключенных модулей в **json** формате, модифицировать его вручную не понадобится. 

### BUILD

Под каждый отдельный модуль в **Bazel** создаётся новая директория, с файлом **BUILD** в ней. В этом файле описывается специфика модуля, все его зависимости, видимость для других модулей проекта.

---

### Модули

Перейдём к конфигурированию модулей самого кода. Предположим, нашей целью является написание класса для работы с дробями. Сперва нужно определиться, где именно будет лежать код. Для этого создадим директорию **src/**, в которой будем хранить весь код. Создадим также директорию первого модуля `main` - **src/main/**, в котором будет **main.cpp** и определяющий этот модуль **BUILD** файл, содержимое которого рассмотрим чуть позже. 

Нам понадобятся ещё 2 модуля: `fraction` (файлы класса `Fraction`) и `tests` (тесты проекта) в директориях **src/fraction/** и **src/tests/** соответственно. В **src/fraction/** поместим файл заголовка класса **Fraction.hpp** и файл реализации **Fraction.cpp**, а в **src/tests/** файл с тестами для этого класса **FractionTest.cpp**. Помимо файлов с кодом в каждой из директорий нужно создать **BUILD** файл.

### Описание модулей

В **BUILD** файле модуля `fraction` укажем, что это **библиотека**, **имя модуля**, какие именно **файлы в него входят** и **видимость** модуля:

```sh
## src/fraction/BUILD

cc_library(
    name = "fraction",
    srcs = ["Fraction.cpp"],
    hdrs = ["Fraction.hpp"],
    visibility = ["//visibility:public"],
)
```

Теперь опишем модуль `main`. Назовём его "**cpp_app**":

```sh
## src/main/BUILD

cc_binary(
    name = "cpp_app",
    srcs = ["main.cpp"],
    deps = [
        "//src/fraction:fraction",
    ],
)
```

Для модуля `tests` укажем в его **BUILD** файле, что это модуль с **тестами**, который использует внешний модуль `googletest` и внутренний модуль `fraction`:

```sh
## src/tests/BUILD

cc_test(
    name = "tests",
    srcs = ["FractionTest.cpp"],
    deps = [
        "@googletest//:gtest_main",
        "//src/fraction:fraction",
    ]
)
```

### Сборка проекта

После того, как весь код написан, можно пробовать запускать сборку проекта:

```sh
bazel build //src/main:cpp_app
```

При **первом запуске** начнётся загрузка внешних модулей, если такие прописаны в **MODULES.bazel** (в нашем случае это модуль `googletest`), поэтому убедитесь в стабильном подключении к сети.

Скомпилированный **исполняемый файл** программы будет лежать по пути **bazel-bin/src/main/cpp_app**. Запустить, находясь в **корне проекта**, можно следующим образом:

```sh
./bazel-bin/src/main/cpp_app
```

Также **Bazel** позволяет собрать и сразу запустить скомпилированную программу при помощи команды `run`:

```sh
bazel run //src/main:cpp_app
```


После первой сборки также появятся **символические ссылки** (sym links, soft links) на следующие директории:

### bazel-bin

Cодержит **бинарные файлы**, которые были скомпилированы во время сборки. Используется и для хранения всех **сгенерированных артефактов**, которые могут быть непосредственно использованы или запущены пользователем. В зависимости от конфигурации проекта, здесь могут находиться **собранные программы**, **динамические** и **статические библиотеки** После успешного выполнения сборки вы найдете **конечные исполняемые файлы** внутри этой директории 

### bazel-out

Cодержит все **промежуточные файлы**, сгенерированные во время процесса сборки. Это включает **объектные файлы**, **временные файлы компиляции**, а также различные **артефакты**, специфичные для разных целей сборки (например, для разных платформ или конфигураций)

### bazel-testlogs

Предназначена для хранения **логов тестирования**. В этой директории собираются файлы журналов и результаты тестов, выполненных с помощью **Bazel**. Это включает подробные отчёты о прохождении тестов, ошибки, предупреждения и другую информацию, полезную для анализа результатов тестирования

### bazel-projectname

Эта директория является **рабочим каталогом Bazel** для конкретного проекта. **projectname** будет заменено на имя вашего проекта. Bazel использует эту директорию для хранения всех своих внутренних рабочих файлов, включая **промежуточные артефакты**, **кэшированные данные** и **инструменты для сборки**. Это корневая директория, в которой находятся все остальные специфичные для Bazel директории, поэтому не стоит удивляться "дублированию" директорий проекта в этой директории. Это **не копии**, а **символические ссылки** на них

Т.е. после первой сборки архитектура проекта должна выглядеть примерно так:

![image](https://github.com/Programming-Classrooms/Bazel-Test/assets/105939033/265eb8bc-1197-46d1-afe4-f106a9b8e703)


---

Чтобы запустить все тесты модуля `tests` нужно прописать:

```sh
bazel test //src/tests:all
```

Здесь разными параметрами можно указать вид вывода, кэширование результатов, вывод только успешных/провальных тестов и т.д. 

Подробнее о командах **Bazel** и их параметрах можно узнать здесь: [Command-Line Reference](https://bazel.build/reference/command-line-reference)

### Анализ покрытия кода тестами с `bazel coverage`

=== TODO: разобраться с ошибкой пустого файла с результатами ===


## 4. Настройка VS Code под Bazel проект

**Visual Studio Code** (VS Code, VSC) - крайне гибкая, легкая, кроссплатформенная, бесплатная IDE. При помощи своего открытого каталога расширений и возможности вручную настраивать разные сценарии выполнения сборки, тестирования, анализа кода она позволяет сконфигурировать среду под проект на любом языке и платформе. Поэтому конфигурировать наш проект мы будем именно на **VS Code**. 

Скачать последнюю версию **VS Code** можно здесь: [vscode-download](https://code.visualstudio.com/download). После установки, запустите **VSC** и откройте папку с **Bazel-проектом**. 

### Интеграция с Git

В VSC из коробки есть поддержка `git`, поэтому сразу инициализируйте там `git`-репозиторий и свяжите его с удалённым, если это нужно (подробнее в туториале **GitAndGitHub.md**). Шаблон **.gitignore** для Bazel-проекта вы можете найти в шаблонном репозитории организации. 

### Установка расширений

Для начала необходимо установить расширения. Сделать это можно при помощи графического интерфейса раздела **Extensions** *(Ctrl + Shift + X)* или командами при помощи **VS Code Quick Open** строки *(Ctrl + P)*. Будем использовать последний способ:

- **C/C++**: `ext install ms-vscode.cpptools`
- **Bazel**: `ext install BazelBuild.vscode-bazel`
- **vscode-icons**: `ext install vscode-icons-team.vscode-icons`

![image](https://github.com/Programming-Classrooms/Bazel-Test/assets/105939033/0ac5d95f-1724-40ae-a787-da01a4550590)


После того, как расширения установлены, можно приступать к настройке самого проекта. В **VSC** для хранения файлов с настройками проекта используется директория **.vscode** (должна находиться в корневой директории), поэтому создайте её, если ещё этого не сделали. Как правило, файлы с настройками имею **.json** расширение.

Начнём с файла настроек **C/C++**:

### c_cpp_properties.json

```json
{
    "configurations": [
        {
            "name": "Linux",
            "includePath": [
                /*   "/**" - means recursive search     */
                "${workspaceFolder}/bazel-bin/**",
                "${workspaceFolder}/bazel-out/**",
                "${workspaceFolder}/bazel-${workspaceFolderBasename}/**"
            ],
            "intelliSenseMode": "${default}",
            "cppStandard": "c++20"
        }
    ],
    "version": 4
}
```

Здесь в поле **"includePath"** указывается список директорий, в которых **IntelliSense** будет искать остальные файлы C/C++ кода. Назначение остальных полей очевидно.

*(**IntelliSense** - это система, которая предоставляет **контекстно-зависимые подсказки**, **автозаполнение кода**, а также **предварительный просмотр** и **анализ возможных вариантов завершения кода**)*

Подробнее о **c_cpp_properties.json** здесь: [c-cpp-properties-json](https://code.visualstudio.com/docs/cpp/c-cpp-properties-schema-reference)


### tasks.json

**tasks.json** используется для настройки и управления задачами в вашем рабочем пространстве. Задачи в **VSC** — это операции, которые могут быть автоматизированы для упрощения разработки, такие как сборка проекта, запуск скриптов, или другие командные операции, которые вы обычно выполняете в терминале. 

Нашими основными задачами будут **сборка _release_-версии проекта**, **сборка _debug_-версии проекта**, **сборка тестов**:

```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "bazel-build-debug",
            "type": "shell",
            "command": "bazel build //src/main:cpp_app --config=debug ",
            "group": "build"
        },
        {
            "label": "bazel-build-release",
            "type": "shell",
            "command": "bazel build //src/main:cpp_app --config=release ",
            "group": "build"
        },
        {
            "label": "bazel-test",
            "type": "shell",
            "command": "bazel test //src/test:all --test_output=all --nocache_test_results || [ $? -eq 3 ] && exit 0", 
            "group": "test"
        }
    ]
}
```

Если у вас возникло недопонимание последней части команды сборки тестов:

В **bash** у каждой команды, как и у каждой программы на C++, есть **код возврата**. Все коды возврата кроме `0` обозначают некоторую ошибку. Код возврата **последней выполненной команды** содержится в переменной `$?`, а оператор `||` производит выполнение **следующей за ним команды** **только в том случае**, если **команда перед ним** вернула НЕ `0`. Его противоположность - оператор `&&`, который выполняет следующую команду только в случае успешного завершения предыдущей. `bazel test` возвращает `0`, если все тесты пройдены успешно. Если же сам запуск тестов произведён успешно, но некоторые тесты не прошли, то `bazel test` вернёт код `3`, который будет восприниматься средой как краш самой команды `bazel test`, за счёт чего не запустится скомпилированный файл с тестами. Поэтому и была написана такая конструкция, чтобы это предотвратить и в случае успешного выполнения команды, но провала некоторых тестов всё равно запустить скомпилированный файл.  

Подробнее о **tasks.json** здесь: [tasks-json](https://code.visualstudio.com/docs/editor/tasks)

### launch.json
 
**launch.json** используется для настройки и управления конфигурациями сборки и отладки вашего проекта. Этот файл позволяет настроить, каким образом VSCode будет запускать и отлаживать ваше приложение. 

```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "Bazel Debug",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}/bazel-bin/src/main/cpp_app",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "externalConsole": false,  
            "MIMode": "gdb",
            "miDebuggerArgs": "-q -ex quit; wait() { fg >/dev/null; }; /bin/gdb -q --interpreter=mi",
            "miDebuggerPath": "/usr/bin/gdb",
            "setupCommands": [
                {
                    "description": "Enable pretty-printing for gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": false
                }
            ],
            "preLaunchTask": "bazel-build-debug"
        },
        {
            "name": "Bazel Release",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}/bazel-bin/src/main/cpp_app",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "miDebuggerArgs": "-q -ex quit; wait() { fg >/dev/null; }; /bin/gdb -q --interpreter=mi",
            "preLaunchTask": "bazel-build-release" 
        },
        {
            "name": "Bazel Test",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}/bazel-bin/src/tests/tests",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "externalConsole": false,
            "MIMode": "gdb",
            "miDebuggerArgs": "-q -ex quit; wait() { fg >/dev/null; }; /bin/gdb -q --interpreter=mi",
            "preLaunchTask": "bazel-test"
        }
    ]
}
```

Здесь прописаны 3 конфигурации, которые запускают исполняемые файлы того, что соберут соответсвующие задачи в **tasks.json**. 

Label задачи, которая выполняется перед запуском, прописан в поле **"preLaunchTask"**. 

В поле **"miDebuggerArgs"** прописаны аргументы, которые позволяют скрыть системные сообщения отладчика. 

Поле **"externalConsole"** содержит булево значение и в случае `true` запускает прописанный в поле **"program"** исполняемый файл во внешнем терминале. В противном случае, файл исполняется во встроенном терминале VSCode.

В **debug** сборке можно заметить поле **"setupCommands"**, в котором указан **-enable-pretty-printing** - параментр отладчика `gdb`, который позволяет красиво выводить значения **STL**-контейнеров: 

![2024-02-19 08 42 37](https://github.com/Programming-Classrooms/Bazel-Test/assets/105939033/bc410152-80e1-4d09-9ff1-407a8c429c89)


Все написанные конфигурации можно запустить в разделе **Run and Debug** *(Ctrl + Shift + D)* кнопкой `F5`.

![image](https://github.com/Programming-Classrooms/Bazel-Test/assets/105939033/38f2efb1-67d7-4701-86c7-22e295599d9a)


Подробнее о **launch.json** здесь: [launch-json](https://code.visualstudio.com/docs/editor/debugging)

Подробнее о **launch.json** в контексте C/C++ сборки здесь: [launch-json-cpp](https://code.visualstudio.com/docs/cpp/launch-json-reference)

### settings.json

**settings.json** представляет собой конфигурационный файл, в котором хранятся пользовательские и рабочие настройки редактора 

```json
{
    "C_Cpp.default.cppStandard": "c++20",

    "telemetry.telemetryLevel": "off",

    "editor.tabSize": 4,
    "editor.insertSpaces": true,
    "editor.formatOnSave": false,

    "workbench.colorTheme": "Default Dark+",
    "workbench.iconTheme": "vscode-icons",
    "editor.fontFamily": "Consolas",
    "editor.fontSize": 15,

    "workbench.editor.highlightModifiedTabs": true,
    
    "files.trimFinalNewlines": true,

    "explorer.sortOrder": "default",

    "files.autoSave": "onFocusChange",

    "files.exclude": {
        "**/.git": true,
        "**/.github": true,
        "**/.DS_Store": true
    }
}
```

![image](https://github.com/Programming-Classrooms/Bazel-Test/assets/105939033/7b4e9d54-ea03-4967-be5e-70dbbc3873d8)


Подробнее о **settings.json** здесь: [settings-json](https://code.visualstudio.com/docs/getstarted/settings)

---

На этом настройка завершена.
