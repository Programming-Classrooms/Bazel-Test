# Конфигурация C++ проeкта на Bazel в VS Code (под ОС Linux)

## 1. Установка дополнительных пакетов

Сперва необходимо обновить пакетный менеджер `apt` и установить компиляторы `gcc` и `g++`:

```sh
sudo apt update && sudo apt install gcc g++ -y
```

Также установим утилиты `apt-transport-https`, `curl`, `gnupg` для работы с сетью:

```sh
sudo apt apt-transport-https curl gnupg -y
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

*(этот шаг можно пропустить)*

```sh
sudo apt update && sudo apt full-upgrade
```

**WARN:** Учтите, что может потребоваться немалое кол-во свободного места на диске. Перед тем, как ввести **'y'** вниммательно прочитайте какие пакеты будут обновлены и сколько свободного места займёт обновление

Для проверки успешности установки пропишите стандартную команду

```sh
bazel --version
```
