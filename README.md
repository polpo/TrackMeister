Tracked Music Compo Player
==========================

This application is a player for [tracker music files](https://en.wikipedia.org/wiki/Module_file) ("module" files) as they were &ndash;and still are&ndash; common in the [demoscene](https://en.wikipedia.org/wiki/Demoscene). With its fullscreen interface and limited interaction options, it's specifically targeted towards presenting tracked music in a competition ("compo").

## Features

- based on [libopenmpt](https://lib.openmpt.org/libopenmpt/), a very well-regarded library for module file playback
- plays all common formats: MOD, XM, IT, S3M, and a dozen others
- fullscreen interface based on OpenGL
- metadata display (title, artist, technical info, module comment, intstrument and sample names)
- pattern display for visualization
- cross-platform (tested on Windows and Linux)
- single executable; no extra DLLs/`.so`s needed
- open source (MIT license)

## Building

- prerequisites:
  - a C++17 compatible compiler (GCC 7.1 or later, Clang 6 or later, Microsoft Visual Studio 2019 or later)
  - CMake 3.15 or later
  - Python 3.8 or later
  - SDL2 development packages (only required on non-Windows systems; on Windows, the SDL2 SDK will be downloaded automatically during building)
- make sure you cloned the repository recursively, as it pulls libopenmpt in as a submodule; if you forgot that, run "`git submodule update --init`"
- building itself is done using standard CMake (e.g. "`cmake -S . -B build && cmake --build build`")

## Usage

Just drag a module file onto the executable, or into the window once the player has already been started. If a directory is opened this way, the first playable file therein is loaded. Note that this is *not* recursive; TMCP won't play entire directory hierarchies.

Playback is always paused after loading a module; this is by design. Press the **Space** key to start playback.

The screen is split into three parts: The pattern display, the info bar at the top (containing basic information about the module format as well as filename, title and artist), and the metadata bar at the right (with the free-text module message, instrument and sample names). If the content doesn't fit in the metadata bar, it slowly scrolls down during playback, so it reaches the bottom end at the end of the track or after four minutes, whatever comes first.

The following other controls are available:

| Input | Action |
|-------|--------|
| **Q** or **Alt+F4** | quit the application
| **Space** | pause / continue playback
| **Tab** | hide / unhide the info and metadata bars
| Cursor **Left** / **Right** | seek backward / forward one order
| **Page Up** | load previous module in the directory
| **Page Down** | load next module in the directory
| **Ctrl+Home** | load first module in the directory
| **Ctrl+End** | load last module in the directory
| Mouse Wheel | manually scroll through the metadata bar (stops autoscrolling)
| **A** | stop / resume autoscrolling
| **F** | slowly fade out the song
| **V** | show the TMCP and libopenmpt version numbers
| **F5** | reload the current module and the application's configuration
| **F11** | toggle fullscreen mode
| **Ctrl+Shift+S** | save `tmcp_default.ini` (see below)

For directory navigation, "previous" and "next" refer to case-insensitive lexicographical ordering.


## Configuration

TMCP can be configured using configuration files with an INI-like syntax.

The following aspects can be configured:
- display colors and font sizes (but **not** the font itself; that's "baked into" the program)
- windowed/fullscreen mode and window size (*)
- audio sample rate and buffer size (*)
- audio interpolation filter
- amount of stereo separation

All items can be changed at runtime when loading a new module or pressing the **F5** key, _except_ those marked with an asterisk (*); these are only evaluated once on startup.

The following locations are searched for configuration files:
- `tmcp.ini` in the program's directory (i.e. directly next to `tmcp.exe`)
- `tmcp.ini` in the currently opened module file's directory
- a file with the same name as the currently opened module file, but with `.tmcp` as a suffix; for example, for `foo.mod`, the configuration file will be `foo.tmcp`

The configuration files can contain multiple sections, delimited by lines containing the section name in square brackets, `[like so]`. The following sections are evaluated, and all other sections are ignored:
- the unnamed section at the beginning of the file
- the `[TMCP]` section
- sections that match the current module's file name, e.g. `[foo*.mod]`;
  the following rules apply for those:
  - only the filename is matched, no directory names
  - matching is case-insensitive
  - exactly one '`*`' may be used as a wildcard (no '`?`'s, no multiple '`*`'s)

All other lines contain key-value pairs of the form "`key = value`" or "`key: value`". Spaces, dashes (`-`) and underscores (`_`) in key names are ignored. All parts of a line following a semicolon (`;`) are ignored. It's allowed to put comments at the end of key/value lines.

To get a list of all possible settings, along with documentation and the default values for each setting, run TMCP and press **Ctrl+Shift+S**. This will generate a file `tmcp_default.ini` in the current directory (usually the program directory) that also be used as a template for an individual configuration.

All sizes (font sizes, margins etc.) are specified in 1/1000s of the display width, so they are more or less resolution-independent. Colors are specified in HTML/CSS-style hexadecimal RGB notation, but with optional alpha, i.e. in the form `#rrggbb`, `#rrggbbaa`, `#rgb` or `#rgba`.

Here's an example for a useful INI file:

    [TMCP]
    ; generic options, specified in classic INI syntax

    ; we want a decent filter and full stereo for most module formats
    filter=auto
    stereoSeparation=100

    [*.mod]
        ; this section is only active for MOD format file, which tend to be
        ; written on or for the Amiga, hence we want a suitable filter
        ; emulation and way less stereo separation;
        ; also, we're specifying this in CSS-like syntax, because we can:
        filter: auto;
        stereo-separation: 100;
