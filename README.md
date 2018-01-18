# ddcset

Set [DDC/CI](https://en.wikipedia.org/wiki/Display_Data_Channel) values from the
windows commandline/scripts/etc.


## Usage

An example that (might) change monitor input:

    ddcset 0x60 0x0f


## Incomplete

It's very basic, and just kind of picks a random monitor if you have more than
one.
