# TCP echo server

This project defines a template TCP server written in C++ using the [asio](https://think-async.com/Asio/) library for networking and [Gtest](https://github.com/google/googletest) for testing.

What you will find here:

- a working server accepting connections on a configurable port.
- a client system allowing to take actions when a client dis/connects and sends data.
- a working CI running the tests on each commit.
- a build process to package the server in a docker image.

This extracts the server proposed in [bsgalone](https://github.com/Knoblauchpilze/bsgalone) and removes the logic to play the game to keep a simple echo TCP server.

Yet another copy of a famous game which will be probably not as polished and not as fun as the original. This time we try out: [Battlestar Galactica Online](https://www.mmorpg.com/battlestar-galactica-online).

# Badges

TODO: Will come later

# Installation

⚠️ The following sections are tailored for an installation on Ubuntu: this is what was used during the development. If you want to try to install it on another OS it probably works but some of the command will need to be adapted.

If you do so, please consider contributing the guide as an issue to help fellow developers!

## Clone the repository

The first step (as is often the case) if you want to work on this project is to clone the repository with:

```bash
git clone git@github.com:Knoblauchpilze/tcp-server.git
# Move to the project's folder
cd tcp-server
```

## Install the asio library (Ubuntu)

This project uses the `asio` library for networking. There are two ways to install it: either using the version available in the packages. At the time of writing with Ubuntu 20.04 the packaged version is `1.18.1` which is quite old (2020). If you choose to do so, you can run:

```bash
apt-get install libasio-dev
```

You can also download the sources directly from the [official website](https://think-async.com/Asio/) (click on `Downloads`). This gives version `1.30.2` (at the time of writing).

**Note:** we used version `1.28` for the development.

The download process gives a `tar.bz2` file which can be extracted with (change the version as needed) and installed:

```bash
tar -xvjf asio-1.28.0.tar.bz2
sudo mkdir /usr/local/include/asio
sudo cp -r asio-1.28.0/include/* /usr/local/include/asio
```

You can remove the `Makefile.am` and `Makefile.in` files from this directory to not pollute the includes.

**Note:** in case you face problems to compile the project, you can take a look at the [Use asio](https://github.com/Knoblauchpilze/bsgalone?tab=readme-ov-file#use-the-library-in-the-project) section in the [bsgalone](https://github.com/Knoblauchpilze/bsgalone) project. Maybe this can help you.

## VScode configuration

In case you use VScode as an IDE to work on this project, it is recommended to create a `.vscode` folder at the root of the directory. You can then copy past the following configuration in a `c_cpp_properties.json` file:

```json
{
  "configurations": [
    {
      "name": "Linux",
      "includePath": [
        "${workspaceFolder}/**",
        "${workspaceFolder}/src/core",
        "/usr/local/include/",
        "/usr/local/include/asio"
      ],
      "defines": [],
      "compilerPath": "/usr/bin/g++",
      "cppStandard": "c++20",
      "intelliSenseMode": "linux-gcc-x64",
      "configurationProvider": "ms-vscode.cmake-tools"
    }
  ],
  "version": 4
}
```

Note that this will require you to install the [cmake-tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools) extension in the IDE and have a local `g++` version supporting at least `c++20`.

#
