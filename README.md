# 📄 Get Next Line

> **42 School Project**  
> Created by **ipykhtin**

---

## 🧠 Description

The **Get Next Line** project introduces the concept of **static variables** in C and demonstrates how they can be used to maintain state between function calls.

Through this project, I explored:
- How static storage duration works in C
- Memory allocation at different stages of program execution
- File descriptors and buffered reading
- Low-level behavior of memory management and interaction with the kernel

Although I was already familiar with static fields from Java, this project allowed me to deepen my understanding of how **hardware and software memory layers** interact in C.

---

## ⚙️ Compilation

The project must be compiled using the following command:


cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
    get_next_line.c get_next_line_utils.c

---


## 📚 Resources

During the development of this project, I used the following resources to deepen my understanding of the concepts involved:

- **42 Documentation & Subject PDF** – project requirements and constraints
- **Linux man pages** (`read`, `open`, `close`, `malloc`, `free`)
- **GitHub Copilot** – assistance with code suggestions and structure
- **ChatGPT** – conceptual explanations related to:
  - static variables
  - memory allocation
  - compilation stages
  - low-level system behavior

These resources were used strictly for **learning and conceptual understanding**, not for copying code.

