# show-properties

> A Node.js module for showing the File Explorer properties dialog for a file or folder on Windows.

This project is part of [#CreateWeekly](https://twitter.com/JosephusPaye/status/1214853295023411200), my attempt to create something new publicly every week in 2020.

## Why

It's easy to call [ShellExecuteEx](https://docs.microsoft.com/en-us/windows/win32/api/shellapi/nf-shellapi-shellexecuteexa) with the `properties` verb to show the properties dialog. [What's hard](https://devblogs.microsoft.com/oldnewthing/?p=22163) is keeping the dialog open without blocking or using hacks like `Sleep()`. This module solves that problem using a custom executable and a wrapping Node module.

## Installation

```
npm install @josephuspaye/show-properties --save
```

## Usage

```js
const { showProperties } = require('@josephuspaye/show-properties');

// Show the properties dialog for the default local disk
showProperties('C:\\');

// Show the properties dialog for a file
showProperties('C:\\my-file.txt');

// Show the properties dialog for a folder
showProperties('C:\\my-folder');
```

## API

```ts
/**
 * Show the Explorer properties dialog for the file or folder at the given path.
 * Returns the exit code of the launcher process (not the launched dialog process).
 */
function showProperties(targetPath: string): Promise<number | null>;
```

## Building the executable

The module uses an executable to launch the properties dialog for the given path. The source of this executable is at [src/show-properties.cpp](src/show-properties.cpp) and you can build it as follows:

- Install an MSVC Compiler. You can get this with [windows-build-tools](https://www.npmjs.com/package/windows-build-tools) or Visual Studio.
- Copy the `.env.bat.example` file to `.env.bat` and update the variables to match your system
- Run `./build.bat` to build. The resulting executable will be placed at `bin/ShowProperties.exe`.

## Licence

[MIT](LICENCE)
