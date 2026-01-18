# Phase 0 — Orientation: How Unix thinks

**Goal:** Stop thinking in terms of “files” and “programs” and start thinking in terms of _kernel-managed objects_.

### Reading

- Short overview: _“The UNIX System Interface”_ (conceptual explanation of system calls and kernel/user boundary)

- Skim, do not memorize:

    - user space vs kernel space

    - system calls as the _only_ privileged boundary


### Exercise

**Prompt:**
Write a short paragraph answering:

> “What is the kernel allowed to do that user programs are not?”

Then:

- List 5 things a user program must ask the kernel to do on its behalf.

- For each, name the syscall category involved (process, file, memory, signal).


If you cannot clearly explain _why_ the kernel exists, pause here.

---

# Phase 1 — Processes (the root abstraction)

**Goal:** Understand what a process _is_, independent of programming language.

### Reading

- Process model overview (process = address space + resources + execution context)

- `fork`, `exec`, `exit`, `wait` — **conceptual descriptions only**


Key ideas to internalize:

- A process owns:

    - virtual memory

    - file descriptor table

    - signal handlers

- `fork` duplicates _structure_, not intent

- `exec` replaces memory, not the process identity


### Exercise

**Prompt:**
Without writing code, answer:

1. After `fork`, list **three things that are identical** between parent and child.

2. List **three things that are not identical**.

3. Explain why `exec` does _not_ create a new process.


Bonus (write code if you want):
Write a C program that prints:

- PID

- PPID
    before and after `fork`, then after `exec`.


---

# Phase 2 — File descriptors (the most important abstraction)

**Goal:** Understand that file descriptors are _references_, not files.

### Reading

- Conceptual article on file descriptors and kernel tables

- Focus on:

    - per-process FD table

    - open file description

    - inode

- Do **not** memorize syscall signatures yet


Key mental model:

`process → fd → open file description → inode`

### Exercise

**Prompt:**
Answer in writing:

1. What is the difference between:

    - a file descriptor

    - an open file description

    - an inode

2. Why can two file descriptors share a file offset?

3. Why can two file descriptors refer to the same inode but _not_ share offsets?


Then:

- Sketch (on paper or text) the FD table after:

    - `open`

    - `dup`

    - `fork`


---

# Phase 3 — Reading man pages correctly (open/read/write)

**Goal:** Learn how man pages encode guarantees and non-guarantees.

### Reading

- `open(2)`

- `read(2)`

- `write(2)`
    Read in this order:


1. ERRORS

2. NOTES

3. DESCRIPTION


Ignore examples.

### Exercise

**Prompt:**
For `open(2)`:

- Identify:

    - What kernel object is created?

    - What kernel object is _not_ created?

- Explain what happens to the file offset and _where it lives_.


Then:

- Write a program that:

    - opens a file twice

    - reads from each descriptor

    - prints offsets using `lseek`
        Explain the result without running it.


---

# Phase 4 — Directories, paths, and inodes

**Goal:** Understand path resolution and why filenames are not files.

### Reading

- Conceptual inode + directory explanation

- `stat(2)` and `lstat(2)` descriptions


Key ideas:

- Directories map names → inode numbers

- Hard links are additional directory entries

- `stat` follows links; `lstat` does not


### Exercise

**Prompt:**
Answer:

1. What does deleting a file _actually_ do?

2. Why does a file continue to exist after `unlink` if it is open?

3. Why can two filenames refer to the same file contents?


Then:

- Write a program that:

    - opens a file

    - unlinks it

    - continues reading from it


Explain why this works.

---

# Phase 5 — Memory and virtual address space

**Goal:** Understand that _everything_ is mediated through virtual memory.

### Reading

- Conceptual virtual memory overview

- `mmap(2)` — conceptual, not implementation details


Key ideas:

- Each process sees a private address space

- Pages are mapped, not copied

- Files can back memory mappings


### Exercise

**Prompt:**
Explain:

1. Why does `fork` not immediately double memory usage?

2. What does copy-on-write actually copy?

3. Why does `mmap` blur the line between “file” and “memory”?


Optional code:

- Map a file with `mmap`

- Modify it

- Observe effects on disk


---

# Phase 6 — Signals and asynchronous behavior

**Goal:** Understand why man pages warn about async safety.

### Reading

- Conceptual signal handling overview

- `signal(2)` / `sigaction(2)` descriptions

- Async-signal-safe function list (skim)


Key ideas:

- Signals interrupt control flow

- Most library functions are unsafe in handlers

- The kernel can deliver signals _at any time_


### Exercise

**Prompt:**
Answer:

1. Why is `printf` unsafe in a signal handler?

2. Why are signals described as “process-wide”?

3. What kernel state exists independently of your code’s control flow?


Optional:

- Write a signal handler that sets a flag

- Handle it safely in `main`


---

# Phase 7 — Event notification (kqueue / FSEvents)

**Goal:** Understand kernel-driven event models.

### Reading

- High-level kqueue overview

- `kqueue(2)` and `kevent(2)` descriptions

- Focus on:

    - filters

    - kernel maintaining state

    - readiness vs occurrence


### Exercise

**Prompt:**
Explain in your own words:

1. Why is `kqueue` more efficient than polling?

2. Why does `EVFILT_VNODE` watch _vnode state_, not file contents?

3. Why does `O_EVTONLY` exist?


Then:

- Sketch a simple event loop using kqueue (pseudocode is fine).


---

# Phase 8 — Putting it together: reread man pages

**Goal:** Confirm that ambiguity now feels _intentional_, not confusing.

### Reading

Revisit:

- `fork(2)`

- `open(2)`

- `stat(2)`

- `kevent(2)`


### Final Exercise

**Prompt:**
Pick **one** syscall and write:

- What kernel objects it touches

- What it guarantees

- What it explicitly does _not_ guarantee

- One bug that could arise if you misunderstand it


If you can do this confidently, you now have the conceptual foundation man pages assume.

---

https://zedware.github.io/homepage/code/tcpl/index.html the c programming language
