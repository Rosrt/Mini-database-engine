# MiniDB 🗄️

A **lightweight mini database engine** built in **C++**, providing a **SQL-like interface** with file persistence.
It’s a great project to understand how databases store and manage records behind the scenes.

---

## ✨ Features

* **INSERT** records with flexible `key=value` fields.
* **SELECT** all or filtered records.
* **UPDATE** records using conditions.
* **DELETE** records by condition.
* **File persistence** → automatically loads from `data.txt` on startup and saves on exit.
* Simple **interactive CLI** (command-line interface).

---

## ⚙️ Requirements

* C++11 or higher
* A C++ compiler (e.g., `g++`, `clang++`, or MSVC)
* Works on **Linux**, **Windows**, and **macOS**

---

## 🛠️ Compilation & Run

### 1. Compile

```bash
g++ -std=c++11 -o minidb main.cpp
```

### 2. Run

```bash
./minidb   # Linux / macOS
minidb.exe # Windows
```

---

## 🚀 Commands & Usage

When you start, MiniDB shows:

```
🚀 MiniDB started. Commands:
INSERT key=value key=value
SELECT [condition]
DELETE key=value
UPDATE key=value WHERE key=value
EXIT (saves and quits)
```

### 📌 Examples

#### Insert Records

```bash
> INSERT name=Harshit age=22 city=Delhi
✅ Record inserted!

> INSERT name=Alice age=30 city=London
✅ Record inserted!
```

#### Select All Records

```bash
> SELECT
name=Harshit age=22 city=Delhi
name=Alice age=30 city=London
```

#### Select with Condition

```bash
> SELECT city=Delhi
name=Harshit age=22 city=Delhi
```

#### Update Records

```bash
> UPDATE age=23 WHERE name=Harshit
✏️ Updated 1 record(s).

> SELECT
name=Harshit age=23 city=Delhi
name=Alice age=30 city=London
```

#### Delete Records

```bash
> DELETE name=Alice
🗑️ Deleted 1 record(s).
```

#### Exit & Save

```bash
> EXIT
💾 Database saved to data.txt
👋 Exiting MiniDB.
```

---

## 📂 File Storage Format

MiniDB stores records in `data.txt`.

Example:

```
name=Harshit,age=23,city=Delhi
name=Alice,age=30,city=London
```

* Each line = one record.
* Fields are stored as `key=value` pairs separated by commas.
* This file is **loaded automatically** when MiniDB starts and **saved** on exit.

---

## ⚠️ Notes & Limitations

* **Conditions only support `key=value`** (no `<`, `>`, `AND`, `OR` yet).
* `INSERT` uses **space-separated** pairs, while saved file uses **comma-separated** format.
* No type system → everything is stored as a string.
* No indexes → searches are linear (`O(n)`).

---

## 🧩 Example Session

```
$ ./minidb
🚀 MiniDB started. Commands:
INSERT key=value key=value
SELECT [condition]
DELETE key=value
UPDATE key=value WHERE key=value
EXIT (saves and quits)

> INSERT name=John age=25 city=Paris
✅ Record inserted!

> INSERT name=Emma age=28 city=Berlin
✅ Record inserted!

> SELECT
name=John age=25 city=Paris
name=Emma age=28 city=Berlin

> UPDATE age=26 WHERE name=John
✏️ Updated 1 record(s).

> DELETE city=Berlin
🗑️ Deleted 1 record(s).

> EXIT
💾 Database saved to data.txt
👋 Exiting MiniDB.
```

---

## 🔮 Future Improvements

* Support multiple conditions (`AND`, `OR`).
* Add comparison operators (`<`, `>`, `!=`).
* Improve parser for SQL-like syntax.
* Add indexing for faster lookups.
* Implement transactions and rollback.
* Create a **C++ API** for programmatic usage.

---

## 👨‍💻 Author

* Developed by **Harshit Singh**
* Email: `lifeaspirant24@gmail.com`

---