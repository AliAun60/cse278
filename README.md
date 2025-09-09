# CSE 278 – Code & Mini-Projects

Welcome! 👋  
This repository is a collection of small programs and web pages I built while learning systems/software fundamentals. It’s meant to be **easy to browse** and **easy to run**.

## 🔎 What’s inside
- Short C++ utilities (I/O, files, simple algorithms)
- Simple web pages (HTML/CSS/JS) used for basic front-end practice
- Clear run instructions for each item

> Tip: Jump to **[How to Run](#-how-to-run)** and **[Project Index](#-project-index)**.

---

## 🧭 Project Index

| Area | Name / Folder | What it demonstrates | How to try it |
|---|---|---|---|
| C++ | `cpp/total_payments/` | File reading + aggregate totals | `g++ main.cpp -o total_payments && ./total_payments` |
| C++ | `cpp/get_total_orders/` | Parsing input + counting | `g++ main.cpp -o get_total_orders && ./get_total_orders` |
| Web | `web/index.html` | Simple static page | Open in browser |
| Web | `web/customers/` | List + basic layout | Open `web/customers/index.html` |

> If your files are currently in the root, consider moving them into `cpp/...` and `web/...` folders like above. (See **Repo structure** below.)

---

## 🚀 How to Run

### Prereqs
- **C++:** any modern compiler (GCC/Clang/MSVC)
- **Web:** any browser (Chrome/Firefox/Edge)
- **Optional:** VS Code + C/C++ extension

### C++ (example)
```bash
# from repo root
cd cpp/total_payments
g++ main.cpp -o total_payments
./total_payments   # Windows: .\total_payments.exe
