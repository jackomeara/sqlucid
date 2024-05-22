# SQLucid

A simple SQL DBMS command-line program based on SQLite architecture with a focus on a simple, user-friendly query language.

### Usage

SQLucid uses a simple yet powerful query language. The CRUD operations of a typical SQL database are offered with modified keywords:

- **get** represents the SELECT mode
- **new** represents the CREATE mode
- **add** represents the INSERT mode
- **edit** represents the UPDATE mode
- **delete** represents the DELETE mode
- **where** represents the WHERE mode

### Architecture

The architecture of SQLucid is based on that of SQLite. The tutorial series by [Connor Stack](https://cstack.github.io/db_tutorial/) that aims to create an SQLite clone serves as a base for this project. The architecture of SQLite is explained well in this tutorial's [overview](https://cstack.github.io/db_tutorial/parts/part1.html#sqlite).