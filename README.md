# cpplox

### Дисклеймер ###
Всем привет!
Этот проект является реализацией интерпретатора для языка lox на C++. Для написания кода и освоения нужной информации я пользуюсь книгой Robert Nystrom "Crafting Interpreters".

Данный проект все ещё пишется) на данный момент уже готов парсер.

## Компиляция ##
Для запуска компиляции *.lox файла требуется:
```
cmake .
make
./cpplox file_path
```

Также можно запустить интерпретатор в командной строке:
```
cmake .
make
./cpplox
```

## Часть I. Грамматика языка lox ##

```
expression     → literal
               | unary
               | binary
               | grouping ;

literal        → NUMBER | STRING | "true" | "false" | "nil" ;
grouping       → "(" expression ")" ;
unary          → ( "-" | "!" ) expression ;
binary         → expression operator expression ;
operator       → "==" | "!=" | "<" | "<=" | ">" | ">="
               | "+"  | "-"  | "*" | "/" ;
```

## О репозиторие ##

*   `examples/` – Содержит некоторые примеры программ на lox.
*   `include/` – Содержит необходимые headers
*   `src/` – Содержит код


