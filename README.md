![Line count][Line-badge] [![License][License-badge]]([License-link])

# StrawberryOS

StrawberryOS is a project operating system developed for the ARMv8 64-bit architecture, specifically for the Raspberry PI 4B.

## Installation

Currently there are no releases available, so you would have to clone the source code, and make the image with ``make all``
Then the contents of the SDCard folder should be copied to the 'bootfs' partition of the SD card (the SD card should be partitioned as if you installed Raspbian)

## Features

Currently the only features that work are:

- the mini UART
- the Video Core mailbox for retrieving machine information such as the revision number, burned-in MAC address etc.
- simple heap allocation

### Current priorities

I am currently focusing most of my efforts on:

- the virtual address space and utilizing the MMU
- interrupt handling and system calls

## Wiki

You can find information on the OS [here](https://github.com/stcksmsh/StrawberryOS/wiki)

## Contributing

Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License

[MIT][License-link]

[Line-badge]: https://img.shields.io/badge/Lines-4.38k-f89820?style=for-the-badge
[License-badge]: https://img.shields.io/badge/License-MIT-04a635?style=for-the-badge
[License-link]: https://opensource.org/licenses/MIT
