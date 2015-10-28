# spconfig
Configuration UI for the RSP plugin.

## Purpose

Writes user-requested configuration settings to `rsp_conf.bin`, which is used by the ["Static Interpreter"](https://github.com/cxd4/rsp) RSP emulation plugin.  Configuring the RSP plugin through the emulator's Options menu or the like will simply re-load and refresh the contents of `rsp_conf.bin` and apply its settings.

## Configuration

Launch the EXE, and answer the questions either individually or all at once.

There are only two (or three) questions, effectively offering "HLE graphics" and "HLE audio".  If both are answered with a No (full low-level RSP emulation), there will be a third question asking to adjust the RSP semaphore register timing (which for speed and compatibility with non-supportive emulators ought to be disabled).

All questions are yes-or-no.  Only a single character can be typed in the console to respond to a single question; entering two or more characters will answer the current question with the leading character and skip over the next question, answering that automatically with the subsequent character.

## Input Interpretation
* 'N', 'n', '0' and any other character whose ASCII code point is an even number signals "no".
* 'Y', 'y', '1' and any other character whose ASCII code point is an odd number signals "yes".

If in doubt about the results written by this program, check the contents of `rsp_conf.bin`.

## Examples

```shell
spconfig # launches the configuration program
> 000 # answers No to all three questions
> yy # answers Yes to both questions
> 10101 # Yes to HLE graphics, No to HLE audio, following digits ignored.
> Y # Yes to HLE graphics.  Wait for program to inquire input for HLE audio.
```
