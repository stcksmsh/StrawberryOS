![Line count][Line-badge] [![License][License-badge]]([License-link])

# StrawberryOS

StrawberryOS is a project operating system developed for the ARMv8 64-bit architecture, specifically for the Raspberry PI 4B.

## Installation

Currently there are no releases available, so you would have to clone the source code, and make the image with ``make all``\
Then the contents of the SDCard folder should be copied to the 'bootfs' partition of the SD card (the SD card should be partitioned as if you installed Raspbian)

## Features

Currently the only features that work are:

- the mini UART
- the Video Core mailbox for retrieving machine information such as the revision number, burned-in MAC address etc.
- simple heap allocation

## Documentation

I have created several `.md` documentation files in the `doc/` folder, 
> - Information on [notation](./doc/notation.md)
> - Short explanation of all the [classes](./doc/classes.md)
> - Some information on [mailboxes](./doc/mailbox.md)

## Contributing

Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License

[MIT][License-link]

[Line-badge]: https://img.shields.io/badge/Lines-2.79k-f89820?style=for-the-badge
[License-badge]: https://img.shields.io/badge/License-MIT-04a635?style=for-the-badge
[License-link]: https://opensource.org/licenses/MIT
