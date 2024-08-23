# fipi_check

Эта программа выполняет периодическую проверку содержимого веб-страницы на наличие строки включающей в себя "2025" и выводит результат в консоль. В противном случае она сообщает, что строка не найдена.

## Требования

Для запуска этой программы на вашем компьютере должно быть установлено следующее программное обеспечение:

- Компилятор C (например, gcc)
- Библиотека libcurl (для работы с HTTP-запросами)

## Установка библиотеки libcurl

### На Ubuntu Linux:

```bash
sudo apt-get update
sudo apt-get install libcurl4-openssl-dev libxml2-dev
```

### На macOS:

``` bash
brew update
brew install curl
```

## Компиляция и запуск

``` bash
git clone https://github.com/firapinch/fipi_check.git
cd fipi_check
gcc ege2025check.c -o ege2025check -lcurl
```
