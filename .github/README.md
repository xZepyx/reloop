<div align="center">

# ✦ Reloop ✦

A simple terminal utility that helps devs run commands (eg. build commands) whenever the specifed file is changed.
</div>

---

<div align="center">
  
## ✦ Overview ✦

</div>

Reloop is a lightweight terminal utility that monitors file changes in real-time and executes custom commands whenever a file is modified. Designed for developers and sysadmins, it can run in the background as a daemon and supports logging, configurable watched files, and flexible command execution.

### Features

* Real-time file monitoring.
* Background daemon mode (--background) to run without occupying a terminal
* Custom commands on file change (--command "your-command")
* Flexible file watching (--watchfile <path/complete_path_from_root>)
* Optional logging to a file (--logfile <path/complete_path_from_root>)
* Cross-platform compatible (Linux/macOS with minor tweaks)
* Simple, single C++ binary—no dependencies beyond the standard library and FileWatch


---

<div align="center">
  
## ✦ Installation ✦

</div>

Follow these steps to install the utility.

1. Clone the repository:
    ```bash
    git clone https://github.com/xZepyx/reloop.git ~/Documents/Reloop
    cd ~/Documents/Reloop
    ```

2. Build the project:
    ```bash
    mkdir build && cd build
    cmake ..
    make
    ```
3. Install the project to the system:
   ```
   sudo make install
   ```
    - The installer will compile and install the utility to /usr/local/bin/reloop

4.  Installtion complete now enjoy the power and simplicity of reloop.

---

<div align="center">
  
## ✦ Usage ✦

</div>

### Flags :
- ./reloop [--background] [--logfile <path>] [--watchfile <path>] [--help]
- --background :       Run the program as a background daemon.
- --command <cmd>:    Command to execute on file change (in quotes).
- --logfile <path>:   Specify a log file to redirect output.
- --watchfolder <path> Specify the folder to watch changes in.;
- --watchfile <path>: Specify the file to watch for changes.
- --help   :          Display this help message.

---


<div align="center">
  
## ✦ Contributing ✦

</div>

Contributions are welcome. When contributing:
- Open concise issues after confirming the problem isn't caused by local machine.
- Submit focused PRs with clear descriptions and tests where applicable.
- Follow code structure and naming conventions used in `src/`.

See `CONTRIBUTING.md` for full contribution guidelines.

---

<div align="center">
  
## ✦ Maintainer ✦

</div>

- Maintainer: xZepyx (Aditya Yadav) 
- Contact: [zepyxunderscore@gmail.com](mailto:zepyxunderscore@gmail.com)

---

<div align="center">
  
## ✦ Acknowledgments ✦

</div>

- WatchFile header.
- C++ (Obvisouly)

---

<div align="center">
  
## ✦ License ✦

</div>

© 2025 xZepyx (Aditya Yadav) — Licensed under the MIT License.

---